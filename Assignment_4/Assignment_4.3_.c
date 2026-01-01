///////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Program Name :- Assignment_4.2_.c
//    Description  :- Write a program to copy file using pwrite() and pread() without changing file offset.
//    Author Name  :- Aryan Shailendrasingh Pardeshi
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    int fd_src, fd_dest;
    ssize_t bytes_read, bytes_written;
    off_t offset = 0;
    char buffer[BUFFER_SIZE];

    if (argc != 3)
    {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    fd_src = open(argv[1], O_RDONLY);
    if (fd_src == -1)
    {
        perror("Error opening source file");
        return 1;
    }

    fd_dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_dest == -1)
    {
        perror("Error opening destination file");
        close(fd_src);
        return 1;
    }

    while ((bytes_read = pread(fd_src, buffer, BUFFER_SIZE, offset)) > 0)
    {
        bytes_written = pwrite(fd_dest, buffer, bytes_read, offset);
        if (bytes_written != bytes_read)
        {
            perror("Error writing to destination file");
            close(fd_src);
            close(fd_dest);
            return 1;
        }

        offset += bytes_read;
    }

    if (bytes_read < 0)
    {
        perror("Error reading source file");
    }

    close(fd_src);
    close(fd_dest);

    printf("File copied successfully using pread() and pwrite().\n");
    return 0;
}
