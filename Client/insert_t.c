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

int insert_tuple(){
		int i =0;
		char name[BUFFER_LEN];
		char writer[BUFFER_LEN];
		char publisher[BUFFER_LEN];
		char count[BUFFER_LEN];

		for(i=0; i<25; i++){
			printf("                                                                          \n");
		}
		gotoxy(0,0);
		print_screen("insert_view.txt");
		
		gotoxy(25,4);
		scanf("%s",name);
		fflush(stdin);
		write(client_socket,name, strlen(name));
		gotoxy(25,6);	
		scanf("%s",writer);
		fflush(stdin);
		write(client_socket,writer,strlen(writer));
		gotoxy(25,8);
		scanf("%s",publisher);
		fflush(stdin);
		write(client_socket,publisher,strlen(publisher));
		gotoxy(25,10);
		scanf("%s",count);
		fflush(stdin);
		gotoxy(10,14);
		write(client_socket,count,strlen(count));
		getch();
        
        
	

	char insert[BUFFER_LEN] = "";
	int n = read(client_socket, insert, BUFFER_LEN);
    	buffer[n] = '\0';

	if(strcmp(insert,"noInsert") == 0){
		gotoxy(10,14);
		printf("도서 추가에 실패하였습니다.");
		getch();
	}else if(strcmp(insert,"success")==0){
		gotoxy(10,14);
		printf("도서 추가에 성공하였습니다.");
		getch();
	}
	

}
