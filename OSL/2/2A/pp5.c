#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t child_pid;

    // Fork the process
    child_pid = fork();

    if (child_pid == -1) {
        perror("Failed to fork");
        return 1;
    }

    if (child_pid == 0) {
        // Child process: Execute "ls -l" using execl
        execl("/bin/ls", "ls", "-l", NULL);
        perror("Child failed to exec ls");
        return 1;
    }

    // Parent process: Wait for the child process to complete
    if (child_pid != wait(NULL)) {
        perror("Parent failed to wait due to signal or error");
        return 1;
    }

    return 0;
}
