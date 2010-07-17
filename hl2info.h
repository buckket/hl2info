// 
//  hl2info.h
//  hl2info
//  
//  Created by bucketT on 2009-10-20.
//

#include <string.h>
#include <time.h>


#ifdef _WIN32
// WINSOCK2
#include "winSock.h"

#else
// BSD Sockets
#include "bsdSock.h"
#endif

#include "query.h"