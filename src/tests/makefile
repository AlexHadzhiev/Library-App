PREFIX = gcc

CFLAGS = -Wall -Wextra -pedantic -I/usr/include/mysql -I/usr/include/mysql/mysql -L/usr/lib/ -lbsd -lmariadb -lncurses -lpthread -g

SRC_DIR = ../
HEAD_DIR = ../include

test: sort_test.o db_utils.o test.o data_types.o
	$(PREFIX) $(CFLAGS) -o test test.o data_types.o db_utils.o
	$(PREFIX) $(CFLAGS) -o sort_test sort_test.o data_types.o db_utils.o
	rm *.o

test.o: test.c $(HEAD_DIR)/db_utils.h
	$(PREFIX) $(CFLAGS) -c test.c

sort_test.o: sort_test.c
	$(PREFIX) $(CFLAGS) -c sort_test.c

data_types.o: $(SRC_DIR)/data_types.c $(HEAD_DIR)/data_types.h
	$(PREFIX) $(CFLAGS) -c $(SRC_DIR)/data_types.c

db_utils.o: $(SRC_DIR)/db_utils.c $(HEAD_DIR)/db_utils.h
	$(PREFIX) $(CFLAGS) -c $(SRC_DIR)/db_utils.c
