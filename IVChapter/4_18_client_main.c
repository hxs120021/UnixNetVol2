#include "client.h"
#include "fifo.h"

int main(){
    int rfd, wfd;
    printf("1\n");
    wfd = open(FIFO1, O_WRONLY, 0);
    printf("2\n");
    rfd = open(FIFO2, O_RDONLY, 0);
    printf("3\n");
    client(rfd, wfd);
    close(rfd);
    close(wfd);
    unlink(FIFO1);
    unlink(FIFO2);
    exit(0);
}
