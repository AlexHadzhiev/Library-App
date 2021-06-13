PREFIX = gcc

CFLAGS = -Wall -Wextra -pedantic -I/usr/include/mysql -I/usr/include/mysql/mysql -L/usr/lib/ -lbsd -lmariadb -lncurses -lpthread -g

SRC_DIR = ../
INCL_DIR = ../include

test: sort_test.o types_test.o db_utils.o test.o data_types.o
	$(PREFIX) $(CFLAGS) -o test test.o data_types.o db_utils.o
	$(PREFIX) $(CFLAGS) -o sort_test sort_test.o data_types.o db_utils.o
	$(PREFIX) $(CFLAGS) -o types_test types_test.o data_types.o db_utils.o
	rm *.o

test.o: test.c $(INCL_DIR)/db_utils.h
	$(PREFIX) $(CFLAGS) -c test.c

sort_test.o: sort_test.c
	$(PREFIX) $(CFLAGS) -c sort_test.c

types_test.o: types_test.c
	$(PREFIX) $(CFLAGS) -c types_test.c

data_types.o: $(SRC_DIR)/data_types.c $(INCL_DIR)/data_types.h
	$(PREFIX) $(CFLAGS) -c $(SRC_DIR)/data_types.c

db_utils.o: $(SRC_DIR)/db_utils.c $(INCL_DIR)/db_utils.h
	$(PREFIX) $(CFLAGS) -c $(SRC_DIR)/db_utils.c
