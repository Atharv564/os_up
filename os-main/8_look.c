#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void clook(int requests[], int n, int initial) {
    int total_head_movement = 0;
    int current = initial;

    // Sort requests in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    // Move to the right of initial position and service requests
    int start_index = -1;
    for (int i = 0; i < n; i++) {
        if (requests[i] >= current) {
            if (start_index == -1) start_index = i; // Mark where the first request >= initial occurs
            printf("Servicing request at: %d\n", requests[i]);
            total_head_movement += abs(current - requests[i]);
            current = requests[i];
        }
    }

    // Wrap around to the smallest request and service remaining requests
    if (start_index != 0) { // Only wrap around if there's a need
        total_head_movement += abs(current - requests[0]);
        current = requests[0];
        printf("Wrapping around to service request at: %d\n", requests[0]);

        // Service the remaining requests (skip the first one as it has been serviced already)
        for (int i = 1; i < start_index; i++) { // Start from index 1 to avoid servicing requests[0] again
            printf("Servicing request at: %d\n", requests[i]);
            total_head_movement += abs(current - requests[i]);
            current = requests[i];
        }
    }

    printf("Total head movement: %d\n", total_head_movement);
}

int main() {
    int requests[MAX_REQUESTS];
    int n, initial;

    // Input: number of requests, request list, and initial head position
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &initial);

    // Call the C-LOOK algorithm
    clook(requests, n, initial);

    return 0;
}

