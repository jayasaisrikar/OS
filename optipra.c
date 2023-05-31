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
    
    printf("\nWhat is the total number of frames:\t");
    scanf("%d", &frames);
    
    int temp[frames];
    for (m = 0; m < frames; m++)
    {
        temp[m] = -1;
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
                break;
            }
        }
        
        pageFaults++;
        
        if ((pageFaults <= frames) && (s == 0))
        {
            temp[m] = referenceString[m];
        }
        else if (s == 0)
        {
            int index = -1;
            int furthest = m + 1;
            
            for (n = 0; n < frames; n++)
            {
                int found = 0;
                for (int k = m + 1; k < pages; k++)
                {
                    if (temp[n] == referenceString[k])
                    {
                        found = 1;
                        if (k > furthest)
                        {
                            furthest = k;
                            index = n;
                        }
                        break;
                    }
                }
                
                if (found == 0)
                {
                    index = n;
                    break;
                }
            }
            
            if (index != -1)
            {
                temp[index] = referenceString[m];
            }
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
