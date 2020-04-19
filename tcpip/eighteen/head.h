/*************************************************************************
	> File Name: head.h
	> Author: 
	> Mail: 
	> Created Time: Wed 16 Oct 2019 06:35:43 PM PDT
 ************************************************************************/

#ifndef _HEAD_H
#define _HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

#endif
