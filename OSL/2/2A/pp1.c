#include <stdio.h>
#include <unistd.h>

int main() {
    // Print the process ID and parent process ID
    printf("The process ID is %d\n", (int)getpid());
    printf("The parent process ID is %d\n", (int)getppid());
    return 0;
}
