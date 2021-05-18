#include "include/data_types.h"
#include <stdlib.h>
#include <bsd/stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <mysql.h>

int 
cmpstr ( const char * a , const char * b )
{
	int weight = 0;
	
	do
	{
		if ( *a != *b )
		{
			if ( !(isalpha ( *a ) && isalpha ( *b )) )
			{
				if ( (isalpha ( *a ) || isalpha ( *b )) )
				{
					return isalpha ( *a ) - isalpha ( *b );
				}
				return *a - *b;
			}
			if ( tolower ( *a ) != tolower( *b ) )
				return tolower ( *a ) - tolower ( *b );
			if ( weight == 0 )
				weight = isupper ( *a ) - isupper ( *b );
		}

		++a;
		++b;
	} while ( *a && *b );

	if ( *a == *b )
		return weight;
	return !*b - !*a;
}

int
cmpint ( int a , int b )
{
	return ( a > b ) - ( a < b );
}

void
swap_book ( book * b1 , book * b2 )
{
	book tmp = *b1;
	*b1 = *b2;
	*b2 = tmp;
}

void
swap_collection ( collection * c1 , collection * c2 )
{
	collection tmp = *c1;
	*c1 = *c2;
	*c2 = tmp;
}

book *
alloc_book ()
{
	book * b;

	b = ( book * ) malloc ( sizeof(book) + 1 );
	b->id = 0;
	b->title = ( char * ) calloc ( 1024 , sizeof(char) );
	b->author = ( char * ) calloc ( 1024 , sizeof(char) );
	b->publisher = ( char * ) calloc ( 1024 , sizeof(char) );
	b->year = 0;
	b->pagecount = 0;
	b->filepath = ( char * ) calloc ( 1024 , sizeof(char) );
	b->filename = ( char * ) calloc ( 1024 , sizeof(char) );

	return b;
}

void 
init_book ( long id , char * title , char * author , char * publisher , int year , int pagecount , char * filepath , char * filename , book * b )
{
	b->id = id;
	strcpy ( b->title , title ); strcat ( b->title , "\0" );
	strcpy ( b->author , author ); strcat ( b->author , "\0" );
	strcpy ( b->publisher , publisher ); strcat ( b->publisher , "\0" );
	b->year = year;
	b->pagecount = pagecount;
	strcpy ( b->filepath , filepath ); strcat ( b->filepath , "\0" );
	strcpy ( b->filename , filename ); strcat ( b->filename , "\0" );
}

void
fill_book_from_db ( MYSQL_RES * result , book * b )
{
	MYSQL_ROW row = mysql_fetch_row ( result );
	const char * errstr;

	init_book ( strtonum ( row[0] , 0 , 999999 , &errstr ) , row[1] , row[2] , row[3] , strtonum ( row[4] , 0 , 999999 , &errstr ) , strtonum ( row[5] , 0 , 999999 , &errstr ) , row[6] , row[7] , b );
}

void
free_book ( book * b )
{
	free ( b->filename );
	free ( b->filepath );
	free ( b->publisher );
	free ( b->author );
	free ( b->title );
	free ( b );
}

collection *
alloc_collection ()
{
	collection * c;

	c = ( collection * ) malloc ( sizeof(collection) + 1 );
	c->id = 0;
	c->name = ( char * ) calloc ( 1024 , sizeof(char) );

	return c;
}

void 
init_collection ( long id , char * name , collection * c )
{
	c->id = id;
	strcpy ( c->name , name );
}

void
fill_collection_from_db ( MYSQL_RES * result , collection * c )
{
	MYSQL_ROW row = mysql_fetch_row ( result );
	const char * errstr;

	init_collection ( strtonum ( row[0] , 0 , 999999 , &errstr ) , row[1] , c );
}

void
free_collection ( collection * c )
{
	free ( c->name );
	free ( c );
}

void 
sort_books_by_title ( book ** books , int number_of_books )
{
	for ( int i = 0 ; i < (number_of_books - 1) ; ++i )
		for ( int j = 0 ; j < ( number_of_books - i - 1 ) ; ++j )
			if ( cmpstr ( books[j]->title , books[j + 1]->title ) > 0 )
				swap_book ( books[j] , books[j + 1] );
}

void 
sort_books_by_author ( book ** books , int number_of_books )
{
	for ( int i = 0 ; i < (number_of_books - 1) ; ++i )
		for ( int j = 0 ; j < ( number_of_books - i - 1 ) ; ++j )
			if ( cmpstr ( books[j]->author , books[j + 1]->author ) > 0 )
				swap_book ( books[j] , books[j + 1] );
}

void 
sort_books_by_publisher ( book ** books , int number_of_books )
{
	for ( int i = 0 ; i < (number_of_books - 1) ; ++i )
		for ( int j = 0 ; j < ( number_of_books - i - 1 ) ; ++j )
			if ( cmpstr ( books[j]->publisher , books[j + 1]->publisher ) > 0 )
				swap_book ( books[j] , books[j + 1] );
}

void 
sort_books_by_year ( book ** books , int number_of_books )
{
	for ( int i = 0 ; i < (number_of_books - 1) ; ++i )
		for ( int j = 0 ; j < ( number_of_books - i - 1 ) ; ++j )
			if ( cmpint ( books[j]->year , books[j + 1]->year ) > 0 )
				swap_book ( books[j] , books[j + 1] );
}

void 
sort_books_by_pagecount ( book ** books , int number_of_books )
{
	for ( int i = 0 ; i < (number_of_books - 1) ; ++i )
		for ( int j = 0 ; j < ( number_of_books - i - 1 ) ; ++j )
			if ( cmpint ( books[j]->pagecount , books[j + 1]->pagecount ) > 0 )
				swap_book ( books[j] , books[j + 1] );
}

void 
sort_collections ( collection ** collections , int number_of_collections )
{
	for ( int i = 0 ; i < (number_of_collections - 1) ; ++i )
		for ( int j = 0 ; j < ( number_of_collections - i - 1 ) ; ++j )
			if ( cmpstr ( collections[j]->name , collections[j + 1]->name ) > 0 )
				swap_collection ( collections[j] , collections[j + 1] );
}

