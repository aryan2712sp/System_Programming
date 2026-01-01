///////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Program Name :- Assignment_4.1_.c
//    Description  :- Write a program to copy file byte-to-byte into another file.
//    Author Name  :- Aryan Shailendrasingh Pardeshi
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    FILE *src, *dest;
    char buffer;
 
    if (argc != 3)
    {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    src = fopen(argv[1], "r");
    if (src == NULL)
    {
        perror("Error opening source file");
        return 1;
    }

    dest = fopen(argv[2], "w");
    if (dest == NULL)
    {
        perror("Error opening destination file");
        fclose(src);
        return 1;
    }

    while ((buffer = fgetc(src)) != EOF)
    {
        if (fputc(buffer, dest) == EOF)
        {
            perror("Error writing to destination file");
            fclose(src);
            fclose(dest);
            return 1;
        }
    }

    if (ferror(src))
    {
        perror("Error reading source file");
    }

    fclose(src);
    fclose(dest);

    printf("File copied successfully.\n");
    return 0;
}
