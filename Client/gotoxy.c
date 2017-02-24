#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gotoxy(int x, int y) {
    printf("\033[%d;%df", y, x);
    fflush(stdout);
}
