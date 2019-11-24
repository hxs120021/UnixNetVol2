#include "client.h"

void client(int rfd, int wfd){
    size_t len;
    ssize_t n;
    char buff[MAXLINE];

    printf("in client\n");
    fgets(buff, MAXLINE, stdin);
    len = strlen(buff);
    if(buff[len - 1] == '\n')
	len--;
    write(wfd, buff, len);
    while((n = read(rfd, buff, MAXLINE)) > 0)
	write(STDOUT_FILENO, buff, n);
}

