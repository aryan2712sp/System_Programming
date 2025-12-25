///////////////////////////////////////////////////////////////////////////////////////////////////
//
//   Program Name :- Assignment_1.3_.c
//   Description  :- Write a program to accept a file from user and check file permission.
//   Author Name  :- Aryan Shailendrasingh Pardeshi
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main()
{
    char fname[100];
    char mode[10];
    int iRet = 0;
    int iFlag = 0;

    printf("Enter file name: ");
    scanf("%s", fname);

    printf("Enter access mode (read / write / execute): ");
    scanf("%s", mode);

    if (strcmp(mode, "read") == 0)
    {
        iFlag = R_OK;
    }
    else if (strcmp(mode, "write") == 0)
    {
        iFlag = W_OK;
    }
    else if (strcmp(mode, "execute") == 0)
    {
        iFlag = X_OK;
    }
    else
    {
        printf("Invalid access mode\n");
        return -1;
    }

    iRet = access(fname, iFlag);

    if (iRet == 0)
    {
        printf("Accessible\n");
    }
    else
    {
        printf("Not accessible\n");
        perror("Reason");
    }

    return 0;
}
