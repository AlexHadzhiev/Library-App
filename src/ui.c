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

#include "include/ui.h"

void
center ( int max_x , const char * str , WINDOW * win )
{
	int len = strlen ( str ) - 1;
	int pad = ( len >= max_x ) ? 0 : (( max_x - len ) / 2);
	mvwprintw ( win , 1 , 1 , "%*.*s%s" , pad , pad , " " , str );
}

WINDOW *
init_collection_window_header ( int max_x )
{
	WINDOW * collection_window_header;

	collection_window_header = newwin ( 3 , ( max_x / 6 ) , 0 , 0 );
    wborder ( collection_window_header , ACS_VLINE , ACS_VLINE , ACS_HLINE , ACS_HLINE , ACS_ULCORNER , ACS_URCORNER , ACS_LLCORNER , ACS_LRCORNER );

	center ( (max_x / 6) - 2 , "COLLECTIONS" , collection_window_header );

	return collection_window_header;
}

WINDOW *
init_collection_window ( int max_y , int max_x )
{
	WINDOW * collection_window;

	collection_window = newwin ( ( max_y - 3 ) , ( max_x / 6 ) , 3 , 0 );
    wborder ( collection_window , ACS_VLINE , ACS_VLINE , ACS_HLINE , ACS_HLINE , ACS_ULCORNER , ACS_URCORNER , ACS_LLCORNER , ACS_LRCORNER );

	return collection_window;
}

WINDOW **
init_book_window_header ( int max_x , int start_x )
{
	WINDOW ** book_window_headers = malloc ( sizeof(WINDOW *) * 5 );

	int part = max_x / 5;

	for ( int i = 1 ; i <= 5 ; ++i )
		book_window_headers[i - 1] = newwin ( 3 , part , 0 , ((start_x / 6) + (part * ( i - 1 ))) );

	wborder ( book_window_headers[1] , ACS_VLINE , 0x20 , ACS_HLINE , ACS_HLINE , ACS_TTEE , ACS_HLINE , ACS_BTEE , ACS_HLINE );
	wborder ( book_window_headers[2] , ACS_VLINE , 0x20 , ACS_HLINE , ACS_HLINE , ACS_TTEE , ACS_HLINE , ACS_BTEE , ACS_HLINE );
	wborder ( book_window_headers[3] , ACS_VLINE , 0x20 , ACS_HLINE , ACS_HLINE , ACS_TTEE , ACS_HLINE , ACS_BTEE , ACS_HLINE );
	wborder ( book_window_headers[0] , ACS_VLINE , 0x20 , ACS_HLINE , ACS_HLINE , ACS_ULCORNER , ACS_HLINE , ACS_LLCORNER , ACS_HLINE );
	wborder ( book_window_headers[4] , ACS_VLINE , ACS_VLINE , ACS_HLINE , ACS_HLINE , ACS_TTEE , ACS_URCORNER , ACS_BTEE , ACS_LRCORNER );

	center ( part - 2 , "TITLE" , book_window_headers[0] );
	center ( part - 2 , "AUTHOR" , book_window_headers[1] );
	center ( part - 2 , "PUBLISHER" , book_window_headers[2] );
	center ( part - 2 , "YEAR" , book_window_headers[3] );
	center ( part - 2 , "PAGECOUNT" , book_window_headers[4] );

	return book_window_headers;
}

WINDOW **
init_book_windows ( int max_y , int max_x )
{
	WINDOW ** book_windows = malloc ( sizeof(WINDOW *) * 5 );

	int part = ( ( max_x - (max_x / 6) ) / 5 );

	for ( int i = 1 ; i <= 5 ; ++i )
		book_windows[i - 1] = newwin ( max_y - 3 , part , 3 , (max_x / 6 + (part * (i - 1))) );

	wborder ( book_windows[1] , ACS_VLINE , 0x20 , ACS_HLINE , ACS_HLINE , ACS_TTEE , ACS_HLINE , ACS_BTEE , ACS_HLINE );
	wborder ( book_windows[2] , ACS_VLINE , 0x20 , ACS_HLINE , ACS_HLINE , ACS_TTEE , ACS_HLINE , ACS_BTEE , ACS_HLINE );
	wborder ( book_windows[3] , ACS_VLINE , 0x20 , ACS_HLINE , ACS_HLINE , ACS_TTEE , ACS_HLINE , ACS_BTEE , ACS_HLINE );
	wborder ( book_windows[0] , ACS_VLINE , 0x20 , ACS_HLINE , ACS_HLINE , ACS_ULCORNER , ACS_HLINE , ACS_LLCORNER , ACS_HLINE );
	wborder ( book_windows[4] , ACS_VLINE , ACS_VLINE , ACS_HLINE , ACS_HLINE , ACS_TTEE , ACS_URCORNER , ACS_BTEE , ACS_LRCORNER );
	
	return book_windows;
}
