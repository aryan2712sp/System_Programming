////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Program Name :- Assignment_2.5_.c 
//    Description  :- Write a program to fid largest file in directory and print its bytes.
//    Author Name  :- Aryan Shailendrasingh Pardeshi
//
////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *entry;
    struct stat sb;
    char path[1024];

    char largest_file[1024] = "";
    off_t max_size = 0;

    if (argc != 2) {
        printf("Usage: %s <directory_name>\n", argv[0]);
        return 1;
    }

    dir = opendir(argv[1]);
    if (dir == NULL) 
    {
        perror("opendir");
        return 1;
    }

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

        if (S_ISREG(sb.st_mode)) {
            if (sb.st_size > max_size) 
            {
                max_size = sb.st_size;
                strncpy(largest_file, entry->d_name, sizeof(largest_file));
                largest_file[sizeof(largest_file)-1] = '\0';
            }
        }
    }

    closedir(dir);

    if (max_size > 0) 
    {
        printf("Largest file: %s\n", largest_file);
        printf("Size: %ld bytes\n", max_size);
    }
    else 
    {
        printf("No regular files found in directory '%s'\n", argv[1]);
    }

    return 0;
}
