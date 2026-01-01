///////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Program Name :- Assignment_4.2_.c
//    Description  :- Write a program to copy file byte-to-byte into another file using offset.
//    Author Name  :- Aryan Shailendrasingh Pardeshi
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    FILE *src, *dest;
    long offset;
    int ch;

    if (argc != 4)
    {
        printf("Usage: %s <source_file> <destination_file> <offset>\n", argv[0]);
        return 1;
    }

    offset = atol(argv[3]);
    if (offset < 0)
    {
        printf("Error: Offset must be non-negative\n");
        return 1;
    }

    src = fopen(argv[1], "rb");
    if (src == NULL)
    {
        perror("Error opening source file");
        return 1;
    }

    if (fseek(src, offset, SEEK_SET) != 0)
    {
        perror("Error seeking source file");
        fclose(src);
        return 1;
    }

    dest = fopen(argv[2], "wb");
    if (dest == NULL)
    {
        perror("Error opening destination file");
        fclose(src);
        return 1;
    }

    while ((ch = fgetc(src)) != EOF)
    {
        fputc(ch, dest);
    }

    if (ferror(src))
    {
        perror("Error reading source file");
    }

    fclose(src);
    fclose(dest);

    printf("File copied from offset %ld successfully.\n", offset);
    return 0;
}
