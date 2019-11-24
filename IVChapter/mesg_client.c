#include "mesg.h"

void client(int rfd, int wfd){
    size_t len;
    ssize_t n;
    MESG mesg;
// console get file name
    fgets(mesg.mesg_data, MAXMESGDATA, stdin);

    len = strlen(mesg.mesg_data);
    if(mesg.mesg_data[len-1] == '\n')
	len--;
    mesg.mesg_len = len;
    mesg.mesg_type = 1;

    mesg_send(wfd, &mesg);
    while((n = mesg_recv(rfd, &mesg)) > 0){
	write(STDOUT_FILENO, mesg.mesg_data, n);
    }
}
