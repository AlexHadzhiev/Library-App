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
#include "../include/ui.h"

int
main ( int argc , char * argv[] )
{
	initscr ();
	noecho ();
	cbreak ();
	refresh ();
	curs_set ( 0 );

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
	
	int max_x; int max_y;
	getmaxyx ( stdscr , max_y , max_x );

	WINDOW * collection_window_header = init_collection_window_header ( max_x );
	wrefresh ( collection_window_header );

	WINDOW * collection_window = init_collection_window ( max_y , max_x );
	wrefresh ( collection_window );

	int x = (max_x - (max_x / 6));
	
	WINDOW ** book_windows = init_book_windows ( max_y , max_x );
	for ( int i = 0 ; i < 5 ; ++i )
		wrefresh ( book_windows[i] );

	WINDOW ** book_window_headers = init_book_window_header ( x , max_x );
	for ( int i = 0 ; i < 5 ; ++i )
		wrefresh ( book_window_headers[i] );

	int book_windows_max_x; int book_windows_max_y;
	getmaxyx ( book_windows[1] , book_windows_max_y , book_windows_max_x );

	for ( int i = 0 ; i < 24 ; ++i )
	{
		for ( int j = 0 ; j < 5 ; ++j )
		{
			switch ( j )
			{
			case 0:
				  if ( ( int ) strlen ( books[i]->title ) > book_windows_max_x )
				  {
					  mvwprintw ( book_windows[j] , i + 1 , 1 , "%.*s" , 24 , books[i]->title );
					  wprintw ( book_windows[j] , "..." );
				  }
				  else
				  {
					  mvwprintw ( book_windows[j] , i + 1 , 1 , "%s" , books[i]->title );
				  }
				  break;
			case 1:
				  if ( ( int ) strlen ( books[i]->author ) > book_windows_max_x )
				  {
					  mvwprintw ( book_windows[j] , i + 1 , 1 , "%.*s" , 24 , books[i]->author );
					  wprintw ( book_windows[j] , "..." );
				  }
				  else
				  {
					  mvwprintw ( book_windows[j] , i + 1 , 1 , "%s" , books[i]->author );
				  }
				  break;
			case 2:
				  if ( ( int ) strlen ( books[i]->publisher ) > book_windows_max_x )
				  {
					  mvwprintw ( book_windows[j] , i + 1 , 1 , "%.*s" , 24 , books[i]->publisher );
					  wprintw ( book_windows[j] , "..." );
				  }
				  else
				  {
					  mvwprintw ( book_windows[j] , i + 1 , 1 , "%s" , books[i]->publisher );
				  }
				  break;
			case 3:
				  mvwprintw ( book_windows[j] , i + 1 , 1 , "%d" , books[i]->year );
				  break;
			case 4:
				  mvwprintw ( book_windows[j] , i + 1 , 1 , "%d" , books[i]->pagecount );
				  break;
			}
		}
	}

	for ( int i = 0 ; i < 24 ; ++i )
		free_book ( books[i] );
	
	for ( int i = 0 ; i < 5 ; ++i )
		wrefresh ( book_windows[i] );

	free ( books );

	mysql_free_result ( result );

	mysql_close ( connection );
	
	getch ();

	endwin ();

	return 0;
}
