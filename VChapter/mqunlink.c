#include <unpipc.h>

int main(int argc, char **argv){
    if(argc != 2){
	printf("option error");
    }

    mq_unlink(argv[1]);
    return 0;
}
