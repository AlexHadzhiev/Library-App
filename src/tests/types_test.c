#include <bsd/stdlib.h>
#include <limits.h>
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
#include "../include/data_types.h"

int
main ( int argc , char * argv[] )
{
	MYSQL * connection = mysql_init ( NULL );

	if ( (mysql_real_connect ( connection , "localhost" , "thelichknight" , "12345678" , NULL , 0 , NULL , 0 )) == NULL )
	{
		perror ( "mysql_real_connect" );

		mysql_close ( connection );

		return -1;
	}

	if ( mysql_select_db ( connection , "Library_App" ) )
	{
		perror ( "mysql_select_db" );

		mysql_close ( connection );

		return -1;

	}

	if ( mysql_query ( connection , "SELECT * FROM Book" ) )
	{
		perror ( "mysql_query" );

		mysql_close ( connection );

		return -1;
	}

	MYSQL_RES * result = mysql_store_result ( connection );

	book ** books = malloc ( sizeof(book *) * 24 );

	for ( int i = 0 ; i < 24 ; ++i )
		books[i] = alloc_book ();
	
	for ( int i = 0 ; i < 24 ; ++i )
		fill_book_from_db ( result , books[i] );

	printf ( "-UNSORTED-\n" );

	for ( int i = 0 ; i < 24 ; ++i )
		printf ( "id: %2ld ; title: %60s ; author: %30s ; year: %4d ; pagecount: %5d\n" , books[i]->id , books[i]->title , books[i]->author , books[i]->year , books[i]->pagecount );
	
	sort_books_by_title ( books , 24 );
	
	printf ( "-SORTED-\n" );

	for ( int i = 0 ; i < 24 ; ++i )
		printf ( "id: %2ld ; title: %50s ; author: %30s ; year: %4d ; pagecount: %5d\n" , books[i]->id , books[i]->title , books[i]->author , books[i]->year , books[i]->pagecount );

	for ( int i = 0 ; i < 24 ; ++i )
		free_book ( books[i] );

	free ( books );

	mysql_free_result ( result );

	mysql_close ( connection );
	
	return 0;
}
