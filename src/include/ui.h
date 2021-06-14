#ifndef UI_H
#define UI_H

#include <ncurses.h>

WINDOW *
init_collection_header ( int max_x , int start_x );

WINDOW *
init_collection_window ( int max_y , int max_x );

WINDOW **
init_book_window_header ( int max_x , int start_x );

WINDOW *
init_book_window ( int max_y , int max_x );

#endif
