#include <unpipc.h>
// sizeof(MESG) <= PIPE_BUF
#define MAXMESGDATA (PIPE_BUF - 2 * sizeof(long))
// header lenght
#define MESGHDRSIZE (sizeof(MESG) - MAXMESGDATA)

typedef struct mymesg{
    long mesg_len;
    long mesg_type;
    char mesg_data[MAXMESGDATA];
}MESG;

ssize_t mesg_send(int, MESG *);
void	Mesg_send(int, MESG *);
ssize_t mesg_recv(int, MESG *);
ssize_t Mesg_recv(int, MESG *);
