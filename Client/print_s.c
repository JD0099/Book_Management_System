#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <termio.h>
#include <fcntl.h>
#include <unistd.h>

void print_screen(char fname[])
{
	FILE *fp;
	char line[100];

	if ( (fp = fopen(fname,"r"))  == NULL ){
		printf("file open error\n");
		//getch();
		exit(-1);
	}
	while(1)
	{
		if( fgets(line, 99, fp) == NULL){
		     break;
		}
		printf("%s", line);
	}

	fclose(fp);
}
