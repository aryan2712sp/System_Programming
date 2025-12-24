////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Program Name :- Assignment_3.3_.c 
//    Description  :- Write a program to move files from one directory to another directory.
//    Author Name  :- Aryan Shailendrasingh Pardeshi
//
////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int copy_file(const char *src, const char *dest) 
{
    int src_fd = open(src, O_RDONLY);
    if (src_fd < 0) return -1;

    int dest_fd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) 
    {
        close(src_fd);
        return -1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t n;
    while ((n = read(src_fd, buffer, BUFFER_SIZE)) > 0) 
    {
        if (write(dest_fd, buffer, n) != n) {
            close(src_fd);
            close(dest_fd);
            return -1;
        }
    }

    close(src_fd);
    close(dest_fd);
    return (n < 0) ? -1 : 0;
}

int main(int argc, char *argv[]) 
{
    if (argc != 3) 
    {
        printf("Usage: %s <source_dir> <destination_dir>\n", argv[0]);
        return 1;
    }

    char *src_dir = argv[1];
    char *dest_dir = argv[2];
    DIR *dir = opendir(src_dir);
    if (!dir) 
    {
        perror("opendir source");
        return 1;
    }

    struct dirent *entry;
    struct stat sb;
    char src_path[1024], dest_path[1024];
    int moved_count = 0;

    while ((entry = readdir(dir)) != NULL) 
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(src_path, sizeof(src_path), "%s/%s", src_dir, entry->d_name);
        if (lstat(src_path, &sb) == -1) 
        {
            perror("lstat");
            continue;
        }

        if (S_ISREG(sb.st_mode)) 
        {
            snprintf(dest_path, sizeof(dest_path), "%s/%s", dest_dir, entry->d_name);

            if (rename(src_path, dest_path) == 0) 
            {
                moved_count++;
            } else 
            {
            
                if (errno == EXDEV) 
                {
                    if (copy_file(src_path, dest_path) == 0) 
                    {
                        unlink(src_path);  
                        moved_count++;
                    } 
                    else 
                    {
                        fprintf(stderr, "Failed to move %s\n", src_path);
                    }
                } 
                else 
                {
                    perror("rename");
                }
            }
        }
    }

    closedir(dir);
    printf("Total files moved: %d\n", moved_count);
    return 0;
}
