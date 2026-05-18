#include<stdio.h>

int main()
{
    int n, r, i, j, k;

    int allocation[10][10];
    int max[10][10];
    int available[10];
    int request[10];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter number of resources: ");
    scanf("%d", &r);

    // Allocation Matrix
    printf("\nEnter allocation matrix:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < r; j++)
            scanf("%d", &allocation[i][j]);
    }

    // Maximum Matrix
    printf("\nEnter max matrix:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < r; j++)
            scanf("%d", &max[i][j]);
    }

    // Available Vector
    printf("\nEnter availability vector:\n");
    for(j = 0; j < r; j++)
        scanf("%d", &available[j]);

    // Need Matrix
    int need[10][10];

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < r; j++)
            need[i][j] = max[i][j] - allocation[i][j];
    }

    // Request Section
    int pno;

    printf("\nEnter process number making request: ");
    scanf("%d", &pno);

    printf("Enter request vector:\n");
    for(i = 0; i < r; i++)
        scanf("%d", &request[i]);

    // Step 1: Check Request <= Need
    for(i = 0; i < r; i++)
    {
        if(request[i] > need[pno][i])
        {
            printf("\nError! Process exceeded maximum claim.\n");
            return 0;
        }
    }

    // Step 2: Check Request <= Available
    for(i = 0; i < r; i++)
    {
        if(request[i] > available[i])
        {
            printf("\nResources not available. Process must wait.\n");
            return 0;
        }
    }

    // Step 3: Temporary Allocation
    for(i = 0; i < r; i++)
    {
        available[i] -= request[i];
        allocation[pno][i] += request[i];
        need[pno][i] -= request[i];
    }

    // Safety Algorithm
    int f[n], ans[n], ind = 0;

    for(k = 0; k < n; k++)
        f[k] = 0;

    int y = 0;

    for(k = 0; k < n; k++)
    {
        for(i = 0; i < n; i++)
        {
            if(f[i] == 0)
            {
                int flag = 0;

                for(j = 0; j < r; j++)
                {
                    if(need[i][j] > available[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                if(flag == 0)
                {
                    ans[ind++] = i;

                    for(y = 0; y < r; y++)
                    {
                        available[y] += allocation[i][y];
                    }

                    f[i] = 1;
                }
            }
        }
    }

    // Check Safe State
    if(ind == n)
    {
        printf("\nRequest can be granted.\n");
        printf("System is in safe state.\n");

        printf("Safe Sequence:\n");

        for(i = 0; i < n - 1; i++)
            printf("P%d -> ", ans[i]);

        printf("P%d\n", ans[n - 1]);
    }
    else
    {
        printf("\nRequest cannot be granted.\n");
        printf("System is in unsafe state.\n");
    }

    return 0;
}