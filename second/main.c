#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 128

int main() {

    int fd;
    ssize_t bytesRead;
    char buffer[BUFFER_SIZE];

    fd = open("test.txt", O_RDONLY);

    if (fd < 0) {
        printf("Error: cannot open file\n");
        return 1;
    }

    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
        write(1, buffer, bytesRead);
    }

    if (bytesRead < 0) {
        printf("Error: read failed\n");
    }

    close(fd);

    return 0;
}