#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_REQUESTS 100

void scan(int requests[], int n, int initial, int total_cylinders) {
    int total_head_movement = 0;
    int current = initial;

    // Sort the requests in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    // First service requests to the right of the current position
    printf("Servicing requests to the right of the head position:\n");
    for (int i = 0; i < n; i++) {
        if (requests[i] >= current) {
            printf("Servicing request at: %d\n", requests[i]);
            total_head_movement += abs(current - requests[i]);
            current = requests[i];
        }
    }

    // If there are requests remaining on the left side, move to the highest cylinder
    if (current != total_cylinders - 1) {
        printf("Moving to the end of the disk at: %d\n", total_cylinders - 1);
        total_head_movement += abs(current - (total_cylinders - 1));
        current = total_cylinders - 1;
    }

    // Service requests to the left of the initial position
    printf("Servicing requests to the left of the head position:\n");
    for (int i = n - 1; i >= 0; i--) {
        if (requests[i] < initial) {
            printf("Servicing request at: %d\n", requests[i]);
            total_head_movement += abs(current - requests[i]);
            current = requests[i];
        }
    }

    printf("Total head movement: %d\n", total_head_movement);
}

int main() {
    int requests[MAX_REQUESTS];
    int n, initial, total_cylinders;

    printf("Enter the number of requests: ");
    scanf("%d", &n);
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter initial head position: ");
    scanf("%d", &initial);
    printf("Enter total number of cylinders: ");
    scanf("%d", &total_cylinders);

    scan(requests, n, initial, total_cylinders);
    return 0;
}

