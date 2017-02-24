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

//서버의 listen 소켓 데이터 구조 생성과정
char buffer[BUFFER_LEN];
struct sockaddr_in server_addr;
char temp[20];
int server_fd, client_fd;

int insert_query(char name[50],char writer[50],char publisher[50],char count[50]){
	char insert_data[1000] = "success";
	char insert_error[100] = "noInsert";
	
	sprintf(query,"insert into book values('%s','%s','%s','%s')", name,writer,publisher,count);
	printf("------------------------------------\n");
	
	if (mysql_query(&mysql, query)) {
	 	printf("MySQL Error %d: %s\n",
		mysql_errno(&mysql), mysql_error(&mysql));
		
		printf("클라이언트로 보낼 값 : %s\n", insert_error);
		write(client_fd, insert_error, strlen(insert_error));
	}else{
		printf("클라이언트로 보낼 값 : %s\n", insert_data);
		write(client_fd,insert_data,strlen(insert_data));
     	}

}
