PREFIX = gcc

CFLAGS = -Wall -Wextra -pedantic -I/usr/include/mysql -I/usr/include/mysql/mysql -L/usr/lib/ -lbsd -lmariadb -lncurses -lpthread -g

SRC_DIR = ../
INCL_DIR = ../include

test: ui_test.o db_test.o sort_test.o types_test.o db_utils.o data_types.o ui.o
	$(PREFIX) $(CFLAGS) -o db_test db_test.o data_types.o db_utils.o
	$(PREFIX) $(CFLAGS) -o sort_test sort_test.o data_types.o db_utils.o
	$(PREFIX) $(CFLAGS) -o types_test types_test.o data_types.o db_utils.o
	$(PREFIX) $(CFLAGS) -o ui_test ui_test.o data_types.o db_utils.o ui.o
	rm *.o

db_test.o: db_test.c $(INCL_DIR)/db_utils.h
	$(PREFIX) $(CFLAGS) -c db_test.c

sort_test.o: sort_test.c
	$(PREFIX) $(CFLAGS) -c sort_test.c

types_test.o: types_test.c
	$(PREFIX) $(CFLAGS) -c types_test.c

ui_test.o: ui_test.c
	$(PREFIX) $(CFLAGS) -c ui_test.c

data_types.o: $(SRC_DIR)/data_types.c $(INCL_DIR)/data_types.h
	$(PREFIX) $(CFLAGS) -c $(SRC_DIR)/data_types.c

db_utils.o: $(SRC_DIR)/db_utils.c $(INCL_DIR)/db_utils.h
	$(PREFIX) $(CFLAGS) -c $(SRC_DIR)/db_utils.c

ui.o: $(SRC_DIR)/ui.c $(INCL_DIR)/ui.h
	$(PREFIX) $(CFLAGS) -c $(SRC_DIR)/ui.c
