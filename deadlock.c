#include <stdio.h>

int main()
{
    int n, m, i, j, k;

    printf("Enter number of processes : ");
    scanf("%d", &n);

    printf("Enter number of resources : ");
    scanf("%d", &m);

    int alloc[n][m], request[n][m];
    int avail[m];

    int finish[n], safeSeq[n];

    // Input Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++)
    {
        printf("For P%d : ", i);
        for(j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input Request Matrix
    printf("\nEnter Request Matrix:\n");
    for(i = 0; i < n; i++)
    {
        printf("For P%d : ", i);
        for(j = 0; j < m; j++)
        {
            scanf("%d", &request[i][j]);
        }
    }

    // Input Available Resources
    printf("\nEnter Available Resources : ");
    for(i = 0; i < m; i++)
    {
        scanf("%d", &avail[i]);
    }

    // Initialize finish array
    for(i = 0; i < n; i++)
    {
        int flag = 0;

        for(j = 0; j < m; j++)
        {
            if(alloc[i][j] != 0)
            {
                flag = 1;
                break;
            }
        }

        if(flag == 0)
            finish[i] = 1;
        else
            finish[i] = 0;
    }

    int count = 0;

    while(count < n)
    {
        int found = 0;

        for(i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                int possible = 1;

                for(j = 0; j < m; j++)
                {
                    if(request[i][j] > avail[j])
                    {
                        possible = 0;
                        break;
                    }
                }

                if(possible)
                {
                    for(k = 0; k < m; k++)
                    {
                        avail[k] += alloc[i][k];
                    }

                    finish[i] = 1;
                    safeSeq[count++] = i;
                    found = 1;

                    printf("P%d is executed\n", i);
                }
            }
        }

        if(found == 0)
            break;
    }

    // Check Deadlock
    int deadlock = 0;

    for(i = 0; i < n; i++)
    {
        if(finish[i] == 0)
        {
            deadlock = 1;
            printf("\nProcess P%d is in Deadlock", i);
        }
    }

    if(deadlock == 0)
    {
        printf("\n\nNo Deadlock Detected");
        printf("\nSafe Sequence is : ");

        for(i = 0; i < count; i++)
        {
            printf("P%d ", safeSeq[i]);
        }
    }

    return 0;
}
