#include "utils.h"

#define CHARS_PER_LINE  16

void
PrintBuffer(
            char *Buffer,
            int Length
            )
{
    int i;
    char a[CHARS_PER_LINE+1];

    //
    a[CHARS_PER_LINE] = 0;

    for (i = 0; i < Length; i++)
    {
        char x = Buffer[i];

        if ((x >= 'a') && (x <= 'z') ||
            (x >= 'A') && (x <= 'Z') ||
            (x >= '0') && (x <= '9') )
        {
            a[i % CHARS_PER_LINE] = x;
        }
        else
        {
            a[i % CHARS_PER_LINE] = '.';    // Replace with '.' if non alpha characters might appear in buffer
        }

        printf("%0.2x ", (unsigned char)Buffer[i]);

        if (i % CHARS_PER_LINE == (CHARS_PER_LINE-1))
        {
            printf("| %s\n", a);
        }
        else 
        if (i == Length-1)
        {
            int j;
            for (j = (i+1) % CHARS_PER_LINE; j < CHARS_PER_LINE; j++)
            {
                printf("   ");
            }

            if ((i+1) % CHARS_PER_LINE != 0)
            {
                a[(i+1)%CHARS_PER_LINE] = 0;
                printf("| %s\n", a);
            }
        }

    }

    //printf("\n");
}

DWORD
MapFile(
    _In_	PCSTR		Filename,
    _In_	DWORD		AccessRights,
    _Out_	MAPPING*	Mapping
)
{
    DWORD result;
    DWORD flProtect;
    DWORD mapAccessRights;

    if (NULL == Filename)
    {
        return ERROR_INVALID_PARAMETER;
    }

    if (NULL == Mapping)
    {
        return ERROR_INVALID_PARAMETER;
    }

    result = ERROR_SUCCESS;
    Mapping->FileHandle = INVALID_HANDLE_VALUE;
    Mapping->MapHandle = NULL;
    Mapping->DataSize = 0;
    Mapping->Data = NULL;

    if (0 != (GENERIC_WRITE & AccessRights))
    {
        flProtect = PAGE_READWRITE;
        mapAccessRights = FILE_MAP_READ | FILE_MAP_WRITE;
    }
    else
    {
        flProtect = PAGE_READONLY;
        mapAccessRights = FILE_MAP_READ;
    }

    __try
    {
        Mapping->FileHandle = CreateFileA(Filename,
            AccessRights,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
        if (INVALID_HANDLE_VALUE == Mapping->FileHandle)
        {
            result = GetLastError();
            __leave;
        }

        Mapping->MapHandle = CreateFileMapping(Mapping->FileHandle,
            NULL,
            flProtect,
            0,
            0,
            NULL);
        if (NULL == Mapping->MapHandle)
        {
            result = GetLastError();
            __leave;
        }

        Mapping->Data = MapViewOfFile(Mapping->MapHandle,
            mapAccessRights,
            0,
            0,
            0);
        if (NULL == Mapping->Data)
        {
            result = GetLastError();
            __leave;
        }


        if (!GetFileSizeEx(Mapping->FileHandle, (PLARGE_INTEGER)&Mapping->DataSize))
        {
            result = GetLastError();
            __leave;
        }
    }
    __finally
    {
        if (ERROR_SUCCESS != result)
        {
            UnmapFile(Mapping);
        }
    }

    return result;
}

void
UnmapFile(
    _In_	MAPPING*	Mapping
)
{
    if (NULL == Mapping)
    {
        return;
    }

    Mapping->DataSize = 0;

    if (NULL != Mapping->Data)
    {
        UnmapViewOfFile(Mapping->Data);
        Mapping->Data = NULL;
    }

    if (NULL != Mapping->MapHandle)
    {
        CloseHandle(Mapping->MapHandle);
        Mapping->MapHandle = NULL;
    }

    if (INVALID_HANDLE_VALUE != Mapping->FileHandle)
    {
        CloseHandle(Mapping->FileHandle);
        Mapping->FileHandle = INVALID_HANDLE_VALUE;
    }
}

DWORD TestMAP()
{
    MAPPING map;
    DWORD result;

    result = ERROR_SUCCESS;

    result = MapFile("file.txt",                     //nume
        GENERIC_READ | GENERIC_WRITE,                //drepturi
        &map);
    if (ERROR_SUCCESS != result)
    {
        printf("MapFile failed with result %u\n", result);
        goto Cleanup;
    }

    /// now you can read from / write to the file like accessing a buffer
    printf("MapFile succeeded. First char = %c \n", map.Data[0]);   // read  
    //map.Data[0] = 'a';                                              // write

Cleanup:
    UnmapFile(&map);

    return result;
}

HANDLE createFile(LPCSTR fileName) //TODO: Interpret errors
{
	if (NULL == fileName)
	{
		return (HANDLE)ERROR_INVALID_PARAMETER;
	}

	HANDLE fileHandle;
	fileHandle = CreateFileA(
		fileName,
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (INVALID_HANDLE_VALUE == fileHandle)
	{
		CloseHandle(fileHandle);
		return (HANDLE)ERROR_INVALID_HANDLE;
	}

	return fileHandle;
}
