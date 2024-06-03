#include <stdio.h>

typedef struct {
    int id;
    int at;
    int bt;
    int priority;
    int rt;
} Proc;

void swap(Proc *a, Proc *b) {
    Proc temp = *a;
    *a = *b;
    *b = temp;
}

void sort_by_priority(Proc p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].priority > p[j + 1].priority) {
                swap(&p[j], &p[j + 1]);
            }
        }
    }
}

void priority_preemptive(Proc p[], int n) {
    int wt[n], tat[n];
    int total_time = 0;
    int completed = 0;

    while (completed < n) {
        int highest_priority_index = -1;
        int highest_priority = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= total_time && p[i].priority > highest_priority && p[i].rt > 0) {
                highest_priority_index = i;
                highest_priority = p[i].priority;
            }
        }
        if (highest_priority_index == -1) {
            total_time++;
            continue;
        }

        p[highest_priority_index].rt--;
        if (p[highest_priority_index].rt == 0) {
            completed++;
            wt[highest_priority_index] = total_time + 1 - p[highest_priority_index].at - p[highest_priority_index].bt;
            if (wt[highest_priority_index] < 0) {
                wt[highest_priority_index] = 0;
            }
            tat[highest_priority_index] = wt[highest_priority_index] + p[highest_priority_index].bt;
        }
        total_time++;
    }

    float avg_wt = 0, avg_tat = 0;
    for (int i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];
    }
    avg_wt /= n;
    avg_tat /= n;

    printf("\nPreemptive Priority Scheduling:\n");
    printf("ID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].priority, wt[i], tat[i]);
    }
    printf("Avg Waiting Time: %.2f\n", avg_wt);
    printf("Avg Turnaround Time: %.2f\n", avg_tat);
}

void priority_non_preemptive(Proc p[], int n) {
    int wt[n], tat[n];
    sort_by_priority(p, n);

    int total_time = p[0].at;
    for (int i = 0; i < n; i++) {
        wt[i] = total_time - p[i].at;
        if (wt[i] < 0) {
            wt[i] = 0;
            total_time = p[i].at;
        }
        tat[i] = wt[i] + p[i].bt;
        total_time += p[i].bt;
    }

    float avg_wt = 0, avg_tat = 0;
    for (int i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];
    }
    avg_wt /= n;
    avg_tat /= n;

    printf("\nNon-preemptive Priority Scheduling:\n");
    printf("ID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].priority, wt[i], tat[i]);
    }
    printf("Avg Waiting Time: %.2f\n", avg_wt);
    printf("Avg Turnaround Time: %.2f\n", avg_tat);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Proc p[n];
    printf("Enter arrival time, burst time, and priority for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        p[i].id = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Priority: ");
        scanf("%d", &p[i].priority);
        p[i].rt = p[i].bt;
    }

    priority_non_preemptive(p, n);
    priority_preemptive(p, n);

    return 0;
}
