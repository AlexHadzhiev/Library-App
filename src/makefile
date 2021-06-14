PREFIX = gcc

CFLAGS = -Wall -Wextra -pedantic -I/usr/include/mysql -I/usr/include/mysql/mysql -L/usr/lib/ -lbsd -lmariadb -lncurses -lpthread -g

SRC_DIR = ./
INCL_DIR = ./include

ui: ui.o db_utils.o data_types.o
	$(PREFIX) $(CFLAGS) -o ui ui.o db_utils.o data_types.o
	rm *.o
ui.o: $(SRC_DIR)/ui.c $(INCL_DIR)/ui.h
	$(PREFIX) $(CFLAGS) -c ui.c
db_utils.o: $(SRC_DIR)/db_utils.c $(INCL_DIR)/db_utils.h
	$(PREFIX) $(CFLAGS) -c db_utils.c
data_types.o: $(SRC_DIR)/data_types.c $(INCL_DIR)/data_types.h
	$(PREFIX) $(CFLAGS) -c data_types.c
