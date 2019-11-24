#include <unpipc.h>

int main(){
    size_t n;
    char buff[MAXLINE], command[MAXLINE];
    FILE *fp;

    fgets(buff, MAXLINE, stdin);
    n = strlen(buff);
    if(buff[n-1] == '\n')
	n--;
    snprintf(command, sizeof(command), "ls %s", buff);
    fp = popen(command, "r");
    while(fgets(buff, MAXLINE, fp) != NULL)
	fputs(buff, stdout);
    pclose(fp);
    exit(0);
}
