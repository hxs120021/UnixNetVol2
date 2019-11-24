#include <unpipc.h>

int main(){
    int fd[2], n;
    char buff[MAXLINE + 1];
    pid_t childpid;

    pipe(fd);
    if((childpid = fork()) == 0){
	sleep(1);
	if((n = read(fd[0], buff, MAXLINE)) != MAXLINE){
	    printf("child: read data number : %d\n", n);
	}

	printf("child read data: %s\n", buff);
	char senddata[10] = "asdfasdfa";
	write(fd[0], senddata, strlen(senddata));
	exit(0);
    }

    write(fd[1], "asdf", 4);
    if((n = read(fd[1], buff, MAXLINE)) != MAXLINE)
	printf("parent: read data number : %d\n", n);
    printf("parent read data : %s\n", buff);
    exit(0);
}
