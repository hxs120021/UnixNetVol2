#include <unpipc.h>

int main(int argc, char **argv){
    mqd_t mqd;
    void *ptr;
    size_t len;
    uint32_t prio;

    if(argc != 4){
	printf("usage: mqsend <name> <#bytes> <priority>\n");
	return 0;
    }

    len = atol(argv[2]);
    prio = atol(argv[3]);
    mqd = mq_open(argv[1], O_WRONLY);
    ptr = calloc(len, sizeof(char));
    mq_send(mqd, ptr, len, prio);

    return 0;
}
