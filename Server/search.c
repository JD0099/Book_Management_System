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

 
#define BUFFER_LEN 1000
#define CHAT_SIZE 1024
#define BUFF_SIZE 1024
#define LISTEN_QUEUE_SIZE 5

MYSQL mysql;
MYSQL_RES* res;
MYSQL_ROW row; 
char query[200];

unsigned int i, fields; 	

//서버의 listen 소켓 데이터 구조 생성과정
char buffer[BUFFER_LEN];
struct sockaddr_in server_addr;
char temp[20];
int server_fd, client_fd;


int search_query(char value[30])
{	
	char select_data[1000] = "";
	char select_error[100] = "empty";
	int select_chk = 0;
	
	sprintf(query,"select * from book where name like '%%%s%%'", value);
	
	if (mysql_query(&mysql, query)) {
	 	printf("MySQL Error %d: %s\n",
		mysql_errno(&mysql), mysql_error(&mysql));
	}else{
		res = mysql_store_result(&mysql);
			fields = mysql_num_fields(res);
			printf("------------------------------------\n");
 	   		
 	   		while ((row = mysql_fetch_row(res))) {
 				for (i = 0; i < fields; i++) {	
					strcat(select_data,row[i]);
					strcat(select_data,"/");
				}
				select_chk = 1;
			
	   		}     
			
			if(select_chk == 0){
			printf("클라이언트로 보낼 값 : %s\n", select_error);
			write(client_fd, select_error, strlen(select_error));
			}
			if(select_chk == 1){
			printf("클라이언트로 보낼 값 : %s\n", select_data);
          		write(client_fd, select_data, strlen(select_data));
			}
 			mysql_free_result(res); 
		
     	}
}
