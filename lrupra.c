#include <stdio.h>
int main()
{
    int referenceString[10], pageFaults = 0, hits = 0, m, n, s, pages, frames;
    printf("\nEnter the number of Pages:\t");
    scanf("%d", &pages);
    printf("\nEnter reference string values:\n");
    for (m = 0; m < pages; m++)
    {
        printf("Value No. [%d]:\t", m + 1);
        scanf("%d", &referenceString[m]);
    }
    printf("\nWhat are the total number of frames:\t");
    scanf("%d", &frames);
    int temp[frames];
    int time[frames];
    int currentTime = 0;
    for (m = 0; m < frames; m++)
    {
        temp[m] = -1;
        time[m] = 0;
    }
    for (m = 0; m < pages; m++)
    {
        s = 0;
        for (n = 0; n < frames; n++)
        {
            if (referenceString[m] == temp[n])
            {
                s++;
                pageFaults--;
                hits++;
                time[n] = currentTime++;
                break;
            }
        }
        pageFaults++;
        if ((pageFaults <= frames) && (s == 0))
        {
            int minTime = time[0];
            int minIndex = 0;
            for (n = 1; n < frames; n++)
            {
                if (time[n] < minTime)
                {
                    minTime = time[n];
                    minIndex = n;
                }
            }
            temp[minIndex] = referenceString[m];
            time[minIndex] = currentTime++;
        }
        else if (s == 0)
        {
            int minTime = time[0];
            int minIndex = 0;

            for (n = 1; n < frames; n++)
            {
                if (time[n] < minTime)
                {
                    minTime = time[n];
                    minIndex = n;
                }
            }
            temp[minIndex] = referenceString[m];
            time[minIndex] = currentTime++;
        }
        printf("\n");
        for (n = 0; n < frames; n++)
        {
            printf("%d\t", temp[n]);
        }
    }
    float hitRatio = (float)hits / pages;
    float missRatio = (float)(pageFaults - hits) / pages;
    printf("\nTotal Page Faults:\t%d\n", pageFaults);
    printf("Hit Ratio:\t%.2f\n", hitRatio);
    printf("Miss Ratio:\t%.2f\n", missRatio);
    return 0;
}
