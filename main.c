// 
//  main.c
//  hl2info
//  
//  Created by bucketT on 2009-10-20.
// 

#include <stdlib.h>
#include <stdio.h>

#include "hl2info.h"


int printServerDetails(char *ipadress,int port);


int main(int argc, char *argv[]) {
	
	
	//G'Day
	printf("hl2info - %s\n", __DATE__);

	
	char ipadress[16] = "212.83.47.140";
	int port = 27015;
	
	/*
	if(argc == 3 || argc == 4) {
			strncpy(ipadress, argv[1],16);
			port = strtol(argv[2],NULL,10);
			
			if(argc == 4) {
				if(strcmp(argv[3],"-a") == 0) {
					printf("\nNow i'd add the server to the favs\n");
				}
			}
		}
		else {
			printf("\nRight Syntax: hl2info <IP> <Port>\n");
		}
	*/
		
	hl2info_startup();
	if(printServerDetails(ipadress, port) == 1) printf("[-] Error while reading infos\n");
	hl2info_cleanup();
	
	return 0;
}

int printServerDetails(char *ipadress,int port) {
	
	//This function just sucks, rewrite needed
	
	#ifdef _WIN32
	SOCKET sock;
	#else
	int sock;
	#endif
	
	
	struct A2S_INFO hl2info_serverInfoS, *hl2info_serverInfoPTR;
	hl2info_serverInfoPTR = &hl2info_serverInfoS;
	
	
	if(hl2info_connect(&sock, ipadress, &port) == -1) return 1;
	
	
	printf("\n.:: #1 ::.\n");
	if(hl2info_serverInfo(&sock, hl2info_serverInfoPTR) == -1) return 1;
	printf("%s\n", hl2info_serverInfoS.serverName);
	printf("%s @ %s with %d/%d players\n", \
		hl2info_serverInfoS.gameDescription, \
		hl2info_serverInfoS.map, \
		hl2info_serverInfoS.numberPlayer, \
		hl2info_serverInfoS.numberMax);
	
	printf("Flags: %c",hl2info_serverInfoS.os);
	if(hl2info_serverInfoS.password == 1) printf("p");
	if(hl2info_serverInfoS.vac == 1) printf("v");

	printf(" | Latency: %d | IP: %s:%d\n\n", hl2info_ping(&sock), ipadress, port);
	
	struct A2S_PLAYER *playerPTR;
	playerPTR = (struct A2S_PLAYER*) calloc(hl2info_serverInfoS.numberMax,sizeof(struct A2S_PLAYER));
	if (playerPTR == NULL) return 1;
	
	if(hl2info_challenge(&sock, A2S_challenge) == -1) return 1;
	
	int numPlayer = hl2info_player(&sock, A2S_challenge, playerPTR);
	if(numPlayer == -1) return 1;
	if(numPlayer == 0) printf("Nothing to show\n");
	
	int i;
	for(i=0; i < numPlayer; i++) {	
		if(strlen(playerPTR[i].playerName) == 0) {
			printf("%d. Player not connected yet\n", -1);
		}
		else {
			printf("%d. (%d) %s (%d) since %f\n", i+1,
				playerPTR[i].playerIndex, \
				playerPTR[i].playerName, \
				playerPTR[i].playerKills, \
				playerPTR[i].playerConnected);
		}	
	}

	
	free(playerPTR);
	hl2info_close(&sock);
	
	return 0;
}