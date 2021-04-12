#ifndef DB_FUNC_H
#define DB_FUNC_H

#include <mysql.h>

static int default_collection_created;

MYSQL *
init_db ( char ** init_query );

int
insert_book ( MYSQL * mysql_connection , char ** values );

int
insert_collection ( MYSQL * mysql_connection , char ** values );

int
update_book_title ( MYSQL * mysql_connection , char ** values );

int
update_book_author ( MYSQL * mysql_connection , char ** values );

int
update_book_publisher ( MYSQL * mysql_connection , char ** values );

int
update_book_year ( MYSQL * mysql_connection , char ** values );

int
update_book_filepath ( MYSQL * mysql_connection , char ** values );

int
update_book_filename ( MYSQL * mysql_connection , char ** values );

int
update_book_pagecount ( MYSQL * mysql_connection , char ** values );

int
update_collection_name ( MYSQL * mysql_connection , char ** values );

int
update_collection_bookid ( MYSQL * mysql_connection , char ** values );

int
delete_collection_book ( MYSQL * mysql_connection , char ** values );

int
delete_collection ( MYSQL * mysql_connection , char ** values );

int
delete_book ( MYSQL * mysql_connection , char ** values );

#endif
