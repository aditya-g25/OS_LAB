#include <stdio.h>

struct Process {
    int pid, at, bt, ct, tat, wt, rt, queue;
};

int main() {
    int n;
    struct Process p[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nEnter AT and BT for P%d: ", p[i].pid);
        scanf("%d%d", &p[i].at, &p[i].bt);
        printf("Enter queue (0 = System, 1 = User): ");
        scanf("%d", &p[i].queue);
        p[i].rt = -1;
    }

    struct Process systemP[20], userP[20];
    int sysCount = 0, userCount = 0;

    for (int i = 0; i < n; i++) {
        if (p[i].queue == 0)
            systemP[sysCount++] = p[i];
        else
            userP[userCount++] = p[i];
    }

    printf("\n--- System Ready Queue ---\n");
    printf("PID\tAT\tBT\n");
    for (int i = 0; i < sysCount; i++)
        printf("P%d\t%d\t%d\n", systemP[i].pid, systemP[i].at, systemP[i].bt);

    printf("\n--- User Ready Queue ---\n");
    printf("PID\tAT\tBT\n");
    for (int i = 0; i < userCount; i++)
        printf("P%d\t%d\t%d\n", userP[i].pid, userP[i].at, userP[i].bt);

    for (int i = 0; i < sysCount - 1; i++) {
        for (int j = i + 1; j < sysCount; j++) {
            if (systemP[i].at > systemP[j].at) {
                struct Process temp = systemP[i];
                systemP[i] = systemP[j];
                systemP[j] = temp;
            }
        }
    }

    int time = 0, g = 0;
    int ganttPID[100], ganttTime[100];
    ganttTime[g] = 0;

    float totalWT = 0, totalTAT = 0, totalCT = 0, totalRT = 0;
    int totalCount = 0;

    for (int i = 0; i < sysCount; i++) {
        if (time < systemP[i].at)
            time = systemP[i].at;

        ganttPID[g++] = systemP[i].pid;

        systemP[i].rt = time - systemP[i].at;

        time += systemP[i].bt;
        systemP[i].ct = time;
        systemP[i].tat = systemP[i].ct - systemP[i].at;
        systemP[i].wt = systemP[i].tat - systemP[i].bt;

        ganttTime[g] = time;

        totalWT += systemP[i].wt;
        totalTAT += systemP[i].tat;
        totalCT += systemP[i].ct;
        totalRT += systemP[i].rt;
        totalCount++;
    }

    int remaining[20], completed = 0;
    int lastPID = -1;

    for (int i = 0; i < userCount; i++)
        remaining[i] = userP[i].bt;

    while (completed < userCount) {
        int idx = -1;
        int minRT = 9999;

        for (int i = 0; i < userCount; i++) {
            if (userP[i].at <= time && remaining[i] > 0) {
                if (remaining[i] < minRT) {
                    minRT = remaining[i];
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        if (lastPID != userP[idx].pid) {
            ganttPID[g++] = userP[idx].pid;
            ganttTime[g] = time;
            lastPID = userP[idx].pid;
        }

        if (userP[idx].rt == -1)
            userP[idx].rt = time - userP[idx].at;

        remaining[idx]--;
        time++;

        if (remaining[idx] == 0) {
            completed++;
            userP[idx].ct = time;
            userP[idx].tat = userP[idx].ct - userP[idx].at;
            userP[idx].wt = userP[idx].tat - userP[idx].bt;

            totalWT += userP[idx].wt;
            totalTAT += userP[idx].tat;
            totalCT += userP[idx].ct;
            totalRT += userP[idx].rt;
            totalCount++;
        }
    }

    ganttTime[g] = time;

    printf("\nPID\tType\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for (int i = 0; i < sysCount; i++)
        printf("P%d\tSystem\t%d\t%d\t%d\t%d\t%d\t%d\n",
               systemP[i].pid, systemP[i].at, systemP[i].bt,
               systemP[i].ct, systemP[i].tat, systemP[i].wt, systemP[i].rt);

    for (int i = 0; i < userCount; i++)
        printf("P%d\tUser\t%d\t%d\t%d\t%d\t%d\t%d\n",
               userP[i].pid, userP[i].at, userP[i].bt,
               userP[i].ct, userP[i].tat, userP[i].wt, userP[i].rt);

    printf("\nAverage WT  = %.2f", totalWT / totalCount);
    printf("\nAverage TAT = %.2f", totalTAT / totalCount);
    printf("\nAverage CT  = %.2f", totalCT / totalCount);
    printf("\nAverage RT  = %.2f\n", totalRT / totalCount);

    printf("\nGantt Chart:\n");
    for (int i = 0; i < g; i++) printf("--------");
    printf("-\n|");

    for (int i = 0; i < g; i++) printf(" P%d\t|", ganttPID[i]);

    printf("\n");
    for (int i = 0; i < g; i++) printf("--------");
    printf("-\n");

    for (int i = 0; i <= g; i++) printf("%d\t", ganttTime[i]);
    printf("\n");

    return 0;
}
