#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define RLT_SIZE 4
#define OPSZ     4

void error_handling(char*);
int main(int argc, char**argv)
{
    int sock;
    char opmsg[BUF_SIZE]; //信息
    int result, opnd_cnt, i;  //结果  操作数的个数
    struct sockaddr_in serv_addr;

    if(argc!=3){
        printf("Usage : %s <IP><port>\n", argv[0]);
        exit(1);
    }

    sock=socket(PF_INET, SOCK_STREAM, 0);
    if(sock==-1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(struct sockaddr))==-1)
        error_handling("connect() error");
    else
        puts("Connected................");

    fputs("Operand count: ", stdout);  //获取操作数的个数，并以字符串的形式保存在opmsg中
    scanf("%d", &opnd_cnt);
    opmsg[0]=(char)opnd_cnt;
    
    //输入操作数
    for(i=0; i<opnd_cnt; i++)
    {
        printf("operand %d: ", i+1);
        scanf("%d", (int*)&opmsg[i*OPSZ+1]);
    }
    fgetc(stdin);
    //输入操作符
    fputs("Operator: ", stdout);
    scanf("%c", &opmsg[opnd_cnt*OPSZ+1]);
    //发送数据
    write(sock, opmsg, opnd_cnt*OPSZ+2);
    //接收运算结果
    read(sock, &result, RLT_SIZE);

    printf("Operation result: %d \n", result);
    close(sock);

    return 0;
}

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}


