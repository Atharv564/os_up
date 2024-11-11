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
} Process;
void calculateSJFPreemptive(Process processes[], int n)
{
    int time = 0;
    int completed = 0;
    int min_remaining_time;
    int shortest = 0;
    int i;
    int all_completed = 0;
    while (completed < n)
    {
        min_remaining_time = INT_MAX;
        for (i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0)
            {
                if (processes[i].remaining_time < min_remaining_time)
                {
                    min_remaining_time = processes[i].remaining_time;
                    shortest = i;
                }
            }
        }
        if (min_remaining_time == INT_MAX)
        {
            time++;
            continue;
        }
        processes[shortest].remaining_time--;
        time++;
        if (processes[shortest].remaining_time == 0)
        {
            processes[shortest].completion_time = time;
            processes[shortest].turnaround_time = processes[shortest].completion_time - processes[shortest].arrival_time;
            processes[shortest].waiting_time = processes[shortest].turnaround_time - processes[shortest].burst_time;
            completed++;
        }
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
        printf(" %d | %d | %d | %d | %d | %d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, processes[i].completion_time, processes[i].waiting_time, processes[i].turnaround_time);
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
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }
    calculateSJFPreemptive(processes, n);
    printProcessInfo(processes, n);
    return 0;
}