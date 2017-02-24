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
char admin_chk[BUFFER_LEN] = "";
char check[BUFFER_LEN] = "";
int i =0;
char s[BUFFER_LEN];

int getch(void);
void print_screen(char fname[]);
void gotoxy(int x, int y);
void select_tuple();
int insert_tuple();
void delete_tuple();
void login();

int main(int argc, char** argv) 
{
	
    if (argc != 2) 
    {
        printf("Usage: %s IPv4-address\n", argv[0]);
        return -1;
    }
 
    //서버에 접속할 소켓 데이터 구조 생성과정
      client_socket = socket(PF_INET, SOCK_STREAM, 0);
      if(client_socket == -1)
      {
          printf("socket 생성 실패\n");
           exit(1);
       }
 
    //connect file descriptor 선언	
    // memset은 모든 값을 0으로 초기화 해주기위해 클라이언트 실행 시 이용한다.
     memset(&client_addr, 0, sizeof(client_addr));
 
     client_addr.sin_family = AF_INET;
     client_addr.sin_port = htons(9190); // 포트번호를 9190으로 임의 지정해두었다.
     client_addr.sin_addr.s_addr= inet_addr("127.0.0.1"); // 서버 ip는 로컬 주소인 127.0.0.1로 지정해두었다.
 
    //서버에 접속하시오
        if(connect(client_socket, (struct sockaddr*)&client_addr, sizeof(client_addr)) == -1)
        {
            printf("접속 실패\n");
            exit(1);
        }
   	printf("접속에 성공했습니다.\n");

	while(1){
	for(i=0; i<25; i++){
	printf("                                                                          \n");
	}
	gotoxy(0,0);
	print_screen("menu2_view.txt");
	gotoxy(36,10);
	
	scanf("%s",admin_chk);
	fflush(stdin);
	write(client_socket, admin_chk, strlen(admin_chk));

	if(admin_chk[0] == '1'){
		select_tuple();
	
	}
	else if(admin_chk[0] == '2'){
		login();
		
	    while(1){
	     if(strcmp(s,"1")==0){
		gotoxy(26,5);
		printf("로그인성공");
		getch();
		gotoxy(0,0);
		
		while(1){
			for(i=0; i<25; i++){
				printf("                                                                          \n");
			}
			gotoxy(0,0);
			print_screen("menu_view.txt");
			gotoxy(36,10);
	
			scanf("%s",check);
			fflush(stdin);
			strcat(check,"a");
			write(client_socket, check, strlen(check));

			if(check[0] == '1' && check[1] == 'a'){
				insert_tuple();
			}
			if(check[0] == '2' && check[1] == 'a'){
				select_tuple();
			}
			if(check[0] == '3' && check[1] == 'a'){
				delete_tuple();
			}
			if(check[0] == '4' && check[1] == 'a'){
				for(i=0; i<25; i++){
				printf("                                                                          \n");
			}
			gotoxy(0,0);
			exit(1);
			}
			else{
				gotoxy(38,12);
				printf("값을 잘못 입력하였습니다.");
				continue;
			}
		    }
		}	
		else if(strcmp(s,"empty")==0){
			gotoxy(26,5);
			printf("아이디 혹은 비밀번호가 틀렸습니다.");
			getch();
			break;
		}
	    }
		
	}
	else{
		gotoxy(38,12);
		printf("값을 잘못 입력하였습니다.");
		continue;
		}
	}
	
    //클라이언트 접속 종료
     close(client_socket);
 
    return 0;
}
