#include <stdio.h>

int main()
{
    int n, r, i, j, k;

    int allocation[10][10];
    int request[10][10];
    int available[10];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &r);

    // Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < r; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Request Matrix
    printf("\nEnter Request Matrix:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < r; j++)
        {
            scanf("%d", &request[i][j]);
        }
    }

    // Available Vector
    printf("\nEnter Available Vector:\n");
    for(i = 0; i < r; i++)
    {
        scanf("%d", &available[i]);
    }

    int finish[10], ans[10], ind = 0;

    // Initialize finish array
    for(i = 0; i < n; i++)
    {
        finish[i] = 0;
    }

    // Detection Algorithm
    for(k = 0; k < n; k++)
    {
        for(i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                int flag = 0;

                for(j = 0; j < r; j++)
                {
                    if(request[i][j] > available[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                if(flag == 0)
                {
                    ans[ind++] = i;

                    for(j = 0; j < r; j++)
                    {
                        available[j] += allocation[i][j];
                    }

                    finish[i] = 1;
                }
            }
        }
    }

    // Check Deadlock
    int deadlock = 0;

    for(i = 0; i < n; i++)
    {
        if(finish[i] == 0)
        {
            deadlock = 1;
            printf("\nProcess P%d is deadlocked.", i);
        }
    }

    if(deadlock == 0)
    {
        printf("\n\nNo Deadlock Detected.\n");

        printf("Safe Sequence:\n");

        for(i = 0; i < n - 1; i++)
        {
            printf("P%d -> ", ans[i]);
        }

        printf("P%d\n", ans[n - 1]);
    }

    return 0;
}