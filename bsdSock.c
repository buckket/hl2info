// 
//  bsdSock.c
//  hl2info
//  
//  Created by bucketT on 2009-10-20.
// 

#define PACKETSIZE 1400


// ============================
// = start and connect socket =
// ============================
int hl2info_connect(int *sock, struct sockaddr_in *addr, char *ip, int *port) {
	
	const int x = -1;
	long rc;
	
	
	*sock = socket(AF_INET,SOCK_DGRAM,0);
	setsockopt(*sock, SOL_SOCKET, SO_REUSEADDR, &x, sizeof(int));
	
	struct timeval tv;
	tv.tv_sec = 4;
	
	setsockopt (*sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof tv);
	setsockopt (*sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&tv, sizeof tv);
	

	(*addr).sin_family=AF_INET;
	(*addr).sin_port=htons(*port);
	(*addr).sin_addr.s_addr=inet_addr(ip);
	
	rc=connect(*sock,(struct sockaddr*)addr,sizeof(*addr));
	
	if(rc != 0) {
		//printf("[-] Error while setting up socket!\n");
		perror("hl2info_connect");
		return 1;
	}
	
	return 0;
}


// =================
// = send UDP data =
// =================
int hl2info_udpSend(int *sock, char *bufferS, int sizeOfBuffer) {
	
	long rc;
	rc = send(*sock,bufferS,sizeOfBuffer,0);
	
	if(rc == -1) {
		//printf("[-] Error while sending data!\n");
		perror("hl2info_udpSend");
		return 1;
	}
	
	return 0;	
}


// ================
// = get UDP data =
// ================
int hl2info_udpRecv(int *sock, char *bufferR) {
	
	long rc;
	rc = recv(*sock,bufferR,PACKETSIZE,0);

	if(rc == -1 || rc == 0) {
		//printf("[-] Error while getting data!\n");
		perror("hl2info_udpRecv");
		return 1;
	}
	
	if(strncmp(bufferR,"\xFF\xFF\xFF\xFF", 4) != 0) {
		printf("[-] Invalid packet!\n");
		return 1;
	}
		
	return 0;
}


// =====================
// = finish off socket =
// =====================
void hl2info_close(int *sock) {
	
	close(*sock);	
}


// =======
// = NOP =
// =======
void hl2info_startup(void) {
	//NOP
}

void hl2info_cleanup(void) {
	//NOP
}
