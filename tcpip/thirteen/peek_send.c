#include "head.h"

int main(int argc, char **argv)
{
    int sock;
    struct sockaddr_in send_addr;
    if(argc!=3){
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock=socket(PF_INET, SOCK_STREAM, 0);
    memset(&send_addr, 0, sizeof(send_addr));
    send_addr.sin_family=AF_INET;
    inet_aton(argv[1], &send_addr.sin_addr);
    send_addr.sin_port=htons(atoi(argv[2]));

    if((connect(sock, (struct sockaddr*)&send_addr, sizeof(send_addr)))==-1)
        error_handling("connect() error");

    write(sock, "123", strlen("123"));
    close(sock);

    return 0;
}


