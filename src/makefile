ui: ui.o
	gcc -Wall -Wextra -pedantic -I/usr/include/mysql -I/usr/include/mysql/mysql -L/usr/lib/ -lbsd -lmariadb -lncurses -lpthread -g -o ui ui.o
	rm *.o
ui.o: ui.c include/ui.h
	gcc -Wall -Wextra -pedantic -I/usr/include/mysql -I/usr/include/mysql/mysql -L/usr/lib/ -lbsd -lmariadb -lncurses -lpthread -g -c ui.c

