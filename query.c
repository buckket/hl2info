// 
//  query.c
//  hl2info
//  
//  Created by bucketT on 2009-10-23.
// 

#define PACKETSIZE 1400


// ====================
// = ping-pong server =
// ====================
int hl2info_ping(int *sock) {
	
	struct timeval start;
	struct timeval end;
	
	char bufferS[PACKETSIZE];
	char bufferR[PACKETSIZE];
	
	sprintf(bufferS, A2S_PING);
	
	if(hl2info_udpSend(sock, bufferS, A2S_PING_LENGTH) ==1) return -1;
	gettimeofday(&start, NULL);
	if(hl2info_udpRecv(sock,bufferR) ==1) return -1;
		
	if(strcmp(bufferR+4,"j00000000000000") != 0) {
		return -1;
	}
	
	gettimeofday(&end, NULL);
	
	int fin = ((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec);
	fin = fin / 1000;
	
	return fin;
}


// ===========================
// = get global server infos =
// ===========================
int hl2info_serverInfo(int *sock, struct A2S_INFO *serverInfo) {
	
	char bufferS[PACKETSIZE];
	char bufferR[PACKETSIZE];
	
	int pos = 4;
		
	sprintf(bufferS, A2S_GETINFO);
	if(hl2info_udpSend(sock, bufferS, A2S_GETINFO_LENGTH) ==1) return -1;
	if(hl2info_udpRecv(sock, bufferR) ==1) return -1;
	
	//check Answer
	if(bufferR[pos] != 0x49) {
		printf("[-] Invalid Answer\n");
		return -1;
	}
	else {
		pos += 2;
	}
	
	//serverName
	strncpy(serverInfo->serverName,bufferR + pos, 255);
	pos += strlen(serverInfo->serverName) + 1;
	
	//map
	strncpy(serverInfo->map,bufferR + pos, 255);
	pos += strlen(serverInfo->map) + 1;
	pos += strlen(bufferR+pos) +1;
	
	//gameDescription
	strncpy(serverInfo->gameDescription,bufferR + pos, 255);
	pos += strlen(serverInfo->gameDescription) + 3;
	
	//numberPlayer
	serverInfo->numberPlayer = bufferR[pos];
	pos += 1;
	
	//numberMax
	serverInfo->numberMax = bufferR[pos];
	pos += 1;
	
	//numberBots
	serverInfo->numberBots = bufferR[pos];
	pos += 2;
	
	//os
	serverInfo->os = bufferR[pos];
	pos += 1;
	
	//password
	if(bufferR[pos] == 0x01) {
		serverInfo->password = 1;
	}
	pos++;
	
	//vac
	if(bufferR[pos] == 0x01) {
		serverInfo->vac = 1;
	}
	

	return 0;
}


// =================
// = Get Challenge =
// =================
int hl2info_challenge(int *sock, char *challenge) {
	
	char bufferS[PACKETSIZE];
	char bufferR[PACKETSIZE];
	
	int pos = 4;
	
	sprintf(bufferS, A2S_GETCHALLENGE);
	if(hl2info_udpSend(sock, bufferS, A2S_GETCHALLENGE_LENGTH) ==1) return -1;
	if(hl2info_udpRecv(sock, bufferR) ==1) return -1;
	
	//check Answer
	if(bufferR[pos] != 0x41) {
		printf("[-] Invalid Answer\n");
		return -1;
	}
	else {
		pos++;
	}
	
	memcpy(A2S_challenge,bufferR + pos,4);
	
	return 0;	
}


// ===================
// = Get Player Info =
// ===================
int hl2info_player(int *sock, char *challenge, struct A2S_PLAYER *playerInfo) {
	
	char bufferS[PACKETSIZE];
	char bufferR[PACKETSIZE] = { 0 };
	
	int pos = 4;
	
	sprintf(bufferS, A2S_GETPLAYER);
	memcpy(bufferS+5, A2S_challenge,4);
	
	if(hl2info_udpSend(sock, bufferS, A2S_GETPLAYER_LENGTH) ==1) return -1;
	if(hl2info_udpRecv(sock, bufferR) ==1) return -1;
	
	//check Answer
	if(bufferR[pos] != 0x44) {
		printf("[-] Invalid Answer\n");
		return -1;
	}
	else {
		pos++;
	}
	
	unsigned char numPlayer;
	numPlayer = bufferR[pos];
	pos++;
	
	if(numPlayer > 60) {
		printf("[-] Invalid Answer\n");
		return -1;
	}
	
	
	int i;
	for(i=0; i < numPlayer; i++) {
		
		playerInfo[i].playerIndex = bufferR[pos];
		pos++;		

		strncpy(playerInfo[i].playerName,bufferR + pos, 255);
		pos += strlen(bufferR + pos) +1;

		playerInfo[i].playerKills = *(int *)&bufferR[pos];
		pos += 4;

		playerInfo[i].playerConnected = *(float *)&bufferR[pos];
		pos += 4;

	}
	
	return numPlayer;
}
