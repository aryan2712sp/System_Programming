#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    char filename[100];
    int fd, N, bytesRead;
    char *buffer;

    printf("Enter file name: ");
    scanf("%s", filename);

    printf("Enter number of bytes to read: ");
    scanf("%d", &N);

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Unable to open file");
        return -1;
    }

    buffer = (char *)malloc(N + 1);
    if (!buffer)
    {
        printf("Memory allocation failed\n");
        close(fd);
        return -1;
    }

    bytesRead = read(fd, buffer, N);
    if (bytesRead == -1)
    {
        perror("Read error");
        free(buffer);
        close(fd);
        return -1;
    }
    buffer[bytesRead] = '\0';

    printf("\nRead %d bytes:\n", bytesRead);
    printf("%s\n", buffer);

    free(buffer);
    close(fd);

    return 0;
}
