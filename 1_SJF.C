#include <stdio.h>

struct Process
{
    int pid, at, bt, wt, tat, ct, rt, remaining;
};

void sjf_non_preemptive(struct Process p[], int n)
{
    int completed = 0, time = 0, min, idx;
    float avg_wt = 0, avg_tat = 0, avg_rt = 0;

    int visited[20] = {0};

    while (completed < n)
    {
        min = 9999;
        idx = -1;

        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= time && !visited[i] && p[i].bt < min)
            {
                min = p[i].bt;
                idx = i;
            }
        }

        if (idx != -1)
        {
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].rt = p[idx].wt;

            visited[idx] = 1;
            completed++;

            avg_wt += p[idx].wt;
            avg_tat += p[idx].tat;
            avg_rt += p[idx].rt;
        }
        else
        {
            time++;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("\nAverage WT = %.2f", avg_wt / n);
    printf("\nAverage TAT = %.2f", avg_tat / n);
    printf("\nAverage RT = %.2f\n", avg_rt / n);
}

void sjf_preemptive(struct Process p[], int n)
{
    int completed = 0, time = 0, min, idx;
    float avg_wt = 0, avg_tat = 0, avg_rt = 0;
    int first_response[20] = {0};

    while (completed < n)
    {
        min = 9999;
        idx = -1;

        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= time && p[i].remaining > 0 && p[i].remaining < min)
            {
                min = p[i].remaining;
                idx = i;
            }
        }

        if (idx != -1)
        {
            if (first_response[idx] == 0)
            {
                p[idx].rt = time - p[idx].at;
                first_response[idx] = 1;
            }

            p[idx].remaining--;
            time++;

            if (p[idx].remaining == 0)
            {
                completed++;
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;

                avg_wt += p[idx].wt;
                avg_tat += p[idx].tat;
                avg_rt += p[idx].rt;
            }
        }
        else
        {
            time++;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("\nAverage WT = %.2f", avg_wt / n);
    printf("\nAverage TAT = %.2f", avg_tat / n);
    printf("\nAverage RT = %.2f\n", avg_rt / n);
}

int main()
{
    int n, choice;

    struct Process p[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("Enter AT and BT for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].remaining = p[i].bt;
    }

    printf("\n1. SJF Non Preemptive\n2. SJF Preemptive (SRTF)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            sjf_non_preemptive(p, n);
            break;

        case 2:
            sjf_preemptive(p, n);
            break;

        default:
            printf("Invalid choice");
    }

    return 0;
}