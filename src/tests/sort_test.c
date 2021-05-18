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

int main ()
{
	book ** books = malloc ( sizeof(book) * 10 );
	for ( int i = 0 ; i < 10 ; ++i )
		books[i] = alloc_book();
	
	init_book ( 1 , "jsth" , "rahjstrkja" , "ieuhrs" , 2014 , 574 , "jsyody" , "uatjnaf" , books[0] );
	init_book ( 2 , "ajatb" , "utshbnaf" , "jtjsnba" , 2021 , 458 , "usykjsg" , "harbafv" , books[1] );
	init_book ( 3 , "hjstyjnaf" , "rjtgbfdfa" , "uoiahreib" , 1957 , 568 , "hjrikr" , "hjfiker" , books[2] );
	init_book ( 4 , "nifrkfrm" , "njurokfm" , "hjuvjfd" , 1956 , 947 , "aejah" , "tkisthba" , books[3] );
	init_book ( 5 , "jigj" , "jtijg" , "isthga" , 2016 , 376 , "ajhat" , "hthjsg" , books[4] );
	init_book ( 6 , "yraujat" , "auaga" , "uykg" , 1978 , 285 , "rustijst" , "ahafha" , books[5] );
	init_book ( 7 , "rustyjs" , "auatgaf" , "stjsg" , 2011 , 985 , "rsuts" , "aruatrg" , books[6] );
	init_book ( 8 , "aytshaf" , "rautrga" , "rautsjg" , 2018 , 857 , "eayutjsg" , "rytsjna" , books[7] );
	init_book ( 9 , "yieyhs" , "eryts" , "brsnys" , 1948 , 144 , "tjartba" , "agra" , books[8] );
	init_book ( 10 , "emarng" , "eakuyte" , "jtsgba" , 2003 , 536 , "yraga" , "garbr" , books[9] );

	printf ( "-BOOKS-\n" );

	printf ( "-Unsorted-\n" );
	for ( int i = 0 ; i < 10 ; ++i )
		printf ( "id: %ld ; title: %s ; author: %s ; publisher: %s ; year: %d ; pagecount: %d\n" , books[i]->id , books[i]->title , books[i]->author , books[i]->publisher , books[i]->year , books[i]->pagecount );

	sort_books_by_title ( books , 10 );
	
	printf ( "-Sorted by title-\n" );
	for ( int i = 0 ; i < 10 ; ++i )
		printf ( "id: %ld ; title: %s ; author: %s ; publisher: %s ; year: %d ; pagecount: %d\n" , books[i]->id , books[i]->title , books[i]->author , books[i]->publisher , books[i]->year , books[i]->pagecount );

	sort_books_by_author ( books , 10 );

	printf ( "-Sorted by author-\n" );
	for ( int i = 0 ; i < 10 ; ++i )
		printf ( "id: %ld ; title: %s ; author: %s ; publisher: %s ; year: %d ; pagecount: %d\n" , books[i]->id , books[i]->title , books[i]->author , books[i]->publisher , books[i]->year , books[i]->pagecount );

	sort_books_by_publisher ( books , 10 );
	
	printf ( "-Sorted by publisher-\n" );
	for ( int i = 0 ; i < 10 ; ++i )
		printf ( "id: %ld ; title: %s ; author: %s ; publisher: %s ; year: %d ; pagecount: %d\n" , books[i]->id , books[i]->title , books[i]->author , books[i]->publisher , books[i]->year , books[i]->pagecount );

	sort_books_by_year ( books , 10 );
	
	printf ( "-Sorted by year-\n" );
	for ( int i = 0 ; i < 10 ; ++i )
		printf ( "id: %ld ; title: %s ; author: %s ; publisher: %s ; year: %d ; pagecount: %d\n" , books[i]->id , books[i]->title , books[i]->author , books[i]->publisher , books[i]->year , books[i]->pagecount );

	sort_books_by_pagecount ( books , 10 );
	
	printf ( "-Sorted by pagecount-\n" );
	for ( int i = 0 ; i < 10 ; ++i )
		printf ( "id: %ld ; title: %s ; author: %s ; publisher: %s ; year: %d ; pagecount: %d\n" , books[i]->id , books[i]->title , books[i]->author , books[i]->publisher , books[i]->year , books[i]->pagecount );

	printf ( "-COLLECTIONS-\n" );

	collection ** collections = malloc ( sizeof(collections) * 4 );

	for ( int i = 0 ; i < 4 ; ++i )
		collections[i] = alloc_collection ();

	init_collection ( 1 , "thjsth" , collections[0] );
	init_collection ( 2 , "dabab" , collections[1] );
	init_collection ( 3 , "auyjn" , collections[2] );
	init_collection ( 4 , "igfa" , collections[3] );

	printf ( "-Unsorted-\n" );

	for ( int i = 0 ; i < 4 ; ++i )
		printf ( "id: %ld ; name: %s\n" , collections[i]->id , collections[i]->name );

	sort_collections ( collections , 4 );
	
	printf ( "-Sorted-\n" );
	for ( int i = 0 ; i < 4 ; ++i )
		printf ( "id: %ld ; name: %s\n" , collections[i]->id , collections[i]->name );

}
