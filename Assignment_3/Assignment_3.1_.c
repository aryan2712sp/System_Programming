////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Program Name :- Assignment_3.1_.c 
//    Description  :- Write a program to copy a file successfully.
//    Author Name  :- Aryan Shailendrasingh Pardeshi
//
////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) 
{
    int src_fd, dest_fd;
    ssize_t n;
    char buffer[BUFFER_SIZE];
    struct stat sb;

    if (argc != 3) 
    {
        printf("Usage: %s <source_file> <dest_file>\n", argv[0]);
        return 1;
    }

    src_fd = open(argv[1], O_RDONLY);
    if (src_fd < 0) 
    {
        perror("open source");
        return 1;
    }

    dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) 
    {
        perror("open destination");
        close(src_fd);
        return 1;
    }
    if (stat(argv[1], &sb) == 0) 
    {
        chmod(argv[2], sb.st_mode);
    }

    while ((n = read(src_fd, buffer, BUFFER_SIZE)) > 0) 
    {
        if (write(dest_fd, buffer, n) != n) {
            perror("write");
            close(src_fd);
            close(dest_fd);
            return 1;
        }
    }

    if (n < 0) 
    {
        perror("read");
    }

    close(src_fd);
    close(dest_fd);

    printf("File copied successfully!\n");
    return 0;
}
