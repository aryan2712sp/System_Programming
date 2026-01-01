///////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Program Name :- Assignment_4.2_.c
//    Description  :- Write a program to reverse a file.
//    Author Name  :- Aryan Shailendrasingh Pardeshi
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    int fd;
    off_t size;
    char ch;

    if (argc != 2)
    {
        printf("Usage: %s <file_name>\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    size = lseek(fd, 0, SEEK_END);
    if (size == -1)
    {
        perror("lseek error");
        close(fd);
        return 1;
    }

    for (off_t i = size - 1; i >= 0; i--)
    {
        lseek(fd, i, SEEK_SET);
        read(fd, &ch, 1);
        write(STDOUT_FILENO, &ch, 1);
    }

    close(fd);
    return 0;
}
