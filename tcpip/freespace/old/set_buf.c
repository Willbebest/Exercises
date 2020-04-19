#include "head.h"

int main(int argc, char **argv)
{
    int sockfd;
    int snd_buf=1024*3, rcv_buf=1024*3;
    int state;
    socklen_t len;
    
    sockfd=socket(PF_INET, SOCK_STREAM, 0);
    state=setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, sizeof(snd_buf));
    if(state)
        error_handling("setsockopt() error");

    state=setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, (void*)&rcv_buf, sizeof(rcv_buf));
    if(state)
        error_handling("setsockopt() error");

    snd_buf=0,rcv_buf=0;
    len=sizeof(snd_buf);
    state=getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, &len);
    if(state)
        error_handling("getsockopt() error");

    len=sizeof(rcv_buf);
    state=getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, (void*)&rcv_buf, &len);
    if(state)
        error_handling("getsockopt() error");

    printf("Input buffer size: %d \n", rcv_buf);
    printf("Output buffer size: %d \n", snd_buf);

    return 0;
}
