test: sort_test.o db_utils.o test.o data_types.o
	gcc -Wall -Wextra -pedantic -I/usr/include/mysql -I/usr/include/mysql/mysql -L/usr/lib/ -lbsd -lmariadb -lncurses -lpthread -g -o test test.o data_types.o db_utils.o
	gcc -Wall -Wextra -pedantic -I/usr/include/mysql -I/usr/include/mysql/mysql -L/usr/lib/ -lbsd -lmariadb -lncurses -lpthread -g -o sort_test sort_test.o data_types.o db_utils.o
	rm *.o

test.o: test.c ../include/db_utils.h
	gcc -Wall -Wextra -pedantic -I/usr/include/mysql -I/usr/include/mysql/mysql -L/usr/lib/ -lbsd -lmariadb -lncurses -lpthread -g -c test.c

sort_test.o: sort_test.c
	gcc -Wall -Wextra -pedantic -I/usr/include/mysql -I/usr/include/mysql/mysql -L/usr/lib/ -lbsd -lmariadb -lncurses -lpthread -g -c sort_test.c

data_types.o: ../data_types.c ../include/data_types.h
	gcc -Wall -Wextra -pedantic -I/usr/include/mysql -I/usr/include/mysql/mysql -L/usr/lib/ -lbsd -lmariadb -lncurses -lpthread -g -c ../data_types.c

db_utils.o: ../db_utils.c ../include/db_utils.h
	gcc -Wall -Wextra -pedantic -I/usr/include/mysql -I/usr/include/mysql/mysql -L/usr/lib/ -lbsd -lmariadb -lncurses -lpthread -g -c ../db_utils.c
