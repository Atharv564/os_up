#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>  // Include the correct header for wait()

#define SIZE 1024

void do_child_proc(int pfd[2]);
void do_parent_proc(int pfd[2]);

int main() {
    int pfd[2];
    int ret_val;
    pid_t pid;

    // Create a pipe
    ret_val = pipe(pfd);
    if (ret_val == -1) {
        perror("pipe error");
        exit(ret_val);
    }

    // Create a child process
    pid = fork();

    switch (pid) {
        case -1:
            // Fork error
            printf("Fork error\n");
            exit(pid);

        case 0:
            // Child process
            do_child_proc(pfd);
            exit(0);

        default:
            // Parent process
            do_parent_proc(pfd);
            exit(pid);
    }

    // Wait for the child process
    wait(NULL);  // This will now work without the implicit declaration warning

    return 0;
}

void do_child_proc(int pfd[2]) {
    int nread;
    char buf[SIZE];  // Allocate memory for buf
    int size = SIZE; // Set size for reading

    // Close the write end of the pipe
    close(pfd[1]);

    // Read from the pipe and print the data
    while ((nread = read(pfd[0], buf, size)) > 0) {
        printf("Child Read=%s\n", buf);
    }

    // Close the read end of the pipe
    close(pfd[0]);
    exit(0);
}

void do_parent_proc(int pfd[2]) {
    char ch;
    char buf[SIZE];  // Allocate memory for buf
    int i = 0;

    // Close the read end of the pipe
    close(pfd[0]);

    // Read input until newline is encountered
    while ((ch = getchar()) != '\n') {
        buf[i++] = ch;  // Store the character in the buffer
    }
    buf[i] = '\0';  // Null-terminate the string

    // Write the buffer to the pipe
    write(pfd[1], buf, strlen(buf) + 1);

    // Close the write end of the pipe
    close(pfd[1]);
}
