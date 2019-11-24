#include "fifo.h"
#include "server.h"

int main(){
    int rfifo, wfifo, dummyfd, fd;
    char *ptr, buff[MAXLINE + 1], fifoname[MAXLINE];
    pid_t pid;
    ssize_t n;

    if((mkfifo(FIFOSERVER, FILE_MODE) < 0) &&(errno != EEXIST))
	printf("can't create %s", FIFOSERVER);
    rfifo = open(FIFOSERVER, O_RDONLY, 0);
/* dummyfd is never used */
    dummyfd = open(FIFOSERVER, O_WRONLY, 0);
// read pid and file path in FIFOSERVER
    while((n = read(rfifo, buff, MAXLINE)) > 0){
// don't need '\n' for line
	if(buff[n-1] == '\n')
	    n--;
	buff[n] = '\0';
// in client, ' ' is split, [0] is pid, [1] is file path
	if((ptr = strchr(buff, ' ')) == NULL){
	    printf("bogus request : %s", buff);
	    continue;
	}
// *ptr = 0; ptr++;
// ptr is file path, buff is pid
	*ptr++ = 0;
	pid = atol(buff);
	snprintf(fifoname, sizeof(fifoname), "/tmp/fifo.%ld", (long)pid);

	if((wfifo = open(fifoname, O_WRONLY, 0)) < 0){
	    printf("can't open %s\n", fifoname);
	    continue;
	}

	if((fd = open(ptr, O_RDONLY)) < 0){
	    snprintf(buff+n, sizeof(buff) - n, ":can't open, %s\n", "error");
// if open error, write to fifo.pid file path
	    n = strlen(ptr);
	    write(wfifo, ptr, n);
	    close(wfifo);
	}else{
// if open success, write to fifo.pid file count
	    while((n = read(fd, buff, MAXLINE)) > 0)
		write(wfifo, buff, n);
//close all;
	    close(fd);
	    close(wfifo);
	}
    }
    return 0;
}
