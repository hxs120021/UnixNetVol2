#include "mesg.h"

void server(int rfd, int wfd){
    FILE *fp;
    ssize_t n;
    MESG mesg;
    mesg.mesg_type = 1;
    if((n = mesg_recv(rfd, &mesg)) == 0){
	printf("path missing\n");
    }
    mesg.mesg_data[n] = '\0';
// open file path, mesg.mesg_data count is file path
    if((fp = fopen(mesg.mesg_data, "r")) == NULL){
// open error, must tell client
	snprintf(mesg.mesg_data + n, sizeof(mesg.mesg_data) - n, "can't open %s\n", "error");
	mesg.mesg_len = strlen(mesg.mesg_data);
	mesg_send(wfd, &mesg);
    }else{
	while(fgets(mesg.mesg_data, MAXMESGDATA, fp) != NULL){
// open success, set mesg_len, and send mesg;
	    mesg.mesg_len = strlen(mesg.mesg_data);
	    mesg_send(wfd, &mesg);
	}
	fclose(fp);
    }
// finish send 0 data to client the end.
    mesg.mesg_len = 0;
    mesg_send(wfd, &mesg);
}
