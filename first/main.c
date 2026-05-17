#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

    pid_t pid = getpid();
    pid_t ppid = getppid();

    if (pid < 0) {
        printf("Error: cannot get PID\n");
        return 1;
    }

    if (ppid < 0) {
        printf("Error: cannot get PPID\n");
        return 1;
    }

    printf("=================================\n");
    printf("Process information (POSIX)\n");
    printf("=================================\n");
    printf("Current PID : %d\n", pid);
    printf("Parent PID  : %d\n", ppid);
    printf("=================================\n");

    return 0;
}