///////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Program Name :- Assignment_4.2_.c
//    Description  :- Write a program to copy multiple files into one file.
//    Author Name  :- Aryan Shailendrasingh Pardeshi
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    int fd_out, fd_in;
    ssize_t bytes_read;
    char buffer[BUFFER_SIZE];
    int i;

    if (argc < 3)
    {
        printf("Usage: %s <output_file> <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    fd_out = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out == -1)
    {
        perror("Error opening output file");
        return 1;
    }

    for (i = 2; i < argc; i++)
    {
        fd_in = open(argv[i], O_RDONLY);
        if (fd_in == -1)
        {
            perror(argv[i]);
            continue;  
        }

        while ((bytes_read = read(fd_in, buffer, BUFFER_SIZE)) > 0)
        {
            if (write(fd_out, buffer, bytes_read) != bytes_read)
            {
                perror("Write error");
                close(fd_in);
                close(fd_out);
                return 1;
            }
        }

        if (bytes_read < 0)
        {
            perror("Read error");
        }

        close(fd_in);
    }

    close(fd_out);

    printf("Files merged successfully.\n");
    return 0;
}
