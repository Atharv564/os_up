#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_REQUESTS 100

void sstf(int requests[], int n, int initial) {
    bool visited[MAX_REQUESTS] = { false };
    int current = initial;
    int total_head_movement = 0;

    for (int count = 0; count < n; count++) {
        int min_index = -1;
        int min_distance = 10000; // A large number

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int distance = abs(requests[i] - current);
                if (distance < min_distance) {
                    min_distance = distance;
                    min_index = i;
                }
            }
        }

        visited[min_index] = true;
        total_head_movement += min_distance;
        current = requests[min_index];
        printf("Servicing request at: %d\n", current);
    }
    printf("Total head movement: %d\n", total_head_movement);
}

int main() {
    int requests[MAX_REQUESTS];
    int n, initial;

    printf("Enter the number of requests: ");
    scanf("%d", &n);
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter initial head position: ");
    scanf("%d", &initial);

    sstf(requests, n, initial);
    return 0;
}

