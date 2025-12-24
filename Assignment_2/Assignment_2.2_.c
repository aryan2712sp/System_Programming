////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Program Name :- Assignment_2.2_.c 
//    Description  :- Write a program to enter name of string and print it in number of bytes written.
//    Author Name  :- Aryan Shailendrasingh Pardeshi
//
////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) 
{
    int fd;
    char buffer[BUF_SIZE];
    ssize_t bytes_written;

    if (argc != 2) 
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    printf("Enter string to write: ");
    fflush(stdout);

    if (fgets(buffer, BUF_SIZE, stdin) == NULL) 
    {
        perror("fgets");
        return 1;
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') 
    {
        buffer[len - 1] = '\0';
        len--;
    }

    fd = open(argv[1], O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd < 0) 
    {
        perror("open");
        return 1;
    }

    bytes_written = write(fd, buffer, len);
    if (bytes_written < 0) 
    {
        perror("write");
        close(fd);
        return 1;
    }

    close(fd);

    printf("Number of bytes written: %zd\n", bytes_written);
    return 0;
}
