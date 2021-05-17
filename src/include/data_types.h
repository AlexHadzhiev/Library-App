#ifndef DATA_TYPES_H
#define DATA_TYPES_H

typedef
struct
{
	long id;
	char * title;
	char * author;
	char * publisher;
	int year;
	int pagecount;
	char * filepath;
	char * filename;
} book;

typedef
struct
{
	long id;
	char * name;
} collection;

int
cmpstr ( const char * a , const char * b );

int
cmpint ( int a , int b );

void
swap_book ( book * b1 , book * b2 );

void
swap_collection ( collection * c1 , collection * c2 );

book *
alloc_book ();

void 
init_book ( long id , char * title , char * author , char * publisher , int year , int pagecount , char * filepath , char * filename , book * b );

void
free_book ();

collection * 
alloc_collection ();

void 
init_collection ( long id , char * name , collection * c );

void
free_collection ();

void 
sort_books_by_title ( book ** books , int number_of_books );

void 
sort_books_by_author ( book ** books , int number_of_books );

void 
sort_books_by_publisher ( book ** books , int number_of_books );

void 
sort_books_by_year ( book ** books , int number_of_books );

void 
sort_books_by_pagecount ( book ** books , int number_of_books );

void 
sort_collections ( collection ** collections , int number_of_collections );

#endif
