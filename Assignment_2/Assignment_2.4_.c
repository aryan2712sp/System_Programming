////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Program Name :- Assignment_2.4_.c 
//    Description  :- Write a program to list files and its type.
//    Author Name  :- Aryan Shailendrasingh Pardeshi
//
////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void print_type(mode_t mode) 
{
    if (S_ISREG(mode))
        printf("Regular");
    else if (S_ISDIR(mode))
        printf("Directory");
    else if (S_ISLNK(mode))
        printf("Link");
    else if (S_ISFIFO(mode))
        printf("FIFO");
    else if (S_ISSOCK(mode))
        printf("Socket");
    else if (S_ISCHR(mode))
        printf("Char");
    else if (S_ISBLK(mode))
        printf("Block");
    else
        printf("Unknown");
}

int main(int argc, char *argv[]) 
{
    DIR *dir;
    struct dirent *entry;
    struct stat sb;
    char path[1024];

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

    printf("Files in directory '%s' with type:\n", argv[1]);

    while ((entry = readdir(dir)) != NULL) 
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(path, sizeof(path), "%s/%s", argv[1], entry->d_name);

        if (lstat(path, &sb) == -1) 
        {
            perror("lstat");
            continue;
        }

        printf("%-30s : ", entry->d_name);
        print_type(sb.st_mode);
        printf("\n");
    }

    closedir(dir);
    return 0;
}
