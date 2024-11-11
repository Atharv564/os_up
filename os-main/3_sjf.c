#include <stdio.h>
// SJF with Arrival Time Consideration
int main() {
    int bt[20], at[20], p[20], wt[20], tat[20], i, j, n, total_wt = 0, total_tat = 0, pos, temp;
    float avg_wt, avg_tat;

    // Get the number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Get the arrival and burst times for each process
    printf("\nEnter Arrival Time and Burst Time for each process:\n");
    for(i = 0; i < n; i++) {
        printf("\np%d Arrival time: ", i + 1);  // Added space between inputs
        scanf("%d", &at[i]);
        printf("p%d Burst time: ", i + 1);
        scanf("%d", &bt[i]);
        p[i] = i + 1;  // Store process number
    }

    // Sort the processes based on arrival time, then burst time
    for(i = 0; i < n; i++) {
        pos = i;
        for(j = i + 1; j < n; j++) {
            if(at[j] < at[pos] || (at[j] == at[pos] && bt[j] < bt[pos])) {
                pos = j;
            }
        }

        // Swap burst time
        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        // Swap arrival time
        temp = at[i];
        at[i] = at[pos];
        at[pos] = temp;

        // Swap process number
        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }

    // Calculate waiting time for each process
    wt[0] = 0;  // Waiting time for the first process is 0
    int time = at[0];  // Start time is the arrival time of the first process
    for(i = 1; i < n; i++) {
        wt[i] = 0;
        // Wait time is the time spent waiting before the process starts
        for(j = 0; j < i; j++) {
            if(at[i] > time) {
                time = at[i];  // Move time to the next arrival time
            }
            wt[i] += bt[j];  // Add burst time of previous processes to waiting time
        }
        time += bt[i];  // Update time after finishing the process
        total_wt += wt[i];  // Add up total waiting time
    }

    avg_wt = (float)total_wt / n;  // Average waiting time
    total_wt = 0;

    // Display results
    printf("\nProcess\t Arrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];  // Turnaround time = burst time + waiting time
        total_tat += tat[i];  // Add up total turnaround time
        printf("p%d\t %d\t\t %d\t\t %d\t\t %d\n", p[i], at[i], bt[i], wt[i], tat[i]);
    }

    avg_tat = (float)total_tat / n;  // Average turnaround time

    // Display averages
    printf("\nAverage Waiting Time: %.2f", avg_wt);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);

    return 0;
}
