#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10

// Structure to represent a process
typedef struct {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int remaining;  // Remaining burst time for Round Robin
    int finish_time; // Completion time
    int turn_around; // Turnaround time
    int waiting;     // Waiting time
} Process;

// Function to sort processes by arrival time (for both algorithms)
void sort_by_arrival(Process p[], int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].arrival > p[j].arrival) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

// Round Robin Scheduling
void round_robin(Process p[], int n, int quantum) {
    int completed = 0, current_time = 0;
    int queue[MAX_PROCESSES], front = 0, rear = 0;
    
    // Initialize queue with processes
    for (int i = 0; i < n; i++) {
        p[i].remaining = p[i].burst;
    }

    while (completed != n) {
        // Add processes that have arrived and are not yet completed to the queue
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= current_time && p[i].remaining > 0) {
                int already_in_queue = 0;
                for (int j = front; j < rear; j++) {
                    if (queue[j] == i) {
                        already_in_queue = 1;
                        break;
                    }
                }
                // Only add process to queue if it is not already there
                if (!already_in_queue) {
                    queue[rear++] = i;
                }
            }
        }

        // Execute the first process in the queue
        if (front < rear) {
            int i = queue[front++];
            if (p[i].remaining > quantum) {
                p[i].remaining -= quantum;
                current_time += quantum;
                // Re-add the process to the queue
                queue[rear++] = i;
            } else {
                current_time += p[i].remaining;
                p[i].finish_time = current_time;
                p[i].turn_around = p[i].finish_time - p[i].arrival;
                p[i].waiting = p[i].turn_around - p[i].burst;
                p[i].remaining = 0;
                completed++;
            }
        } else {
            // If the queue is empty (no process can run), just increment the time
            current_time++;
        }
    }
}

// Function to calculate and print average times
void print_avg_times(Process p[], int n) {
    int total_waiting = 0, total_turnaround = 0;

    printf("\nProcess ID\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].finish_time, p[i].turn_around, p[i].waiting);
        total_waiting += p[i].waiting;
        total_turnaround += p[i].turn_around;
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround / n);
}

int main() {
    int n, choice, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process p[n];
    
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;  // Process ID
        printf("\nEnter arrival time and burst time for process %d: ", i + 1);
        scanf("%d%d", &p[i].arrival, &p[i].burst);
        p[i].remaining = p[i].burst; // Initialize remaining burst time
    }

    // Sort the processes by arrival time
    sort_by_arrival(p, n);

    printf("\nChoose Scheduling Algorithm:\n1. Round Robin\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("\nEnter time quantum for Round Robin: ");
        scanf("%d", &quantum);
        round_robin(p, n, quantum);
    } else {
        printf("Invalid choice!\n");
        return 0;
    }

    // Print results
    print_avg_times(p, n);

    return 0;
}
