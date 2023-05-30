#include <stdio.h>

int main()
{
    int p[10], at[10], bt[10], ct[10], tat[10], wt[10], rem_bt[10], i, j, smallest, n, time = 0, completed = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the arrival time and burst time for each process:\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d: ", i + 1);
        scanf("%d%d", &at[i], &bt[i]);
        rem_bt[i] = bt[i];
        p[i] = i + 1;
    }

    while (completed != n)
    {
        smallest = -1;

        for (i = 0; i < n; i++)
        {
            if (at[i] <= time && rem_bt[i] > 0)
            {
                if (smallest == -1 || rem_bt[i] < rem_bt[smallest])
                {
                    smallest = i;
                }
            }
        }

        if (smallest == -1)
        {
            time++;
            continue;
        }

        rem_bt[smallest]--;

        if (rem_bt[smallest] == 0)
        {
            completed++;
            ct[smallest] = time + 1;
            tat[smallest] = ct[smallest] - at[smallest];
            wt[smallest] = tat[smallest] - bt[smallest];
        }

        time++;
    }

    float awt = 0, atat = 0;

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
        awt += wt[i];
        atat += tat[i];
    }

    awt /= n;
    atat /= n;

    printf("\nAverage turnaround time: %.2f", atat);
    printf("\nAverage waiting time: %.2f\n", awt);

    return 0;
}
