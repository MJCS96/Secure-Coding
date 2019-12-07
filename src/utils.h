#ifndef _UTILS_H_
#define _UTILS_H_

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#define FIELD_SIZE      25
typedef struct _USER_DATA
{
    char Username[FIELD_SIZE];
    char Name[FIELD_SIZE];
    char Email[FIELD_SIZE];
    char Password[FIELD_SIZE];
} USER_DATA;

void
PrintBuffer(
    char *Buffer,
    int Length
    );

typedef unsigned long long QWORD;

typedef struct _MAPPING
{
    HANDLE			FileHandle;
    HANDLE			MapHandle;
    QWORD			DataSize;
    PBYTE			Data;
} MAPPING, *PMAPPING;

DWORD
MapFile(
    _In_	PCSTR		Filename,
    _In_	DWORD		AccessRights,
    _Out_	MAPPING*	Mapping
);

void
UnmapFile(
    _In_	MAPPING*	Mapping
);

#endif // _UTILS_H_

