#include <unpipc.h>

int main(int argc, char **argv){
    int c, flags;
    // Message queue descriptor, if error is -1
    mqd_t mqd;
    // read and write or create
    flags = O_RDWR | O_CREAT;

    while((c = getopt(argc, argv, "e")) != -1){
	if(c == 'e'){
	    flags = flags | O_EXCL;
	}
    }

    if(optind != argc - 1){
	printf("%d, %d\n", optind, argc -1);
	printf("option [-e] error");
    }

    mqd = mq_open(argv[optind], flags, FILE_MODE, NULL);
    mq_close(mqd);
    return 0;
}
