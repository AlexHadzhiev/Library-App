test: db_utils.o test.o
	gcc -Wall -Wextra -pedantic -I/usr/include/mysql -I/usr/include/mysql/mysql -L/usr/lib/ -lmariadb -lncurses -lpthread -g -o test test.o db_utils.o
	rm *.o

test.o: test.c ../include/db_utils.h
	gcc -Wall -Wextra -pedantic -I/usr/include/mysql -I/usr/include/mysql/mysql -L/usr/lib/ -lmariadb -lncurses -lpthread -g -c test.c

db_utils.o: ../db_utils.c ../include/db_utils.h
	gcc -Wall -Wextra -pedantic -I/usr/include/mysql -I/usr/include/mysql/mysql -L/usr/lib/ -lmariadb -lncurses -lpthread -g -c ../db_utils.c
