#include <unpipc.h>
#include "client.h"
#include "server.h"

#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"

int main(){
    int rfd, wfd;
    pid_t childpid;

    if((mkfifo(FIFO1, FILE_MODE) < 0) && (errno != EEXIST))
	printf("can't creat FIFO1 file : %s", FIFO1);
    if((mkfifo(FIFO2, FILE_MODE) < 0) && (errno != EEXIST)){
	unlink(FIFO1);
	printf("can't creat FIFO2 file : %s", FIFO2);
    }

    if((childpid = fork()) == 0){
	printf("in child \n");
	rfd = open(FIFO1, O_RDONLY, 0);
	wfd = open(FIFO2, O_WRONLY, 0);
	server(rfd, wfd);
	exit(0);
    }
    printf("in father \n");
    wfd = open(FIFO1, O_WRONLY, 0);
    rfd = open(FIFO2, O_RDONLY, 0);
    client(rfd, wfd);

    waitpid(childpid, NULL, 0);
    close(rfd);
    close(wfd);
    unlink(FIFO1);
    unlink(FIFO2);
    exit(0);
}
