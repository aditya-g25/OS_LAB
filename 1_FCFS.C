#include <stdio.h>

int main()
{
    int n,i,j;
    int at[10], bt[10], wt[10], tat[10], ct[10], rt[10], p[10];
    float avg_wt=0, avg_tat=0, avg_ct=0, avg_rt=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        p[i] = i+1;
        printf("Enter AT and BT for P%d: ",i+1);
        scanf("%d%d",&at[i],&bt[i]);
    }

    // Sort by Arrival Time
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(at[i] > at[j])
            {
                int temp;

                temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    if(at[0]==0)
        ct[0]=bt[0];
    else
        ct[0]=at[0]+bt[0];

    tat[0]=ct[0]-at[0];
    wt[0]=tat[0]-bt[0];
    rt[0]=wt[0];

    for(i=1;i<n;i++)
    {
        if(ct[i-1] < at[i])
            ct[i]=at[i]+bt[i];
        else
            ct[i]=ct[i-1]+bt[i];

        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
        rt[i]=wt[i];
    }

    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\tRT\n");

    for(i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i],at[i],bt[i],ct[i],wt[i],tat[i],rt[i]);

        avg_wt += wt[i];
        avg_tat += tat[i];
        avg_ct += ct[i];
        avg_rt += rt[i];
    }

    avg_wt /= n;
    avg_tat /= n;
    avg_ct /= n;
    avg_rt /= n;

    printf("\nAverage WT = %.2f",avg_wt);
    printf("\nAverage TAT = %.2f",avg_tat);
    printf("\nAverage CT = %.2f",avg_ct);
    printf("\nAverage RT = %.2f",avg_rt);

    return 0;
}