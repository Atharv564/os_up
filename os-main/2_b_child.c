#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    /* argv[0] is the program name */
    if (argc < 2) {
        printf("No numbers to process.\n");
        return 1;
    }
    
    int *data = (int *) malloc(argc * sizeof(int));  // Allocate memory for the arguments
    if (data == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("\nArgc: %d", argc);
    for (int i = 1; i < argc; i++) {
        data[i] = atoi(argv[i]);  // Convert arguments to integers
    }

    // Printing elements in reverse
    printf("\nPrinting elements in reverse:");
    for (int i = argc - 1; i > 0; i--) {
        printf(" %d ", data[i]);
    }
    printf("\n\nEXECV task completed\n");

    free(data);  // Free the allocated memory
    return 0;
}
