Introduction
============

[hl2info](http://github.com/bucket-T/hl2info) is an experimental C library for querying a HL2 based server.  
It aims to run both on UNIX and Windows.


Status
======

**Implemented functions:**
	hl2info_ping();			// ping server
	hl2info_serverInfo();	// get server details
	hl2info_challenge();	// challengeID for player request
	hl2info_player();		// get playerinfos

**Query Protocol:**  
[http://developer.valvesoftware.com/wiki/Server_Queries](http://developer.valvesoftware.com/wiki/Server_Queries)