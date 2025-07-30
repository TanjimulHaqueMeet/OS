//FCFS
#include <stdio.h>

int main() {
    int n;
    int process[100], arrival[100], burst[100];
    int completion[100], turnaround[100], waiting[100];

    printf("Enter number of processes: ");
    scanf("%d", &n);
   
    printf("Enter Process ID, Arrival Time, Burst Time:\n");
    for (int i = 0; i < n; i++) {
    scanf("%d %d %d", &process[i], &arrival[i], &burst[i]);

    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arrival[j] > arrival[j + 1]) {
                int temp;

                temp = arrival[j];
                arrival[j] = arrival[j + 1];
                arrival[j + 1] = temp;

                temp = burst[j];
                burst[j] = burst[j + 1];
                burst[j + 1] = temp;

                temp = process[j];
                process[j] = process[j + 1];
                process[j + 1] = temp;
            }
        }
    }

    completion[0] = arrival[0] + burst[0];
    for (int i = 1; i < n; i++) {
        if (completion[i - 1] < arrival[i]) {
            completion[i] = arrival[i] + burst[i];
        } else {
            completion[i] = completion[i - 1] + burst[i];
        }
    }

    double avg_turn = 0, avg_wait = 0;

    printf("\nProcess\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        turnaround[i] = completion[i] - arrival[i];
        waiting[i] = turnaround[i] - burst[i];

        avg_turn = avg_turn + turnaround[i];
        avg_wait = avg_wait + waiting[i];

        printf("\t%d\t\t%d\t\t\t%d\n", process[i], turnaround[i], waiting[i]);
    }

    printf("\nAverage Turnaround Time: %.2lf\n", avg_turn / n);
    printf("Average Waiting Time: %.2lf\n", avg_wait / n);

    return 0;
}
