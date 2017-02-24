#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

 
#define BUFFER_LEN 100
#define CHAT_SIZE 1024
#define BUFF_SIZE 1024
#define LISTEN_QUEUE_SIZE 5

MYSQL mysql;
MYSQL_RES* res;
MYSQL_ROW row; 
char query[80];

unsigned int i, fields; 	

//서버의 listen 소켓 데이터 구조 생성과정
char buffer[BUFFER_LEN];
struct sockaddr_in server_addr;
char temp[20];
int server_fd, client_fd;

int search_query(char value[30]);
int insert_query(char name[50],char writer[50],char publisher[50],char count[50]);
int delete_query(char name[300]);
void login_query(char value[20],char value2[20]);
void DB_connect();

int main(int argc, char *argv[])
{
    
    if (argc != 2)
    {
        printf("사용법 : ./filename 포트번호 \n");
        exit(0);
    }
 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("Server: can not Open Socket\n");
        exit(0);
    }
 
    //listen file descriptor 선언
    // memset은 모든 값을 0으로 초기화 해주기위해 서버 실행 시 이용한다.
    memset(&server_addr, 0, sizeof(server_addr));
 
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[1]));
 
    //bind 과정
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Server: can not bind local address\n");
        exit(0);
    }
    printf("클라이언트를 기다리는 중...\n");

    //listen 과정
    if (listen(server_fd, 5) < 0) 
    {
        printf("Server: can not listen connect. \n");
        exit(0);
    }
    printf("=====[포트번호] : %d =====\n", atoi(argv[1]));
    printf("서버 : 연결을 기다리는중...\n");
    
    struct sockaddr_in client_addr;
    int sin_size=sizeof(client_addr);
    	
    if((client_fd=accept(server_fd,(struct sockaddr*)&client_addr,&sin_size))==-1){
  		perror("accept");
     }
     printf("클라이언트가 접속하였습니다.\n");
     memset(buffer, 0, sizeof(buffer));
        
     inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, temp, sizeof(temp));
     printf("서버 : %s 클라이언트 연결\n", temp);

 	DB_connect();
        while (1) 
    	{ 
	
        //서버에서 메세지 전송
        char buffer[BUFFER_LEN];
	char buffer2[100];
	char buffer3[100];
	char buffer4[100];
	char chk[20];
	
	int chkN = read(client_fd, chk, 20);
	chk[chkN] = '\0';
   	printf("클라이언트에서 넘어온 값 : %s\n",chk);

   	if(chk[0] == '1' && chk[1] == 'a'){
		int insertn = read(client_fd, buffer, BUFFER_LEN);
    		buffer[insertn] = '\0';
		insertn=0;
   		printf("클라이언트에서 넘어온 값(책이름) : %s\n",buffer);
		insertn = read(client_fd,buffer2,100);
		buffer2[insertn]='\0';
		insertn=0;
		printf("클라이언트에서 넘어온 값(저자) : %s\n",buffer2);
	        insertn = read(client_fd,buffer3,100);
		buffer3[insertn]='\0';
		insertn=0;
		printf("클라이언트에서 넘어온 값(출판사) : %s\n",buffer3);
		insertn = read(client_fd,buffer4,100);
		buffer4[insertn]='\0';
		insertn=0;
		printf("클라이언트에서 넘어온 값(수량) : %s\n",buffer4);
		if(!insert_query(buffer,buffer2,buffer3,buffer4)){
			continue;
		}else{
			continue;
		}
	}
	
	else if(chk[0] == '2' && chk[1] == 'a'){
		int searchn = read(client_fd, buffer, BUFFER_LEN);
    		buffer[searchn] = '\0';
   		printf("클라이언트에서 넘어온 값(책이름) : %s\n",buffer);
		if(!search_query(buffer)){
			continue;
		}else{
			continue;
		}
	}else if(chk[0] == '3' && chk[1] == 'a'){
		int sn = read(client_fd, buffer, BUFFER_LEN);
    		buffer[sn] = '\0';
   		printf("클라이언트에서 넘어온 값(책이름) : %s\n",buffer);

		if(!search_query(buffer)){
			continue;
		}else{

			if(!delete_query(buffer)){
				continue;
			}else{
				continue;			
			}
			continue;
		}
	}

 	if(chk[0] == '1'){
		int n = read(client_fd, buffer4, BUFFER_LEN);
    		buffer4[n] = '\0';
   		printf("클라이언트에서 넘어온 값(책이름) : %s\n",buffer4);
		if(!search_query(buffer4)){
			continue;
		}else{
			continue;
		}
	}
	else if(chk[0] == '2'){
		int n2 = read(client_fd, buffer2, 20);
    		buffer2[n2] = '\0';
   		printf("클라이언트에서 넘어온 값(아이디) : %s\n",buffer2);
		int n3 = read(client_fd, buffer3, 20);
    		buffer3[n3] = '\0';
   		printf("클라이언트에서 넘어온 값(비밀번호) : %s\n",buffer3);
		login_query(buffer2,buffer3);
		}

	}
 	mysql_close(&mysql);
	//클라이언트 접속 종료
	close(client_fd);
	//서버 listen socket 종료
	close(server_fd);
 	return 0;
} 	
