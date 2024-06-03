#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int pid[n], arrival[n], burst[n], remaining[n], completion[n], waiting[n], turnaround[n];
    float avg_waiting_time = 0, avg_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &arrival[i], &burst[i]);
        remaining[i] = burst[i];
    }

    int completed = 0, current_time = 0, shortest = 0;
    int min_remaining_time = INT_MAX;
    int finish_time;
    int check = 0;

    while (completed != n) {
        for (int j = 0; j < n; j++) {
            if ((arrival[j] <= current_time) &&
                (remaining[j] < min_remaining_time) && remaining[j] > 0) {
                min_remaining_time = remaining[j];
                shortest = j;
                check = 1;
            }
        }

        if (check == 0) {
            current_time++;
            continue;
        }

        remaining[shortest]--;
        min_remaining_time = remaining[shortest];

        if (min_remaining_time == 0) {
            min_remaining_time = INT_MAX;
        }

        if (remaining[shortest] == 0) {
            completed++;
            check = 0;
            finish_time = current_time + 1;
            completion[shortest] = finish_time;
            turnaround[shortest] = finish_time - arrival[shortest];
            waiting[shortest] = turnaround[shortest] - burst[shortest];

            avg_waiting_time += waiting[shortest];
            avg_turnaround_time += turnaround[shortest];
        }
        current_time++;
    }

    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    printf("\nPID\t\tAT\t\tBT\t\tCT\t\tTAT\t\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], arrival[i], burst[i], completion[i], turnaround[i], waiting[i]);
    }

    printf("\nAverage Waiting Time: %.2f", avg_waiting_time);
    printf("\nAverage Turnaround Time: %.2f", avg_turnaround_time);

    return 0;
}
