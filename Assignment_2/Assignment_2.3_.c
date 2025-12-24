////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Program Name :- Assignment_2.3_.c 
//    Description  :- Write a program to list files current and previous directory.
//    Author Name  :- Aryan Shailendrasingh Pardeshi
//
////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
    DIR *dir;
    struct dirent *entry;

    if (argc != 2) 
    {
        printf("Usage: %s <directory_name>\n", argv[0]);
        return 1;
    }

    dir = opendir(argv[1]);
    if (dir == NULL) 
    {
        perror("opendir");
        return 1;
    }

    printf("Files in directory '%s':\n", argv[1]);

    while ((entry = readdir(dir)) != NULL) 
    {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        printf("%s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}
