#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <termio.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
 
#define PORT 10000
#define BUFFER_LEN 1000
#define CHAT_SIZE 1024
#define BUFF_SIZE 1024
#define LISTEN_QUEUE_SIZE 5
 
char* b[100][100];
int client_socket;
struct sockaddr_in client_addr;
char buff[BUFF_SIZE+5];
char buffer[BUFFER_LEN];
char s[BUFFER_LEN];

int getch(void);
void print_screen(char fname[]);
void gotoxy(int x, int y);

void login()
{
		char id[BUFFER_LEN] = "";
		char pwd[BUFFER_LEN] = "";
		int i =0;
		
		for(i=0; i<25; i++){
		printf("                                                                          \n");
		}
		gotoxy(0,0);
		print_screen("login_view.txt");
		gotoxy(16,4);
		scanf("%s",id);
		fflush(stdin);
		write(client_socket, id, strlen(id));

		gotoxy(16,5);
		scanf("%s",pwd);
		fflush(stdin);
		getch();
		write(client_socket, pwd, strlen(pwd));

		s[0] = '\0';
		int n = read(client_socket, s, BUFFER_LEN);
    		buffer[n] = '\0';
}

