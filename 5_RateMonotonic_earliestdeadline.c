#include <stdio.h>
#include <math.h>
#define MAX 10

typedef struct {
    int id, bt, period, deadline;
    int ct, wt, tat;
} Process;

void printGantt(int gantt[], int n) {
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < n; i++) {
        printf(" P%d |", gantt[i]);
    }
    printf("\n0");
    for (int i = 1; i <= n; i++)
        printf("    %d", i);
    printf("\n");
}

void edf(Process p[], int n) {
    int time = 0, completed = 0;
    int gantt[100], g = 0;
    int done[MAX] = {0};
    printf("\n===== Earliest Deadline First (EDF) Scheduling =====\n");
    float util = 0;
    for (int i = 0; i < n; i++)
        util += (float)p[i].bt / p[i].deadline;
    if (util <= 1)
        printf("Schedulable (U = %.2f <= 1)\n", util);
    else
        printf("Not Schedulable (U = %.2f > 1)\n", util);
    printf("ID\tBT\tDeadline\tCT\tWT\tTAT\n");

    while (completed < n) {
        int idx = -1, min_dead = 9999;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].deadline < min_dead) {
                min_dead = p[i].deadline;
                idx = i;
            }
        }

        gantt[g++] = p[idx].id;
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct;
        p[idx].wt = p[idx].tat - p[idx].bt;
        done[idx] = 1;
        completed++;
    }

    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t\t%d\t%d\t%d\n",
               p[i].id, p[i].bt, p[i].deadline,
               p[i].ct, p[i].wt, p[i].tat);
    printGantt(gantt, g);
}

void rms(Process p[], int n) {
    int time = 0, completed = 0;
    int gantt[100], g = 0;
    int done[MAX] = {0};
    printf("\n===== Rate Monotonic Scheduling (RMS) =====\n");

    float util = 0;
    for (int i = 0; i < n; i++)
        util += (float)p[i].bt / p[i].period;
    float bound = n * (pow(2, (float)1/n) - 1);
    if (util <= bound)
        printf("Schedulable (U = %.2f <= %.2f)\n", util, bound);
    else
        printf("Not Schedulable (U = %.2f > %.2f)\n", util, bound);
    printf("ID\tBT\tPeriod\tCT\tWT\tTAT\n");

    while (completed < n) {
        int idx = -1, min_period = 9999;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].period < min_period) {
                min_period = p[i].period;
                idx = i;
            }
        }
        gantt[g++] = p[idx].id;
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct;
        p[idx].wt = p[idx].tat - p[idx].bt;
        done[idx] = 1;
        completed++;
    }
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].bt, p[i].period,
               p[i].ct, p[i].wt, p[i].tat);
    printGantt(gantt, g);
}

int main() {
    int n;
    Process p[MAX], temp[MAX];
    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].id = i;
        printf("\nProcess %d:\n", i);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Deadline (for EDF): ");
        scanf("%d", &p[i].deadline);
        printf("Period (for RMS): ");
        scanf("%d", &p[i].period);
    }

    for (int i = 0; i < n; i++)
        temp[i] = p[i];
    edf(temp, n);
    for (int i = 0; i < n; i++)
        temp[i] = p[i];
    rms(temp, n);

    return 0;
}
