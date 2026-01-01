///////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Program Name :- dir_report.c
//    Description  :- Write a program that calculates total number of files in directory, largest file, total size, total directories.
//    Author Name  :- Aryan Shailendrasingh Pardeshi
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

long total_files = 0;
long total_dirs = 0;
long long total_size = 0;

char largest_file[1024] = "";
long long largest_size = 0;

void scan_dir(const char *path)
{
    DIR *dir;
    struct dirent *entry;
    struct stat st;
    char fullpath[1024];

    dir = opendir(path);
    if (dir == NULL)
        return;

    total_dirs++;

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        if (lstat(fullpath, &st) == -1)
            continue;

        if (S_ISREG(st.st_mode))
        {
            total_files++;
            total_size += st.st_size;

            if (st.st_size > largest_size)
            {
                largest_size = st.st_size;
                strncpy(largest_file, entry->d_name, sizeof(largest_file));
            }
        }
        else if (S_ISDIR(st.st_mode))
        {
            scan_dir(fullpath);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <directory_path>\n", argv[0]);
        return 1;
    }

    scan_dir(argv[1]);

    printf("Files      : %ld\n", total_files);
    printf("Dirs       : %ld\n", total_dirs);
    printf("Total Size : %lld bytes\n", total_size);

    if (largest_size > 0)
        printf("Largest    : %s (%lld bytes)\n", largest_file, largest_size);
    else
        printf("Largest    : None\n");

    return 0;
}
