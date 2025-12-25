///////////////////////////////////////////////////////////////////////////////////////////////////
//
//   Program Name :- Assignment_1.2_.c
//   Description  :- Write a program to open a file according to given mode.
//   Author Name  :- Aryan Shailendrasingh Pardeshi
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd;
    char filename[100];
    char mode[5];
    int flags = 0;

    printf("Enter file name: ");
    scanf("%s", filename);

    printf("Enter mode (R / W / RW / A): ");
    scanf("%s", mode);


    if (strcmp(mode, "R") == 0)
    {
        flags = O_RDONLY;
    }
    else if (strcmp(mode, "W") == 0)
    {
        flags = O_WRONLY | O_CREAT | O_TRUNC;
    }
    else if (strcmp(mode, "RW") == 0)
    {
        flags = O_RDWR | O_CREAT;
    }
    else if (strcmp(mode, "A") == 0)
    {
        flags = O_WRONLY | O_APPEND | O_CREAT;
    }
    else
    {
        printf("Invalid mode entered.\n");
        return -1;
    }

    fd = open(filename, flags, 0777);

    if (fd == -1)
    {
        perror("Unable to open file");
        return -1;
    }
    else
    {
        printf("File opened successfully.\n");
        printf("File Descriptor: %d\n", fd);
    }

    close(fd);
    return 0;
}
