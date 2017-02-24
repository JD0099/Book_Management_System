CFLAGS = -I/usr/include/mysql/
LIBS = -L/usr/lib/mysql -lmysqlclient

server : server_main.o search.o insert.o delete.o login.o connect.o
	gcc -o server server_main.o search.o insert.o delete.o login.o connect.o $(LIBS) -lz -lm
search.o : search.c
	gcc -c search.c $(CFLAGS)
insert.o : insert.c
	gcc -c insert.c $(CFLAGS)
delete.o : delete.c
	gcc -c delete.c $(CFLAGS)
login.o : login.c
	gcc -c login.c $(CFLAGS)
connect.o : connect.c
	gcc -c connect.c $(CFLAGS)
server_main.o : server_main.c
	gcc -c server_main.c $(CFLAGS)
clean :
	rm -f server server_main.o search.o insert.o delete.o login.o connect.o

