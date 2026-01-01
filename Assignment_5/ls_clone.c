///////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Program Name :- ls_clone.c
//    Description  :- Write a program that accepts directory path from user and display all information of it.
//    Author Name  :- Aryan Shailendrasingh Pardeshi
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void print_permissions(mode_t mode)
{
    char perm[10];

    perm[0] = (mode & S_IRUSR) ? 'r' : '-';
    perm[1] = (mode & S_IWUSR) ? 'w' : '-';
    perm[2] = (mode & S_IXUSR) ? 'x' : '-';
    perm[3] = (mode & S_IRGRP) ? 'r' : '-';
    perm[4] = (mode & S_IWGRP) ? 'w' : '-';
    perm[5] = (mode & S_IXGRP) ? 'x' : '-';
    perm[6] = (mode & S_IROTH) ? 'r' : '-';
    perm[7] = (mode & S_IWOTH) ? 'w' : '-';
    perm[8] = (mode & S_IXOTH) ? 'x' : '-';
    perm[9] = '\0';

    printf("%s", perm);
}

const char *get_type(mode_t mode)
{
    if (S_ISREG(mode))  return "file";
    if (S_ISDIR(mode))  return "dir";
    if (S_ISLNK(mode))  return "link";
    return "other";
}

int main(int argc, char *argv[])
{
    DIR *dir;
    struct dirent *entry;
    struct stat st;
    char path[1024];
    char timebuf[64];

    if (argc != 2)
    {
        printf("Usage: %s <directory_path>\n", argv[0]);
        return 1;
    }

    dir = opendir(argv[1]);
    if (dir == NULL)
    {
        perror("opendir");
        return 1;
    }

    printf("%-20s %-6s %-10s %-10s %-20s\n",
           "NAME", "TYPE", "SIZE", "PERMS", "LAST MODIFIED");
    printf("---------------------------------------------------------------------\n");

    while ((entry = readdir(dir)) != NULL)
    {

        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(path, sizeof(path), "%s/%s", argv[1], entry->d_name);

        if (lstat(path, &st) == -1)
        {
            perror("lstat");
            continue;
        }

        strftime(timebuf, sizeof(timebuf),
                 "%Y-%m-%d %H:%M",
                 localtime(&st.st_mtime));

        printf("%-20s %-6s %-10ld ",
               entry->d_name,
               get_type(st.st_mode),
               (long)st.st_size);

        print_permissions(st.st_mode);
        printf(" %-20s\n", timebuf);
    }

    closedir(dir);
    return 0;
}
