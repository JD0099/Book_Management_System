client : getch.o print_s.o gotoxy.o select_t.o insert_t.o delete_t.o login_t.o client_main.o
	gcc -o client getch.o print_s.o gotoxy.o select_t.o insert_t.o delete_t.o login_t.o client_main.o
getch.o : getch.c
	gcc -c getch.c
print_s.o : print_s.c
	gcc -c print_s.c
gotoxy.o : gotoxy.c
	gcc -c gotoxy.c
select_t.o : select_t.c
	gcc -c select_t.c
insert_t.o : insert_t.c
	gcc -c insert_t.c
delete_t.o : delete_t.c
	gcc -c delete_t.c
login_t.o : login_t.c
	gcc -c login_t.c
client_main.o : client_main.c
	gcc -c client_main.c
clean :
	rm -f client getch.o print_s.o gotoxy.o select_t.o insert_t.o delete_t.o login_t.o client_main.o

