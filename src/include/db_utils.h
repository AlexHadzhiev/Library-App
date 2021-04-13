#ifndef DB_UTILS_H
#define DB_UTILS_H

#include <mysql.h>

static int default_collection_set = 0;

MYSQL *
init_db ();

int
insert_book ( MYSQL * connection , char ** values );

int
insert_collection ( MYSQL * connection , char ** values );

int
insert_book_into_collection ( MYSQL * connection , char ** values );

int
delete_book ( MYSQL * connection , char ** values );

int
delete_collection ( MYSQL * connection , char ** values );

int
delete_book_from_collection ( MYSQL * connection , char ** values );

#endif
