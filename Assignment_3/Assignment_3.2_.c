////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Program Name :- Assignment_3.2_.c 
//    Description  :- Write a program to print file's absolute path.
//    Author Name  :- Aryan Shailendrasingh Pardeshi
//
////////////////////////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <directory_name> <file_name>\n", argv[0]);
        return 1;
    }

    char *dir_name = argv[1];
    char *file_name = argv[2];
    DIR *dir;
    struct dirent *entry;
    char full_path[1024];

    dir = opendir(dir_name);
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    int found = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, file_name) == 0) {
            // Build full absolute path
            if (realpath(entry->d_name, full_path) == NULL) {
                perror("realpath");
            } else {
                printf("File found: %s\n", full_path);
            }
            found = 1;
            break;
        }
    }

    closedir(dir);

    if (!found) {
        printf("File '%s' not found in directory '%s'\n", file_name, dir_name);
    }

    return 0;
}
