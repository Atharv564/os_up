#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Function to calculate the absolute difference between two numbers
int absolute(int a, int b) {
    return abs(a - b);
}

// Comparison function used by qsort for sorting the requests in ascending order
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// SSTF (Shortest Seek Time First) Disk Scheduling Algorithm
void SSTF(int arr[], int n, int head) {
    int seek_count = 0, distance, cur_track;
    int visited[MAX] = {0};  // Array to mark visited requests

    // Find the closest request to the initial head position
    for (int i = 0; i < n; i++) {
        int min_distance = 999999;  // A large number
        int index = -1;

        // Find the closest unvisited request
        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                distance = absolute(arr[j], head);
                if (distance < min_distance) {
                    min_distance = distance;
                    index = j;
                }
            }
        }

        // Update the head and seek count
        visited[index] = 1;
        cur_track = arr[index];
        seek_count += absolute(cur_track, head);
        head = cur_track;  // Move the head to the current request
    }

    printf("Total Seek Time (SSTF): %d\n", seek_count);
}

// SCAN Disk Scheduling Algorithm
void SCAN(int arr[], int n, int head, int disk_size) {
    int seek_count = 0;
    int left[MAX], right[MAX];
    int left_count = 0, right_count = 0;

    // Divide the requests into two categories: left and right of the head
    for (int i = 0; i < n; i++) {
        if (arr[i] < head) {
            left[left_count++] = arr[i];
        } else {
            right[right_count++] = arr[i];
        }
    }

    // Sort both left and right request arrays
    qsort(left, left_count, sizeof(int), compare);
    qsort(right, right_count, sizeof(int), compare);

    // Move the head to the rightmost request first, then reverse direction
    // Seek to the rightmost request
    for (int i = 0; i < right_count; i++) {
        seek_count += absolute(head, right[i]);
        head = right[i];
    }

    // Now move to the leftmost request
    for (int i = left_count - 1; i >= 0; i--) {
        seek_count += absolute(head, left[i]);
        head = left[i];
    }

    printf("Total Seek Time (SCAN): %d\n", seek_count);
}

// C-Look Disk Scheduling Algorithm
void C_Look(int arr[], int n, int head, int disk_size) {
    int seek_count = 0;
    int left[MAX], right[MAX];
    int left_count = 0, right_count = 0;

    // Divide the requests into two categories: left and right of the head
    for (int i = 0; i < n; i++) {
        if (arr[i] < head) {
            left[left_count++] = arr[i];
        } else {
            right[right_count++] = arr[i];
        }
    }

    // Sort both left and right request arrays
    qsort(left, left_count, sizeof(int), compare);
    qsort(right, right_count, sizeof(int), compare);

    // Move the head to the rightmost request first, then go to the leftmost request without reversing direction
    for (int i = 0; i < right_count; i++) {
        seek_count += absolute(head, right[i]);
        head = right[i];
    }

    // Now move to the leftmost request in a circular manner
    if (left_count > 0) {
        seek_count += absolute(head, left[0]);
        head = left[0];
    }

    printf("Total Seek Time (C-Look): %d\n", seek_count);
}

int main() {
    int arr[] = {98, 183, 41, 122, 14, 124, 65, 67};
    int n = sizeof(arr) / sizeof(arr[0]);
    int head = 53; // Initial head position
    int disk_size = 200; // Total number of cylinders (example)

    printf("Disk Scheduling Algorithms:\n");

    // SSTF Scheduling
    SSTF(arr, n, head);

    // SCAN Scheduling
    SCAN(arr, n, head, disk_size);

    // C-Look Scheduling
    C_Look(arr, n, head, disk_size);

    return 0;
}

