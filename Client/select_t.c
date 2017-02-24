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
char a[BUFFER_LEN] = "";

int getch(void);
void print_screen(char fname[]);
void gotoxy(int x, int y);

void select_tuple()
{
		int x,y,i;
		for(i=0; i<25; i++){
		printf("                                                                          \n");
		}
		gotoxy(0,0);
		print_screen("select_view.txt");
	
		gotoxy(25,4);
	scanf("%s",a);
		fflush(stdin);
	getch();
        
        write(client_socket, a, strlen(a));
	
	char s[BUFFER_LEN] = "";
	int n = read(client_socket, s, BUFFER_LEN);
    	buffer[n] = '\0';
        
	if(strcmp(s,"empty") == 0){
		gotoxy(6,14);
		printf("검색하신 책이 없습니다.");
	}
	else{
		int c =0;
		int to =0;
		char* token = NULL;
		token = strtok(s,"/");
		char *name[100][100] = {0,};
  	
             while(token != NULL){
		
		name[c][to] = token;
		token = strtok(NULL,"/");
		to++;

		if(to>3){
			c++;
			to=0;
		}
	     }
		x = 1;
		y = 9;
		
		int d = 0;

		for(d;d<c;d++){
			gotoxy(x,y);
			printf("| %-18s | %-10s | %-15s | %-2s |",name[d][0],name[d][1],name[d][2],name[d][3]);
			y++;
		if(y == 13){
			printf("\n        아무키나 입력하세요.");
			getch();
			gotoxy(1,9);
          		 for(i= 0; i < 5; i++){
			printf("                                                          \n");
	  			 }
			y = 9;
			}
		}
	}
	buffer[0]='\0';
	getch();
}

