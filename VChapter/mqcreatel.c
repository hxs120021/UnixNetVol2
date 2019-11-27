#include <unpipc.h>

struct mq_attr attr;

int main(int argc, char **argv){
    int c, flags;
    // Message queue descriptor, if error is -1
    mqd_t mqd;
    // read and write or create
    flags = O_RDWR | O_CREAT;
    // mqueue option struct.
//    struct mq_attr attr;
    while((c = getopt(argc, argv, "em:z:")) != -1){
	switch(c){
	    case 'e':
		flags = flags | O_EXCL;
		break;
	    case 'm':
		attr.mq_maxmsg = atol(optarg);
		break;

	    case 'z':
		attr.mq_msgsize = atol(optarg);
		break;
	}
    }

    if(optind != argc - 1){
	printf("%d, %d\n", optind, argc -1);
	printf("1. option error");
	return 0;
    }

    if((attr.mq_maxmsg == 0 && attr.mq_msgsize != 0) ||
	(attr.mq_maxmsg != 0 && attr.mq_msgsize == 0)){
	printf("2. attr option error");
	return 0;
    }

    mqd = mq_open(argv[optind], flags, FILE_MODE, (attr.mq_maxmsg != 0) ? &attr : NULL);
    mq_close(mqd);
    return 0;
}
