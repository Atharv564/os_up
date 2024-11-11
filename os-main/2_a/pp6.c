#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t child_pid;

    // Create a child process
    child_pid = fork();

    if (child_pid > 0) {
        // Parent process: Sleep for 10 seconds
        sleep(10);
    } else {
        // Child process: Exit immediately
        exit(0);
    }

    return 0;
}
