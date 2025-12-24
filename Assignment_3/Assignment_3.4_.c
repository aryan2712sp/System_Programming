////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Program Name :- Assignment_3.4_.c 
//    Description  :- Write a program to to delete empty files from a directory .
//    Author Name  :- Aryan Shailendrasingh Pardeshi
//
////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        printf("Usage: %s <directory_name>\n", argv[0]);
        return 1;
    }

    char *dir_name = argv[1];
    DIR *dir = opendir(dir_name);
    if (!dir) 
    {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    struct stat sb;
    char path[1024];
    int deleted_count = 0;

    while ((entry = readdir(dir)) != NULL) 
    {

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(path, sizeof(path), "%s/%s", dir_name, entry->d_name);

        if (lstat(path, &sb) == -1) 
        {
            perror("lstat");
            continue;
        }

        if (S_ISREG(sb.st_mode) && sb.st_size == 0) 
        {
            if (unlink(path) == 0) {
                printf("Deleted: %s\n", entry->d_name);
                deleted_count++;
            } else {
                perror("unlink");
            }
        }
    }

    closedir(dir);

    printf("Total empty files deleted: %d\n", deleted_count);
    return 0;
}
