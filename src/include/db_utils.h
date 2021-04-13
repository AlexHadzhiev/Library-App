#include <mysql.h>

static int default_collection_set;

MYSQL *
init_db ( char ** split_init_query_buffer );

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
