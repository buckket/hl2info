// 
//  winSock.c
//  hl2info
//  
//  Created by bucketT on 2009-10-21.
// 

#define PACKETSIZE 1400


// ===========
// = startup =
// ===========
void hl2info_startup(void) {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,0),&wsa);
}


// ============================
// = start and connect socket =
// ============================
int hl2info_connect(int *sock, char *ip, int *port) {
	
	long rc;
	
	struct sockaddr_in addr;
	
	*sock = socket(AF_INET,SOCK_DGRAM,0);
	
	struct timeval tv;
	tv.tv_sec = 4000; //M$ Sucks. 4000 Sec = 4 (MS)Sec :S
	setsockopt (*sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof tv);
	setsockopt (*sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&tv, sizeof tv);

	
	addr.sin_family=AF_INET;
	addr.sin_port=htons(*port);
	addr.sin_addr.s_addr=inet_addr(ip);
	
	rc=connect(*sock,(struct sockaddr*)&addr,sizeof(*addr));
	
	if(rc != 0) {
		printf("[-] Error while setting up socket!\n");
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
		printf("[-] Error while sending data!\n");
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
		printf("[-] Error while getting data!\n");
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
	closesocket(*sock);	
}


// ===========
// = cleanup =
// ===========
void hl2info_cleanup(void) {
	WSACleanup();
}
