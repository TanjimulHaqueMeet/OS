//SJF Non-Preemptive
#include <stdio.h>

int main() {
    int n;
    int process[100], arrival[100], burst[100];
    int completion[100], turnaround[100], waiting[100];
    int done[100] = {0};

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Process ID, Arrival Time, Burst Time:\n");
    for (int i = 0; i < n; i++) 
    {
        scanf("%d %d %d", &process[i], &arrival[i], &burst[i]);
    }

    int time = 0;       
    int completed = 0;  
    double avg_turn = 0; 
    double avg_wait = 0; 

    printf("\nProcess ID\tTurnaround Time\tWaiting Time\n");

    while (completed < n) {
        int idx = -1;
        int min_burst = 100;

        for (int i = 0; i < n; i++) 
        {
            if (!done[i] && arrival[i] <= time) 
            {
                if (burst[i] < min_burst) 
                {
                    min_burst = burst[i];
                    idx = i;
                } 
                
                else if (burst[i] == min_burst) 
                {
                    if (arrival[i] < arrival[idx]) 
                    {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) 
        {
            time++; 
        } 
        
        else 
        {
            time = time + burst[idx];
            completion[idx] = time;
            turnaround[idx] = completion[idx] - arrival[idx];
            waiting[idx] = turnaround[idx] - burst[idx];

            avg_turn = avg_turn + turnaround[idx];
            avg_wait = avg_wait + waiting[idx];

            done[idx] = 1;
            completed++;

            printf("\t%d\t\t\t%d\t\t\t\t%d\n", process[idx], turnaround[idx], waiting[idx]);
        }
    }

    printf("\nAverage Turnaround Time: %.2lf\n", avg_turn / n);
    printf("Average Waiting Time: %.2lf\n", avg_wait / n);

    return 0;
}
