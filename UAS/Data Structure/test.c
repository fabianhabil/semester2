#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    time_t timenow;
    struct tm* timeinfo;
    time(&timenow);
    timeinfo = localtime(&timenow);
    char date[100];
    printf("%d:%d", timeinfo->tm_hour, timeinfo->tm_min);
}