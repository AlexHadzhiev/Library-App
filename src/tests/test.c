#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../include/db_utils.h"

char *
read_from_file ( char * filename )
{
	int fd = open ( filename , O_RDONLY );
	if ( fd < 0 )
	{
		perror ( "open [read_from_file]" );
		return ( char * ) NULL;
	}

	size_t size = 1024;
	size_t offset = 0;
	ssize_t bytes_read;

	char * buffer = ( char * ) calloc ( (size * 2) , sizeof(char) );

	while ( (bytes_read = read ( fd , (buffer + offset) , (ssize_t) 512 )) != 0 )
	{
		if ( bytes_read < 0 )
		{
			perror ( "read [read_from_file]" );
			free ( buffer );
			return ( char * ) NULL;
		}

		offset += bytes_read;

		if ( (offset + 512) > size )
		{
			size *= 2;
			buffer = ( char * ) realloc ( buffer , (size * 2) );
		}
	}

	if ( close ( fd ) < 0 )
	{
		perror ( "close [read_from_file]" );
		free ( buffer );
		return ( char * ) NULL;
	}

	return buffer;
}

char **
split_information ( char * buffer )
{
	char * buffer_backup = ( char * ) calloc ( 2048 , sizeof(char) );
	strcpy ( buffer_backup , buffer );

	int len = ( int ) strlen ( buffer );
	
	int num_of_lines = 0;

	for ( int i = 0 ; i < len ; ++i )
		if ( buffer[i] == '\n' )
			num_of_lines++;

	char ** split_info = ( char ** ) calloc ( num_of_lines , sizeof(char *) );
	for ( int i = 0 ; i < num_of_lines ; ++i )
		split_info[i] = ( char * ) calloc ( 1024 , sizeof(char) );

	char * line = strtok ( buffer_backup , "\n" );
	for ( int i = 0 ; (i < num_of_lines) && (line != NULL) ; ++i )
	{
		strcpy ( split_info[i] , line );
		line = strtok ( NULL , "\n" );
	}

	free ( line );
	free ( buffer_backup );

	return split_info;
}

int
main ( void )
{
	char * titles = read_from_file ( "titles.txt" );
	char * authors = read_from_file ( "authors.txt" );
	char * publishers = read_from_file ( "publishers.txt" );
	char * years = read_from_file ( "years.txt" );
	char * pagecounts = read_from_file ( "pagecount.txt" );
	char * filenames = read_from_file ( "filenames.txt" );
	char * colls = read_from_file ( "collections.txt" );

	MYSQL * connection = init_db ();
	
	char ** titles_list = split_information ( titles );
	char ** authors_list = split_information ( authors );
	char ** publishers_list = split_information ( publishers );
	char ** years_list = split_information ( years );
	char ** pagecount_list = split_information ( pagecounts );
	char ** filenames_list = split_information ( filenames );
	char ** collections_list = split_information ( colls );

	char *** books = ( char *** ) calloc ( 24 , sizeof(char **) );
	for ( int i = 0 ; i < 24 ; ++i )
	{
		books[i] = ( char ** ) calloc ( 7 , sizeof(char **) );
		for ( int j = 0 ; j < 7 ; ++j )
		{
			books[i][j] = ( char * ) calloc ( 1024 , sizeof(char) );
		}
	}

	for ( int i = 0 ; i < 24 ; ++i )
	{
		strcpy ( books[i][0] , titles_list[i]);
		strcpy ( books[i][1] , authors_list[i] );
		strcpy ( books[i][2] , publishers_list[i] );
		strcpy ( books[i][3] , years_list[i] );
		strcpy ( books[i][4] , pagecount_list[i] );
		strcpy ( books[i][5] , "/home/thelichknight/Books" );
		strcpy ( books[i][6] , filenames_list[i] );
	}

	for ( int i = 0 ; i < 24 ; ++i )
		insert_book ( connection , books[i] );

	char *** collections = ( char *** ) calloc ( 3 , sizeof(char **) );
	for ( int i = 0 ; i < 3 ; ++i )
	{
		collections[i] = ( char ** ) calloc ( 1 , sizeof(char *) );
		for ( int j = 0 ; j < 1 ; ++j )
		{
			collections[i][j] = ( char * ) calloc ( 1024 , sizeof(char) );
		}
	}

	for ( int i = 0 ; i < 3 ; ++i )
	{
		strcpy ( collections[i][0] , collections_list[i] );
	}

	for ( int i = 0 ; i < 3 ; ++i )
		insert_collection ( connection , collections[i] );

	free ( titles );
	free ( authors );
	free ( publishers );
	free ( years );
	free ( pagecounts );
	free ( filenames );
	free ( colls );

	for ( int i = 0 ; i < 24 ; ++i )
	{
		free ( titles_list[i] );
		free ( authors_list[i] );
		free ( publishers_list[i] );
		free ( years_list[i] );
		free ( pagecount_list[i] );
		free ( filenames_list[i] );
	}

	for ( int i = 0 ; i < 3 ; ++i )
	{
		free ( collections_list[i] );
	}

	for ( int i = 0 ; i < 24 ; ++i )
	{
		for ( int j = 0 ; j < 7 ; ++j )
		{
			free ( books[i][j] );
		}
		free ( books[i] );
	}

	for ( int i = 0 ; i < 3 ; ++i )
	{
		free ( collections[i][0] );
		free ( collections[i] );
	}

	free ( titles_list );
	free ( authors_list );
	free ( publishers_list );
	free ( years_list );
	free ( pagecount_list );
	free ( filenames_list );
	free ( collections_list );

	free ( books );
	free ( collections );

	mysql_close ( connection );

	return 0;
}
