#include <stdio.h>

struct Process {
    int pid, at, bt, pr;
    int ct, tat, wt, rt;
    int remaining;
    int completed;
    int started;
};

int main() {
    int n, choice;
    struct Process p[20];
    int gantt[100], gtime[100];
    int gindex = 0;

    float total_ct=0, total_tat=0, total_wt=0, total_rt=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(int i=0;i<n;i++){
        p[i].pid=i+1;
        printf("Enter AT, BT and Priority for P%d: ",p[i].pid);
        scanf("%d%d%d",&p[i].at,&p[i].bt,&p[i].pr);

        p[i].remaining=p[i].bt;
        p[i].completed=0;
        p[i].started=0;
    }

    printf("\n1. Priority Non-Preemptive");
    printf("\n2. Priority Preemptive");
    printf("\nEnter choice: ");
    scanf("%d",&choice);

    int currentTime=0, completed=0;

    if(choice==1){

        while(completed<n){
            int idx=-1;
            int highestPriority=9999;

            for(int i=0;i<n;i++){
                if(p[i].at<=currentTime && p[i].completed==0){
                    if(p[i].pr < highestPriority){
                        highestPriority = p[i].pr;
                        idx = i;
                    }
                }
            }

            if(idx!=-1){

                gantt[gindex] = p[idx].pid;
                gtime[gindex] = currentTime;
                gindex++;

                p[idx].rt=currentTime - p[idx].at;

                currentTime += p[idx].bt;

                p[idx].ct = currentTime;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;

                total_ct += p[idx].ct;
                total_tat += p[idx].tat;
                total_wt += p[idx].wt;
                total_rt += p[idx].rt;

                p[idx].completed = 1;
                completed++;
            }
            else{
                currentTime++;
            }
        }

        gtime[gindex] = currentTime;
    }

    else if(choice==2){

        int prev = -1;

        while(completed<n){
            int idx=-1;
            int highestPriority=9999;

            for(int i=0;i<n;i++){
                if(p[i].at<=currentTime && p[i].remaining>0){
                    if(p[i].pr < highestPriority){
                        highestPriority = p[i].pr;
                        idx = i;
                    }
                }
            }

            if(idx!=-1){

                if(prev != p[idx].pid){
                    gantt[gindex] = p[idx].pid;
                    gtime[gindex] = currentTime;
                    gindex++;
                    prev = p[idx].pid;
                }

                if(p[idx].started==0){
                    p[idx].rt=currentTime - p[idx].at;
                    total_rt += p[idx].rt;
                    p[idx].started=1;
                }

                p[idx].remaining--;
                currentTime++;

                if(p[idx].remaining==0){
                    p[idx].ct=currentTime;
                    p[idx].tat=p[idx].ct - p[idx].at;
                    p[idx].wt=p[idx].tat - p[idx].bt;

                    total_ct+=p[idx].ct;
                    total_tat+=p[idx].tat;
                    total_wt+=p[idx].wt;
                    completed++;
                }
            }
            else{
                currentTime++;
            }
        }

        gtime[gindex] = currentTime;
    }

    else{
        printf("Invalid Choice!");
        return 0;
    }

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n");
    for(int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid,p[i].at,p[i].bt,p[i].pr,
        p[i].ct,p[i].tat,p[i].wt,p[i].rt);
    }

    printf("\nAverage CT = %.2f",total_ct/n);
    printf("\nAverage TAT = %.2f",total_tat/n);
    printf("\nAverage WT = %.2f",total_wt/n);
    printf("\nAverage RT = %.2f\n",total_rt/n);

    printf("\nGantt Chart:\n|");
    for(int i=0;i<gindex;i++){
        printf(" P%d |",gantt[i]);
    }

    printf("\n%d",gtime[0]);
    for(int i=1;i<=gindex;i++){
        printf("   %d",gtime[i]);
    }
    printf("\n");

    return 0;
}
