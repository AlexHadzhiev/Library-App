#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "include/db_utils.h"

char *
read_from_init_file ()
{
	int fd = open ( "/home/thelichknight/School/TP/library_app/Library-App/src/init_query.txt" , O_RDONLY );
	if ( fd < 0 )
	{
		perror ( "open [read_from_init_file]" );
		
		return ( char * ) NULL;
	}

	size_t size = 1024;
	size_t offset = 0;
	ssize_t bytes_read;

	char * init_query_buffer = ( char * ) calloc ( (size * 2) , sizeof(char) );

	while ( (bytes_read = read ( fd , (init_query_buffer + offset) , 512 )) != 0 )
	{
		if ( bytes_read < 0 )
		{
			perror ( "read [read_from_init_file]" );
			
			free ( init_query_buffer );
			
			return ( char * ) NULL;
		}

		offset += bytes_read;

		if ( (offset + 512) > size )
		{
			size *= 2;
			init_query_buffer = ( char * ) realloc ( init_query_buffer , (size * 2) );
		}
	}

	init_query_buffer[(strlen ( init_query_buffer ) - 1)] = '\0';

	if ( close ( fd ) < 0)
	{
		perror ( "close [read_from_init_file]" );
		
		free ( init_query_buffer );
		
		return ( char * ) NULL;
	}

	return init_query_buffer;
}

char **
split_init_query ( char * init_query_buffer )
{
	char * init_query_buffer_backup = ( char * ) calloc ( 2048 , sizeof(char) );
	
	strcpy ( init_query_buffer_backup , init_query_buffer );

	char ** split_init_query_buffer = ( char ** ) calloc ( 3 , sizeof(char *) );
	for ( int i = 0 ; i < 3 ; ++i )
		split_init_query_buffer[i] = ( char * ) calloc ( 1024 , sizeof(char) );

	char * query = strtok ( init_query_buffer_backup , ";" );

	for ( int i = 0 ; (i < 3) && (query != NULL) ; ++i )
	{
		strcpy ( split_init_query_buffer[i] , query );
		query = strtok ( NULL , ";" );
	}

	free ( init_query_buffer_backup );
	free ( query );
	
	return split_init_query_buffer;
}

MYSQL * 
init_db ()
{
	char * init_query_buffer = read_from_init_file ();
	char ** split_init_query_buffer = split_init_query ( init_query_buffer );

	MYSQL * connection = mysql_init ( NULL );

	if ( (mysql_real_connect ( connection , "localhost" , "thelichknight" , "12345678" , NULL , 0 , NULL , 0 )) == NULL )
	{
		perror ( "mysql_real_connect [init_db]" );
		
		for ( int i = 0 ; i < 3 ; ++i )
			free ( split_init_query_buffer[i] );
		
		free ( init_query_buffer );
		free ( split_init_query_buffer );
		
		mysql_close ( connection );
		
		return ( MYSQL * ) NULL;
	}

	if ( mysql_query ( connection , "CREATE DATABASE Library_App" ) )
	{
		perror ( "mysql_query [init_db]" );
		
		for ( int i = 0 ; i < 3 ; ++i )
			free ( split_init_query_buffer[i] );
		
		free ( init_query_buffer );
		free ( split_init_query_buffer );
		
		mysql_close ( connection );

		return ( MYSQL * ) NULL;
	}

	if ( mysql_select_db ( connection , "Library_App" ) )
	{
		perror ( "mysql_select_db [init_db]" );
		
		for ( int i = 0 ; i < 3 ; ++i )
			free ( split_init_query_buffer[i] );
		
		free ( init_query_buffer );
		free ( split_init_query_buffer );
		
		mysql_close ( connection );
		
		return ( MYSQL * ) NULL;
	}

	for ( int i = 0 ; i < 3 ; ++i )
	{
		if ( mysql_query ( connection , split_init_query_buffer[i] ) )
		{
			perror ( "mysql_query [init_db]" );
			
			for ( int i = 0 ; i < 3 ; ++i )
				free ( split_init_query_buffer[i] );
			
			free ( init_query_buffer );
			free ( split_init_query_buffer );
			
			mysql_close ( connection );

			return ( MYSQL * ) NULL;
		}
	}

	if ( !default_collection_set )
	{
		if ( mysql_query ( connection , "INSERT INTO Collection(name) VALUES(\"DEFAULT COLLECTION\")" ) )
		{
			perror ( "mysql_query [init_db]" );
			
			for ( int i = 0 ; i < 3 ; ++i )
				free ( split_init_query_buffer[i] );
			
			free ( init_query_buffer );
			free ( split_init_query_buffer );
			
			mysql_close ( connection );
			
			return ( MYSQL * ) NULL;
		}

		default_collection_set = 1;
	}

	for ( int i = 0 ; i < 3 ; ++i )
		free ( split_init_query_buffer[i] );

	free ( init_query_buffer );
	free ( split_init_query_buffer );

	return connection;
}

int
insert_book ( MYSQL * connection , char ** values )
{
	char * query_buffer = ( char * ) calloc ( 2048 , sizeof(char) );

	strcpy ( query_buffer , "INSERT INTO Book(title, author, publisher, year, pagecount, filepath, filename) VALUES(" );
	
	for ( int i = 0 ; i < 7 ; ++i )
	{
		if ( !strcmp ( values[i] , "\n" ) )
			strcat ( query_buffer , "NULL" );
		else 
		{	
			if ( (i != 3) || (i != 4) )
				strcat ( query_buffer , "\"" );
			
			strcat ( query_buffer , values[i] );
			
			if ( (i != 3) || (i != 4) )
				strcat ( query_buffer , "\"" );
		}

		if ( i < 6 )
			strcat ( query_buffer , ", " );
		else
			strcat ( query_buffer , ")" );
	}

	strcat ( query_buffer , "\0" );

	if ( mysql_query ( connection , query_buffer ) )
	{
		perror ( "mysql_query [insert_book]" );
		
		free ( query_buffer );
		
		return -1;
	}

	free ( query_buffer );

	return 0;
}

int
insert_collection ( MYSQL * connection , char ** values )
{
	char * query_buffer = ( char * ) calloc ( 2048 , sizeof(char) );

	strcpy ( query_buffer , "INSERT INTO Collection(name) VALUES(\"" );
	strcat ( query_buffer , values[0] );
	strcat ( query_buffer , "\")\0" );

	if ( mysql_query ( connection , query_buffer ) )
	{
		perror ( "mysql_query [insert_collection]" );
		
		free ( query_buffer );
		
		return -1;
	}

	free ( query_buffer );

	return 0;
}

int
insert_book_into_collection ( MYSQL * connection , char ** values )
{
	char * query_buffer = ( char * ) calloc ( 2048 , sizeof(char) );

	strcpy ( query_buffer , "INSERT INTO BookCollection(book_id, collection_id) VALUES(" );
	strcat ( query_buffer , values[0] );
	strcat ( query_buffer , ", " );
	strcat ( query_buffer , values[1] );
	strcat ( query_buffer , ")\0" );

	if ( mysql_query ( connection , query_buffer ) )
	{
		perror ( "mysql_query [insert_book_into_collection]" );
		
		free ( query_buffer );
		
		return -1;
	}

	free ( query_buffer );

	return 0;
}

int
delete_book ( MYSQL * connection , char ** values )
{
	char * query_buffer = ( char * ) calloc ( 2048 , sizeof(char) );

	strcpy ( query_buffer , "DELETE Book FROM Book WHERE id = " );
	strcat ( query_buffer , values[0] );
	strcat ( query_buffer , "\0" );

	if ( mysql_query ( connection , query_buffer ) )
	{
		perror ( "mysql_query [delete_book]" );
		
		free ( query_buffer );
		
		return -1;
	}

	free ( query_buffer );

	return 0;
}

int
delete_collection ( MYSQL * connection , char ** values )
{
	char * query_buffer = ( char * ) calloc ( 2048 , sizeof(char) );
	
	strcpy ( query_buffer , "DELETE Collection FROM Collection WHERE id = " );
	strcat ( query_buffer , values[0] );
	strcat ( query_buffer , "\0" );

	if ( mysql_query ( connection , query_buffer ) )
	{
		perror ( "mysql_query [delete_collection]" );
		
		free ( query_buffer );
		
		return -1;
	}
	
	free ( query_buffer );

	return 0;
}

int
delete_book_from_collection ( MYSQL * connection , char ** values )
{
	char * query_buffer = ( char * ) calloc ( 2048 , sizeof(char) );

	strcpy ( query_buffer , "DELETE BookCollection FROM BookCollection WHERE book_id = " );
	strcat ( query_buffer , values[0] );
	strcat ( query_buffer , " AND collection_id = " );
	strcat ( query_buffer , values[1] );
	strcat ( query_buffer , "\0" );

	if ( mysql_query ( connection , query_buffer ) )
	{
		perror ( "mysql_query [delete_book_from_collection]" );
		
		free ( query_buffer );
		
		return -1;
	}

	free ( query_buffer );

	return 0;
}
