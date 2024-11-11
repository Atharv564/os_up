#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_SIZE 10

// Function to print the array
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Bubble sort function to sort the array
void bubble_sort(int arr[], int n) {
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int arr[MAX_SIZE];
    int n;

    // Input array size
    printf("Enter the number of integers to sort (max %d): ", MAX_SIZE);
    scanf("%d", &n);

    // Input array elements
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Sort the array using bubble sort
    bubble_sort(arr, n);
    printf("\nParent process sorted the array:\n");
    print_array(arr, n);

    // Fork to create child process
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process

        // Convert the array to string arguments
        char *args[MAX_SIZE + 3];  // +3 for program name and the argument count
        args[0] = "./child_program"; // Name of the new program to load via execve
        args[1] = NULL; // Argument for child program
        
        // Convert the array elements to string and add them to args
        for (int i = 0; i < n; i++) {
            args[i + 2] = (char *)malloc(10 * sizeof(char)); // Allocate memory for each number
            sprintf(args[i + 2], "%d", arr[i]); // Convert integer to string
        }

        // Execute the child program
        execve(args[0], args, NULL);
        // If execve fails
        perror("execve failed");
        exit(1);
    } else {
        // Parent process waits for the child process to finish
        wait(NULL);
        printf("\nParent process has finished execution.\n");
    }

    return 0;
}
