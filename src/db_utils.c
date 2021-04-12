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
	int fd = open ( "init_query.txt" , O_RDONLY );
	if ( fd < 0 )
	{
		perror ( "open" );
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
			perror ( "read" );
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
		perror ( "close" );
		return ( char * ) NULL;
	}

	return init_query_buffer;
}

char **
split_init_query ( char * init_query_buffer )
{
	char ** split_init_query_buffer = ( char ** ) calloc ( 3 , sizeof(char *) );
	for ( int i = 0 ; i < 3 ; ++i )
		split_init_query_buffer[i] = ( char * ) calloc ( 1024 , sizeof(char) );

	split_init_query_buffer[0] = strtok ( init_query_buffer , ";" );
	split_init_query_buffer[1] = strtok ( NULL , ";" );
	split_init_query_buffer[2] = strtok ( NULL , ";" );

	return split_init_query_buffer;
}
