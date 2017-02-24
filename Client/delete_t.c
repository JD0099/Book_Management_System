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

void delete_tuple(){
	int i =0;
	char dele[BUFFER_LEN];
	for(i=0; i<25; i++){
			printf("                                                                          \n");
		}
		gotoxy(0,0);
		print_screen("delete_view.txt");
	
		gotoxy(25,4);
		scanf("%s",dele);
		fflush(stdin);
		getch();
        
        write(client_socket, dele, strlen(dele));
	
	char deles[BUFFER_LEN] = "";
	int delen = read(client_socket, deles, BUFFER_LEN);
    	buffer[delen] = '\0';
        
	if(strcmp(deles,"empty") == 0){
		gotoxy(6,14);
		printf("검색하신 책이 없습니다.");
	}
	else{
	int c =0;
	int to =0;
	char* token = NULL;
	token = strtok(deles,"/");
	char *name[300][300] = {0,};
  	
             while(token != NULL){
		
		name[c][to] = token;
		token = strtok(NULL,"/");
		to++;

		if(to>3){
			c++;
			to=0;
		}
	     }
		
		gotoxy(1,9);
		int d = 0;

		for(d;d<c;d++){
			printf("| %-18s | %-10s | %-15s | %-2s |\n",name[d][0],name[d][1],name[d][2],name[d][3]);
		}
		
	buffer[0]='\0';
	getch();

	
	if(c==1){
		write(client_socket,name[0][0],strlen(name[0][0]));

		char delete[1000] = "";
		int deleten = read(client_socket, delete, BUFFER_LEN);
    		buffer[deleten] = '\0';

		if(strcmp(delete,"fail") == 0){
			gotoxy(10,14);
			printf("도서 삭제에 실패하였습니다.");
			getch();
		}else if(strcmp(delete,"success")==0){
			gotoxy(10,14);
			printf("도서 삭제에 성공하였습니다.");
			getch();
		}
	}else{
		for(i=10; i<25; i++){
			printf("                                                                          \n");
		}
		gotoxy(1,10);
		printf("삭제할 책을 한가지만 선택해주세요.\n");
	}

	}
	buffer[0]='\0';
	getch();

	

}
