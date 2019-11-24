#include "fifo.h"
#include "client.h"

int main(){
    int rfifo, wfifo;
    size_t len;
    ssize_t n;
    char *ptr, fifoname[MAXLINE], buff[MAXLINE];
    pid_t pid;

    pid = getpid();
    snprintf(fifoname, sizeof(fifoname), "/tmp/fifo.%ld", (long)pid);

    if((mkfifo(fifoname, FILE_MODE) < 0) && (errno != EEXIST))
	printf("can't creat %s\n", fifoname);
// ps: befor in "%ld " have a ' ', use split pid and file path
    snprintf(buff, sizeof(buff), "%ld ", (long)pid);
    len = strlen(buff);
// ptr to buff end location
// buff is pid string
    ptr = buff + len;
// console input file path
    fgets(ptr, MAXLINE - len, stdin);
// add from ptr, buff += buff+ptr
    len = strlen(buff);
// write to FIFOSERVER pid and file path
    wfifo = open(FIFOSERVER, O_WRONLY, 0);
    write(wfifo, buff, len);

    rfifo = open(fifoname, O_RDONLY, 0);
// read from rfifo.pid file count, loop all count
    while((n = read(rfifo, buff, MAXLINE)) > 0){
// print to console
	write(STDOUT_FILENO, buff, n);
    }
// close all
    close(rfifo);
    unlink(fifoname);

    return 0;
}
