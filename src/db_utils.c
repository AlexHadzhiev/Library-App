#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>
#include "include/db_utils.h"

char *
read_from_init_file ( void )
{
	int fd = open ( "init_query.txt" , O_RDONLY );
	if ( fd < 0 )
	{
		perror ( "open" );
		return ( char * ) NULL;
	}

	size_t size = 1024;
	size_t offset = 0;
	ssize_t bytes_read;

	char * init_query_buffer = ( char * ) calloc ( size , sizeof(char) );
	
	while ( (bytes_read = read ( fd , ( init_query_buffer + offset ) , 128 )) != 0 )
	{
		if ( bytes_read < 0 )
		{
			perror ( "read" );
			return ( char * ) NULL;
		}

		offset += bytes_read;

		if ( ( offset + 128 ) > size )
		{
			size *= 2;
			init_query_buffer = ( char * ) realloc ( init_query_buffer , size );
		}
	}

	init_query_buffer[ ( strlen ( init_query_buffer ) - 1 ) ] = '\0';

	if ( close ( fd ) < 0 )
	{
		perror ( "close" );
		return ( char * ) NULL;
	}

	return init_query_buffer;
}

char **
split_init_query ( char * init_query_buffer )
{
	char ** split_query_buffer = ( char ** ) calloc ( 3 , sizeof(char *) );
	for ( int i = 0 ; i < 3 ; ++i )
		split_query_buffer[i] = ( char * ) calloc ( 2048 , sizeof(char) );

	strcpy ( split_query_buffer[0] , strtok ( init_query_buffer , ";" ) );
	strcpy ( split_query_buffer[1] , strtok ( NULL , ";" ) );
	strcpy ( split_query_buffer[2] , strtok ( NULL , ";" ) );

	return split_query_buffer;
}

MYSQL *
init_db ( char ** init_query )
{
	MYSQL * connection = mysql_init ( NULL );

	if ( ( mysql_real_connect ( connection , "localhost" , "thelichknight" , "12345678" , NULL , 0 , NULL , 0 ) ) == NULL )
	{
		perror ( "mysql_real_connect" );
		return ( MYSQL * ) NULL;
	}

	if ( mysql_query ( connection , "CREATE DATABASE Library_App" ) )
	{
		perror ( "mysql_query" );
		return ( MYSQL * ) NULL;
	}

	if ( mysql_select_db ( connection , "Library_App" ) )
	{
		perror ( "mysql_select_db" );
		return ( MYSQL * ) NULL;
	}

	for ( int i = 0 ; i < 3 ; ++i )
	{
		if ( mysql_query ( connection , init_query[i] ) )
		{
			perror ( "mysql_query" );
			return ( MYSQL * ) NULL;
		}
	}

	if ( !default_collection_created )
	{
		char * create_default_collection_query = ( char * ) calloc ( 512 , sizeof(char) );
		
		strcpy ( create_default_collection_query , "INSERT INTO Collection(id, NAME) VALUES(1, \"DEFAULT COLLECTION\")" );
		
		default_collection_created = 1;

		free ( create_default_collection_query );
	}

	if ( mysql_query ( connection , init_query[i] ) )
	{
		perror ( "mysql_query" );
		return ( MYSQL * ) NULL;
	}

	return connection;
}

int 
insert_book ( MYSQL * connection , char ** values )
{
	char * query_buffer = ( char * ) calloc ( 2048 , sizeof(char) );
	
	strcpy ( query_buffer , "INSERT INTO Book(Title, Author, Publisher, Year, Pagecount, Filepath, Filename) VALUES(" );

	for ( int i = 0 ; i < 7 ; ++i )
	{
		if ( !strcmp ( values[i] , "\n" ) )
			strcat ( query_buffer , "NULL" );
		else if ( ( i != 3 ) && ( i != 4 ) )
		{
			strcat ( query_buffer , "\"" );
			strcat ( query_buffer , values[i] );
			strcat ( query_buffer , "\"" );
		}
		else
		{
			strcat ( query_buffer , values[i] );
		}

		if ( i < 6 )
			strcat ( query_buffer , "," );
		else
			strcat ( query_buffer , ")" ); 
	}

	strcat ( query_buffer , "\0" );

	if ( mysql_query ( connection , query_buffer ) )
	{
		perror ( "mysql_query" );
		return -1;
	}

	free ( query_buffer );

	return 0;
}

int
insert_collection ( MYSQL * connection , char * value )
{
	char * query_buffer = ( char * ) calloc ( 2048 , sizeof(char) );

	strcpy ( query_buffer , "INSERT INTO Collection(Name) VALUES(" );
	strcat ( query_buffer , value );
	strcat ( query_buffer , "\")\0" );

	if ( mysql_query ( connection , query_buffer ) )
	{
		perror ( "mysql_query" );
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
		perror ( "mysql_query" );
		return -1;
	}

	return 0;
}

int
delete_collection ( MYSQL * connection , char ** values )
{
	char * query_buffer = ( char * ) calloc ( 2048 , sizeof(char) );

	strcpy ( query_buffer , "DELETE Collection FROM Collection WHERE id = \"" );
	strcat ( query_buffer , values[0] );
	strcat ( query_buffer , "\0");

	if ( mysql_query ( connection , query_buffer ) )
	{
		perror ( "mysql_query" );
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
		perror ( "mysql_query" );
		return -1;
	}

	free ( query_buffer );

	return 0;
}

int
delete_book_from_collection ( MYSQL * connection , char ** values )
{
	char * query_buffer = ( char * ) calloc ( 2048 , sizeof(char) );

	if ( mysql_query ( connection , query_buffer ) )
	{
		perror ( "mysql_query" );
		return -1;
	}

	free ( query_buffer );z

	return 0;
}
