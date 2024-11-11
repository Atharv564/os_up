#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void bubbleSort(int arr[], int n) 
{
    printf("\nSorting Started\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("\n\nSorting Completed!\n");
}

// To Convert Integer to Char*
void tostring(char str[], int num) {
    int i, rem, len = 0, n;
    n = num;
    while (n != 0) {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++) {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

int main(int argc, char *argv[]) {
    printf("\nThis is the main process:");
    printf("\nProcess Id: %d", getpid());
    printf("\nParent Id: %d", getppid());
    
    int arr[] = {10, 5, 1, 60, 20};
    int n = 5;
    printf("\n\nSorting Array using Bubble Sort:");
    bubbleSort(arr, n);
    
    printf("\nForking the current process:");
    pid_t cpid = fork();
    
    if (cpid > 0) {
        // Parent process
        printf("\n\nParent is Running:\nParentID: %d\nIt's ID: %d\n", getppid(), getpid());
        printf("\nParent is waiting for child to complete!\n\n");
        wait(NULL);  // Wait for child to complete
        printf("\n\nParent is Exiting!!\n");
    } else if (cpid == 0) {
        // Child process
        printf("\n\nChild is running:\nParentID: %d\nIt's ID: %d\n", getppid(), getpid());
        
        char *arrChar[n + 2];  // Array to hold arguments for execv

        // Creating ASCII Character Array to Pass as command line Argument
        arrChar[0] = (char *)"child";   // Arg 0 = name of executable file
        for (int i = 0; i < n; i++) {
            char *string = (char *)malloc(sizeof(char) * 20);
            tostring(string, arr[i]);
            arrChar[i + 1] = string;
        }
        arrChar[n + 1] = NULL;
        
        printf("\n\nChild Calling EXECV System Call:\n");
        execv("./child", arrChar);  // Execute child program
        printf("\n\nChild EXECV Call Complete\n");
        
        // Free allocated memory
        for (int i = 1; i <= n; i++) {
            free(arrChar[i]);
        }
        
        printf("\n\nChild Execution Complete\n");
    } else if (cpid < 0) {
        printf("Error during fork!\n");
    }

    return 0;
}
