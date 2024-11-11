#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // argc includes the program name, so we start from argv[1]
    printf("Child process received the array:\n");
    
    // Print the array in reverse order
    for (int i = argc - 1; i >= 2; i--) {
        printf("%s ", argv[i]);  // Print each element (argv[i] is a string representation)
    }
    printf("\n");

    return 0;
}
