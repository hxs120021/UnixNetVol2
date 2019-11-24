#include "mesg.h"

ssize_t mesg_send(int fd, MESG *mesg){
    return write(fd, mesg, MESGHDRSIZE + mesg->mesg_len);
}

ssize_t mesg_recv(int fd, MESG *mesg){
    size_t len;
    ssize_t n;
// read head count, get true len.
    if((n = read(fd, mesg, MESGHDRSIZE)) == 0){
	return 0;
    }else if(n != MESGHDRSIZE){
	printf("mesg have error.");
	return 0;
    }

    if((len = mesg->mesg_len) != 0){
	if((n = read(fd, mesg->mesg_data, len)) != len){
	   printf("mesg count is error.");
	   return 0;
	}
    }
    return len;
}
