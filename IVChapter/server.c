#include <unpipc.h>
#include "server.h"

void server(int rfd, int wfd){
    int fd;
    ssize_t n;
    char buff[MAXLINE + 1];
    printf("in server\n");
    if((n = read(rfd, buff, MAXLINE)) == 0)
	    printf("end of file while reading pathname");
    buff[n] = '\0';
    //only read
    if((fd = open(buff, O_RDONLY)) < 0){
	snprintf(buff + n, sizeof(buff) - n, ":can't open, %s\n", strerror(errno));
	n = strlen(buff);
	write(wfd, buff, n);
    }else{
	while((n = read(fd, buff, MAXLINE)) > 0)
		write(wfd, buff, n);
	close(fd);
    }
}

