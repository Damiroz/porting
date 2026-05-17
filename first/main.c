/*
Windows API → Linux API

CreateFile  → open
ReadFile    → read
CloseHandle → close
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {

    int file;
    char buffer[100];
    ssize_t bytesRead;

    file = open("test.txt", O_RDONLY);

    if (file < 0) {
        printf("File open error\n");
        return 1;
    }

    bytesRead = read(file, buffer, sizeof(buffer) - 1);

    if (bytesRead < 0) {
        printf("File read error\n");
        close(file);
        return 1;
    }

    buffer[bytesRead] = '\0';

    printf("%s\n", buffer);

    close(file);

    return 0;
}