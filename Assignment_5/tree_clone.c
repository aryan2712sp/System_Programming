///////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Program Name :- tree_clone.c
//    Description  :- Write a program that prints directory into tree like.
//    Author Name  :- Aryan Shailendrasingh Pardeshi
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

void print_indent(int depth)
{
    for (int i = 0; i < depth; i++)
        printf("    ");
}

void tree(const char *path, int depth)
{
    DIR *dir;
    struct dirent *entry;
    struct stat st;
    char fullpath[1024];

    dir = opendir(path);
    if (dir == NULL)
    {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        if (lstat(fullpath, &st) == -1)
        {
            perror("lstat");
            continue;
        }

        print_indent(depth);

        if (S_ISDIR(st.st_mode))
        {
            printf("[D] %s/\n", entry->d_name);
            tree(fullpath, depth + 1);
        }
        else if (S_ISLNK(st.st_mode))
        {
            printf("[L] %s\n", entry->d_name);
        }
        else if (S_ISREG(st.st_mode))
        {
            printf("[F] %s\n", entry->d_name);
        }
        else
        {
            printf("[?] %s\n", entry->d_name);
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

    printf("[D] %s/\n", argv[1]);
    tree(argv[1], 1);

    return 0;
}
