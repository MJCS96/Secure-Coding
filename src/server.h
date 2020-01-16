#ifndef _SERVER_H_
#define _SERVER_H_

#include "utils.h"

#define DEFAULT_PORT    "27015"
#define DEFAULT_BUFLEN          4096
#define DEFAULT_MAX_PASS_LEN    32

typedef enum {
    CONN_INVALID = 0,
    CONN_UNAUTHENTICATED,       // Can change to: CONN_USER_OK (if 'user XXX' matches a correct user)
    CONN_USER_OK,               // Can change to: UNAUTHENTICATED (if 'pass XXX' fails too many times), or AUTHENTICATED (if 'pass XXX' matches correct password) 
    CONN_AUTHENTICATED,         // Can change to: UNAUTHENTICATED (if 'logoff' is given)
} CONNECTION_STATE;


#define CMD_EXIT        "exit"
#define CMD_USER        "user"
#define CMD_PASS        "pass"
#define CMD_LOGOFF      "logoff"
#define CMD_LIST        "list"
#define CMD_GET         "get"
#define CMD_AVAIL       "avail"
#define CMD_INFO        "info"
#define CMD_CREATE_MSG	"createmsg"
#define CMD_WRITE_MSG	"writemsg"

extern DWORD gUserCount;
extern USER_DATA gUserData[10];

void
Log(
    const char *Format,
    ...
    );

// SERVER COMMANDS
BOOLEAN
CmdHandleUser(
    char* User,
    int *UserId
);


BOOLEAN
CmdHandlePass(
    int UserId,
    char *Password
);

void
CmdHandleList(
    int UserId,
    char *Output,
    int *OutLength
);

BOOLEAN
CmdHandleInfo(
    int UserId,
    char *Details,
    char *Output,
    int *OutLength
);

void
CmdHandleGet(
    int UserId,
    char *Message,
    char *Output,
    int *OutLength
);

HANDLE CmdHandleCreateMsg(char* filePath, int UserId);

void CmdHandleWriteMsg(HANDLE fileHandle);

#endif _SERVER_H_
