#include <unpipc.h>

volatile sig_atomic_t mqflag;
static void sig_usr1(int);

int main(){
    
    return 0;
}

static void sig_usr1(int signo){
    mqflag = 1;
    printf("%d", signo);
    return;
}