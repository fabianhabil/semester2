#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    time_t timenow;
    time(&timenow);
    char date[100];
    sprintf(date, ctime(&timenow));
    printf("%s", date);
}