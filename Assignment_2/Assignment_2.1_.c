////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Program Name :- Assignment_2.1_.c 
//    Description  :- Write a program to read a file and print its bytes written.
//    Author Name  :- Aryan Shailendrasingh Pardeshi
//
////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) 
{
    int fd;
    ssize_t n;
    char buffer[BUFFER_SIZE];
    long total = 0;

    if (argc != 2) 
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) 
    {
        perror("open");
        return 1;
    }

    while ((n = read(fd, buffer, BUFFER_SIZE)) > 0) 
    {
        write(STDOUT_FILENO, buffer, n);
        total = total + n;
    }

    if (n < 0) {
        perror("read");
        close(fd);
        return 1;
    }

    close(fd);

    printf("\n\nTotal bytes read: %ld\n", total);
    return 0;
}
