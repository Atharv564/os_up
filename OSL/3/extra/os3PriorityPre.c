#include <stdio.h>
#include <limits.h>
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
    int priority;
} Process;
void calculatePriorityPreemptive(Process processes[], int n)
{
    int time = 0;
    int completed = 0;
    int highest_priority = INT_MIN;
    int highest_priority_index = -1;
    int i;
    while (completed < n)
    {
        highest_priority = INT_MIN;
        highest_priority_index = -1;
        for (i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0)
            {
                if (processes[i].priority > highest_priority)
                {
                    highest_priority = processes[i].priority;
                    highest_priority_index = i;
                }
            }
        }
        if (highest_priority_index == -1)
        {
            time++; // No process is ready to execute
            continue;
        }
        processes[highest_priority_index].remaining_time--;
        time++;
        if (processes[highest_priority_index].remaining_time == 0)
        {
            processes[highest_priority_index].completion_time = time;
            processes[highest_priority_index].turnaround_time = processes[highest_priority_index].completion_time - processes[highest_priority_index].arrival_time;
            processes[highest_priority_index].completion_time - processes[highest_priority_index].arrival_time;
            processes[highest_priority_index].waiting_time = processes[highest_priority_index].turnaround_time - processes[highest_priority_index].burst_time;
            completed++;
        }
    }
}
void printProcessInfo(Process processes[], int n)
{
    int i;
    float avg_waiting_time = 0;
    float avg_turnaround_time = 0;
    printf("Process ID | Arrival Time | Burst Time | Priority | Completion Time | Waiting Time | Turnaround Time\n");
    for (i = 0; i < n; i++)
    {
        printf(" %d | %d | %d | %d | %d | %d | %d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, processes[i].priority, processes[i].completion_time, processes[i].waiting_time, processes[i].turnaround_time);
        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time / n);
}
int main()
{
    int n, i;
    Process processes[MAX];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time;
    }
    calculatePriorityPreemptive(processes, n);
    printProcessInfo(processes, n);
    return 0;
}
