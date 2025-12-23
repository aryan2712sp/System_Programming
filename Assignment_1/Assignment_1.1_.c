#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main()
{
    int fd;
    char filename[100];

    printf("Enter the file name: ");
    scanf("%s", filename);

    fd = open(filename, O_RDWR);

    if (fd == -1)
    {
        perror("Unable to open file");
        return -1;   
    }
    else
    {
        printf("File opened successfully with fd = %d\n", fd);
        return fd;   
    }
}
