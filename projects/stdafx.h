// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include "targetver.h"

#include <string.h>  
#include <errno.h>  
#include <stdio.h>  
#include <signal.h>  
#ifndef WIN32  
#include <netinet/in.h>  
# ifdef _XOPEN_SOURCE_EXTENDED  
#  include <arpa/inet.h>  
# endif  
#include <sys/socket.h>  
#endif 

#include <event2/bufferevent.h>  
#include <event2/buffer.h>  
#include <event2/listener.h>  
#include <event2/util.h>  
#include <event2/event.h> 
#include <vector>

#pragma comment(lib,"ws2_32.lib")



// TODO: reference additional headers your program requires here
