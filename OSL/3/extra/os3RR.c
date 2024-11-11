#include <stdio.h>
#define MAX 100
typedef struct
{
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
} Process;
void calculateRoundRobin(Process processes[], int n, int quantum)
{
    int time = 0;
    int completed = 0;
    int i;
    int all_completed = 0;
    while (completed < n)
    {
        all_completed = 1;
        for (i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0)
            {
                all_completed = 0;
                if (processes[i].remaining_time > quantum)
                {
                    time += quantum;
                    processes[i].remaining_time -= quantum;
                }
                else
                {
                    time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    processes[i].completion_time = time;
                    processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    completed++;
                }
            }
        }
        if (all_completed)
            break;
    }
}
void printProcessInfo(Process processes[], int n)
{
    int i;
    float avg_waiting_time = 0;
    float avg_turnaround_time = 0;
    printf("Process ID | Arrival Time | Burst Time | Completion Time | Waiting Time | Turnaround Time\n");
    for (i = 0; i < n; i++)
    {
        printf(" %d | %d | %d | %d | %d | %d\n",
               processes[i].id, processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].waiting_time, processes[i].turnaround_time);
        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time / n);
}
int main()
{
    int n, i, quantum;
    Process processes[MAX];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &quantum);
    for (i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }
    calculateRoundRobin(processes, n, quantum);
    printProcessInfo(processes, n);
    return 0;
}