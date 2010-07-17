// 
//  query.h
//  hl2info
//  
//  Created by bucketT on 2009-10-23.
// 

#define A2S_PING "\xFF\xFF\xFF\xFF\x69"
#define A2S_PING_LENGTH 5

#define A2S_GETINFO "\xFF\xFF\xFF\xFF\x54Source Engine Query"
#define A2S_GETINFO_LENGTH 25

#define A2S_GETCHALLENGE "\xFF\xFF\xFF\xFF\x55\xFF\xFF\xFF\xFF"
#define A2S_GETCHALLENGE_LENGTH 9

#define A2S_GETPLAYER "\xFF\xFF\xFF\xFF\x55"
#define A2S_GETPLAYER_LENGTH 9

struct A2S_INFO {
	
	char serverName[255];
	char map[255];
	
	char gameDescription[255];
	
	char numberPlayer;
	char numberBots;
	char numberMax;
	
	char os;
	char password;
	char vac;
};

struct A2S_PLAYER {
	
	char	playerIndex;
	
	char 	playerName[255];
	int		playerKills;
	float	playerConnected;
};

char A2S_challenge[4];


#include "query.c"


int hl2info_ping(int *sock);
int hl2info_serverInfo(int *sock,struct A2S_INFO *serverInfo);
int hl2info_challenge(int *sock, char *challenge);
int hl2info_player(int *sock, char *challenge, struct A2S_PLAYER *playerInfo);