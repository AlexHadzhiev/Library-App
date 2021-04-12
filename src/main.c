#include "include/db_utils.h"
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

MYSQL *
init_db ( void )
{
	MYSQL * mysql_connection = mysql_init ( NULL );
	
	if ( (mysql_real_connect ( mysql_connection , "localhost" , "thelichknight" , "12345678" , NULL , 0 , NULL , 0 )) == NULL )
	{
		perror ("mysql_real_connect");
		return NULL;
	}

	if ( mysql_query ( mysql_connection , "CREATE DATABASE Library_App" ) )
	{
		perror ( "mysql_query" );
		return NULL;
	}

	if ( mysql_select_db ( mysql_connection , "Library_App" ) )
	{
		perror ( "mysql_select_db" );
		return NULL;
	}

	int fd = open ( "init_query.txt" , O_RDONLY );
	if ( fd < 0 )
	{
		perror ( "open" );
		return NULL;
	}

	size_t size = 1024;
	size_t offset = 0;
	ssize_t bytes_read;

	char * query_buffer = ( char * ) calloc ( size , sizeof(char) );
	
	while ( (bytes_read = read ( fd , (query_buffer + offset) , 128 )) != 0 )
	{
		if ( bytes_read < 0 )
		{
			perror ( "read" );
			return NULL;
		}

		offset += bytes_read;
		
		if ( (offset + 128) > size )
		{
			size *= 2;
			query_buffer = ( char * ) realloc ( query_buffer , size );
		}
	}

	query_buffer[ (strlen ( query_buffer )) - 1 ] = '\0';

	char * query_buffer1 = ( char * ) calloc ( 1024 , sizeof(char) );
	char * query_buffer2 = ( char * ) calloc ( 1024 , sizeof(char) );

	query_buffer1 = strtok ( query_buffer , ";" );
	query_buffer2 = strtok ( NULL , ";" );

	if ( close ( fd ) < 0 )
	{
		perror ( "close" );
		return NULL;
	}

	if ( mysql_query ( mysql_connection , query_buffer1 ) )
	{
		perror ( "mysql_query" );
		return NULL;
	}

	if ( mysql_query ( mysql_connection , query_buffer2 ) )
	{
		perror ( "mysql_query" );
		return NULL;
	}

	return mysql_connection;
}

int
insert_book ( MYSQL * mysql_connection , char ** values )
{
	char * query_buffer = ( char * ) calloc ( 1024 , sizeof(char) );

	strcpy ( query_buffer , "INSERT INTO Book(Title, Author, Publisher, Year, Pagecount, Filepath, Filename) VALUES(" );

	for ( int i = 0 ; i < 7 ; ++i )
	{
		if ( !strcmp ( values[i] , "\n" ) )
			strcat ( query_buffer , "NULL" );
		else
		{
			strcat ( query_buffer , "\"" );
			strcat ( query_buffer , values[i] );
			strcat ( query_buffer , "\"" );
		}

		if ( i < 6 )
			strcat ( query_buffer , "," );
		else
			strcat ( query_buffer , ")" ); 
	}

 	strcat ( query_buffer , "\0" );

	if ( mysql_query ( mysql_connection , query_buffer ) )
	{
		perror ( "mysql_query" );
		return -1;
	}

	free ( query_buffer );

	return 0;
}

int
insert_collection ( MYSQL * mysql_connection , char ** values )
{
	char * query_buffer = ( char * ) calloc ( 1024 , sizeof(char) );

	strcpy ( query_buffer , "INSERT INTO Collection(Name, book_id) VALUES(" );

	strcat ( query_buffer , "\"" );
	strcat ( query_buffer , values[0] );
	strcat ( query_buffer , "\", " );

	strcat ( query_buffer , values[1] );
	strcat ( query_buffer , ")\0");

	if ( mysql_query ( mysql_connection , query_buffer ) )
	{
		perror ( "mysql_query" );
		return -1;
	}

	free ( query_buffer );

	return 0;
}

int
delete_collection ( MYSQL * mysql_connection , char ** values )
{
	char * query_buffer = ( char * ) calloc ( 1024 , sizeof(char) );

	strcpy ( query_buffer , "DELETE Collection FROM Collection WHERE Name = \"" );
	strcat ( query_buffer , values[0] );
	strcat ( query_buffer , "\"\0");

	if ( mysql_query ( mysql_connection , query_buffer ) )
	{
		perror ( "mysql_query" );
		return -1;
	}

	free ( query_buffer );

	return 0;
}

int
delete_book ( MYSQL * mysql_connection , char ** values )
{
	char * query_buffer = ( char * ) calloc ( 1024 , sizeof(char) );

	strcpy ( query_buffer , "DELETE Book FROM Book WHERE Filename = \"" );
	strcat ( query_buffer , values[0] );
	strcat ( query_buffer , "\" AND Title = \"");
	strcat ( query_buffer , values[1] );
	strcat ( query_buffer , "\"\0" );

	if ( mysql_query ( mysql_connection , query_buffer ) )
	{
		perror ( "mysql_query" );
		return -1;
	}

	free ( query_buffer );

	return 0;
}

int 
delete_collection_book ( MYSQL * mysql_connection , char ** values )
{
	char * query_buffer = ( char * ) calloc ( 1024 , sizeof(char) );

	strcpy ( query_buffer , "DELETE Collection FROM Collection INNER JOIN Book ON Collection.book_id = Book.id WHERE Collection.Name = \"" );
	strcat ( query_buffer , values[0] );
	strcat ( query_buffer , "\" AND Book.Title = \"" );
	strcat ( query_buffer , values[1] );
	strcat ( query_buffer , "\"" );

	if ( mysql_query ( mysql_connection , query_buffer ) )
	{
		perror ( "mysql_query" );
		return -1;
	}

	free ( query_buffer );

	return 0;
}

int 
main ( void )
{
	MYSQL * connection = init_db ();
	
	char ** values1 = ( char ** ) malloc ( sizeof(char *) * 7 );
	for ( int i = 0 ; i < 7 ; ++i )
		values1[i] = ( char * ) malloc ( sizeof(char) * 32 );

	strcpy ( values1[0] , "Title 1" );
	strcpy ( values1[1] , "Author 1" );
	strcpy ( values1[2] , "Publisher 1" );
	strcpy ( values1[3] , "Year 1" );
	strcpy ( values1[4] , "Pages 1" );
	strcpy ( values1[5] , "Filepath 1" );
	strcpy ( values1[6] , "Filename 1" );
	
	char ** values2 = ( char ** ) malloc ( sizeof(char *) * 7 );
	for ( int i = 0 ; i < 3 ; ++i )
		values2[i] = ( char * ) malloc ( sizeof(char) * 32 );

	strcpy ( values2[0] , "Collection 1" );
	strcpy ( values2[1] , "1" );

	insert_book ( connection , values1 );
	insert_collection ( connection , values2 );

	char ** values3 = ( char ** ) malloc ( sizeof(char *) * 1 );
	values3[0] = ( char * ) malloc ( sizeof(char) * 32);

	strcpy ( values3[0] , "Collection 1" );

	delete_collection ( connection , values3 );
	
	char ** values4 = ( char ** ) malloc ( sizeof(char *) * 7 );
	for ( int i = 0 ; i < 3 ; ++i )
		values4[i] = ( char * ) malloc ( sizeof(char) * 32 );

	strcpy ( values4[0] , "Collection 2" );
	strcpy ( values4[1] , "2" );

	char ** values5 = ( char ** ) malloc ( sizeof(char *) * 7 );
	for ( int i = 0 ; i < 7 ; ++i )
		values5[i] = ( char * ) malloc ( sizeof(char) * 32 );

	strcpy ( values5[0] , "Title 2" );
	strcpy ( values5[1] , "Author 2" );
	strcpy ( values5[2] , "Publisher 2" );
	strcpy ( values5[3] , "Year 2" );
	strcpy ( values5[4] , "Pages 2" );
	strcpy ( values5[5] , "Filepath 2" );
	strcpy ( values5[6] , "Filename 2" );
	
	insert_book ( connection , values5 );
	insert_collection ( connection , values4 );

	char ** values6 = ( char ** ) malloc ( sizeof(char *) * 2 );
	for ( int i = 0 ; i < 2 ; ++i )
		values6[i] = ( char * ) malloc ( sizeof(char) * 32 );

	strcpy ( values6[0] , "Collection 2" );
	strcpy ( values6[1] , "Title 2" );

	delete_collection_book ( connection , values6 );
	
	char ** values7 = ( char ** ) malloc ( sizeof(char *) * 7 );
	for ( int i = 0 ; i < 7 ; ++i )
		values7[i] = ( char * ) malloc ( sizeof(char) * 32 );

	strcpy ( values7[0] , "Title 3" );
	strcpy ( values7[1] , "Author 3" );
	strcpy ( values7[2] , "Publisher 3" );
	strcpy ( values7[3] , "Year 3" );
	strcpy ( values7[4] , "Pages 3" );
	strcpy ( values7[5] , "Filepath 3" );
	strcpy ( values7[6] , "Filename 3" );
	
	insert_book ( connection , values7 );

	char ** values8 = ( char ** ) malloc ( sizeof(char *) * 2 );
	for ( int i = 0 ; i < 2 ; ++i )
		values8[i] = ( char * ) malloc ( sizeof(char) * 32 );

	strcpy ( values8[0] , "Filename 3" );
	strcpy ( values8[1] , "Title 3" );

	//delete_book ( connection , values8 );

	free ( values1 );
	free ( values2 );
	free ( values3 );
	free ( values4 );
	free ( values5 );
	free ( values6 );
	free ( values7 );
	free ( values8 );

	mysql_close ( connection );

	return 0;
}
