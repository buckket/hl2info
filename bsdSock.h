// 
//  bsdSock.h
//  hl2info
//  
//  Created by bucketT on 2009-10-20.
// 

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "bsdSock.c"

int hl2info_connect(int *sock, struct sockaddr_in *addr, char *ip, int *port);
void hl2info_close(int *sock);

int hl2info_udpSend(int *sock, char *bufferS, int sizeOfBuffer);
int hl2info_udpRecv(int *sock, char *bufferR);

void hl2info_startup(void);
void hl2info_cleanup(void);