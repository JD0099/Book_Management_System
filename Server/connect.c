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

MYSQL mysql;
MYSQL_RES* res;
MYSQL_ROW row; 

void DB_connect()
{
	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql, "localhost", "root", "1234", "db", 0, (char *)NULL, 0)) 	{
 		printf("Error %d: %s\n",
		mysql_errno(&mysql), mysql_error(&mysql));
 		exit(0);
 	}
}
