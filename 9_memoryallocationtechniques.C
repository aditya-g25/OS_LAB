#include <stdio.h>

void firstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];

    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                allocation[i] = j;

                // Block used only once
                blockSize[j] = 0;

                break;
            }
        }
    }

    printf("\nFIRST FIT Allocation:\n");
    printf("Process No.\tProcess Size\tBlock no.\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);

        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void bestFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];

    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++)
    {
        int bestIdx = -1;

        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }

        if (bestIdx != -1)
        {
            allocation[i] = bestIdx;

            // Block used only once
            blockSize[bestIdx] = 0;
        }
    }

    printf("\nBEST FIT Allocation:\n");
    printf("Process No.\tProcess Size\tBlock no.\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);

        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void worstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];

    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++)
    {
        int worstIdx = -1;

        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
            }
        }

        if (worstIdx != -1)
        {
            allocation[i] = worstIdx;

            // Block used only once
            blockSize[worstIdx] = 0;
        }
    }

    printf("\nWORST FIT Allocation:\n");
    printf("Process No.\tProcess Size\tBlock no.\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);

        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main()
{
    int m, n;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    int blockSize[m], block1[m], block2[m];

    printf("Enter sizes of memory blocks:\n");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &blockSize[i]);

        // Copy arrays for other algorithms
        block1[i] = blockSize[i];
        block2[i] = blockSize[i];
    }

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int processSize[n];

    printf("Enter sizes of processes:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &processSize[i]);

    firstFit(blockSize, m, processSize, n);
    bestFit(block1, m, processSize, n);
    worstFit(block2, m, processSize, n);

    return 0;
}