#include <stdio.h>
int main() 
{
    // Initialize the variables
    int i, NOP, sum = 0, y, quant, wt = 0, tat = 0;
    int at[10], bt[10], temp[10];
    float avg_wt, avg_tat;
    printf("Total number of processes in the system: ");
    scanf("%d", &NOP);
    y = NOP; // Assign the number of processes to variable y
    // Use for loop to enter the details of the process like Arrival time and Burst Time
    for (i = 0; i < NOP; i++) {
        printf("\nEnter the Arrival and Burst time of the Process[%d]\n", i + 1);
        printf("Arrival time: ");
        scanf("%d", &at[i]); // Accept arrival time
        printf("Burst time: ");
        scanf("%d", &bt[i]); // Accept the Burst time
        temp[i] = bt[i]; // Store the burst time in temp array
    }
    // Accept the Time Quantum
    printf("Enter the Time Quantum for the process: ");
    scanf("%d", &quant);
    // Display the process No, Burst Time, Turn Around Time and Waiting Time
    printf("\nProcess No\tBurst Time\tTAT\tWaiting Time");
    for (sum = 0, i = 0; y != 0; ) {
        // Check if the process has arrived before processing
        if (temp[i] > 0 && at[i] <= sum) {
            if (temp[i] <= quant) { // Define the conditions
                sum += temp[i];
                temp[i] = 0;
                y--; // Decrement the process count
                printf("\nProcess No[%d]\t\t%d\t\t%d\t\t%d", 
                       i + 1, bt[i], sum - at[i], sum - at[i] - bt[i]);
                wt += sum - at[i] - bt[i];
                tat += sum - at[i];
            } else {
                temp[i] -= quant;
                sum += quant;
            }
        }
        // Move to the next process
        i = (i + 1) % NOP; // Wrap around to the first process
    }
    // Represents the average waiting time and Turn Around time
    avg_wt = (float)wt / NOP;
    avg_tat = (float)tat / NOP;
    printf("\nAverage Turn Around Time: %f", avg_tat);
    printf("\nAverage Waiting Time: %f\n", avg_wt);
    return 0;
}
