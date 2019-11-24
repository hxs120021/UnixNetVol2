#include "fifo.h"
#include "server.h"

int main(){
    int rfd, wfd;
    if((mkfifo(FIFO1, FILE_MODE) < 0) && (errno != EEXIST))
	printf("can't creat FIFO1:%s", FIFO1);
    if((mkfifo(FIFO2, FILE_MODE) < 0) && (errno != EEXIST)){
	unlink(FIFO1);
	printf("can't creat FIFO2:%s", FIFO2);
    }

    rfd = open(FIFO1, O_RDONLY, 0);
    wfd = open(FIFO1, O_WRONLY, 0);

    server(rfd, wfd);

    exit(0);
}
