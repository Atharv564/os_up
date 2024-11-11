#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t child_pid;

    // Print the main process ID
    printf("The main program process ID is %d\n", (int)getpid());

    // Create a child process using fork()
    child_pid = fork();

    if (child_pid != 0) {
        // Parent process
        printf("This is the parent process ID, with id %d\n", (int)getpid());
        printf("The child process ID is %d\n", (int)child_pid);
    } else {
        // Child process
        printf("This is the child process ID, with id %d\n", (int)getpid());
    }

    return 0;
}
