#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void main(void) {
    int child_pid;
    int status;

    // Wait for a child process to finish
    child_pid = wait(&status);

    if (child_pid == -1) {
        perror("Failed to wait for child");
    } else if (WIFEXITED(status)) {
        printf("Child %ld terminated with return status %d\n", (long)child_pid, WEXITSTATUS(status));
    }
}

