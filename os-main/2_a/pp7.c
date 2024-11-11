#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid;
    char *msg;
    int n;

    printf("Program starts\n");

    pid = fork();

    switch (pid) {
        case -1:
            // Fork error
            printf("Fork error\n");
            exit(-1);
        case 0:
            // Child process
            msg = "This is the child process";
            n = 5;
            break;
        default:
            // Parent process
            msg = "This is the parent process";
            n = 3;
            break;
    }

    // Print the message 'n' times
    while (n > 0) {
        puts(msg);
        sleep(1);
        n--;
    }

    return 0;
}
