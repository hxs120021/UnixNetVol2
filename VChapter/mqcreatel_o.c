#include <unpipc.h>

int main(int argc, char **argv){
    int c, flags;
    mqd_t mqd;

    flags = O_RDWR | O_CREAT;

    while((c = getopt(argc, argv, "e")) != -1){
	switch(c){
	    case 'e':
		flags |= O_EXCL;
		break;
	}
    }

    if(optind != argc - 1){
	printf("usage : [ -e ], <name>\n");
	return 0;
    }

    mqd = mq_open(argv[optind], flags, FILE_MODE, NULL);

    mq_close(mqd);
    return 0;
}
