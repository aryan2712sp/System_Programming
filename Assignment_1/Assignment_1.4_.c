///////////////////////////////////////////////////////////////////////////////////////////////////
//
//   Program Name :- Assignment_1.4_.c
//   Description  :- Write a program to accept file from user and display its complete information.
//   Author Name  :- Aryan Shailendrasingh Pardeshi
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <fcntl.h>

void print_permissions(mode_t mode)
{
    printf("Permissions: ");
    printf( (S_ISDIR(mode)) ? "d" : "-");
    printf( (mode & S_IRUSR) ? "r" : "-");
    printf( (mode & S_IWUSR) ? "w" : "-");
    printf( (mode & S_IXUSR) ? "x" : "-");
    printf( (mode & S_IRGRP) ? "r" : "-");
    printf( (mode & S_IWGRP) ? "w" : "-");
    printf( (mode & S_IXGRP) ? "x" : "-");
    printf( (mode & S_IROTH) ? "r" : "-");
    printf( (mode & S_IWOTH) ? "w" : "-");
    printf( (mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

void print_file_type(mode_t mode)
{
    printf("File type: ");
    if (S_ISREG(mode)) printf("Regular file\n");
    else if (S_ISDIR(mode)) printf("Directory\n");
    else if (S_ISCHR(mode)) printf("Character device\n");
    else if (S_ISBLK(mode)) printf("Block device\n");
    else if (S_ISFIFO(mode)) printf("FIFO/pipe\n");
    else if (S_ISLNK(mode)) printf("Symbolic link\n");
    else if (S_ISSOCK(mode)) printf("Socket\n");
    else printf("Unknown\n");
}

int main()
{
    char fname[100];
    struct stat fileStat;

    printf("Enter file name: ");
    scanf("%s", fname);

    if(stat(fname, &fileStat) < 0)
    {
        perror("stat");
        return -1;
    }

    printf("\n--- File Information ---\n");
    printf("File Name: %s\n", fname);
    printf("File Size: %ld bytes\n", fileStat.st_size);
    printf("Inode Number: %ld\n", fileStat.st_ino);
    printf("Number of Hard Links: %ld\n", fileStat.st_nlink);
    printf("Owner UID: %d\n", fileStat.st_uid);
    printf("Owner GID: %d\n", fileStat.st_gid);

    print_permissions(fileStat.st_mode);
    print_file_type(fileStat.st_mode);

    printf("Last Access Time: %s", ctime(&fileStat.st_atime));
    printf("Last Modification Time: %s", ctime(&fileStat.st_mtime));

    return 0;
}
