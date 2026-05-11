#include <stdio.h>

int main()
{
    int n, m, i, j, k;

    printf("Enter number of processes : ");
    scanf("%d", &n);

    printf("Enter number of resources : ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], need[n][m];
    int avail[m], finish[n], safeSeq[n];

    for(i = 0; i < n; i++)
    {
        printf("\nEnter details for P%d\n", i);

        printf("Enter Allocation : ");
        for(j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

        printf("Enter Max : ");
        for(j = 0; j < m; j++)
            scanf("%d", &max[i][j]);
    }


    printf("\nEnter Available Resources : ");
    for(i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }


    for(i = 0; i < n; i++)
        finish[i] = 0;

    int count = 0;

    while(count < n)
    {
        int found = 0;

        for(i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                int flag = 1;

                for(j = 0; j < m; j++)
                {
                    if(need[i][j] > avail[j])
                    {
                        flag = 0;
                        break;
                    }
                }

                if(flag)
                {
                    for(k = 0; k < m; k++)
                        avail[k] += alloc[i][k];

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;

                    printf("P%d is visited\n", i);
                }
            }
        }

        if(found == 0)
        {
            printf("\nSystem is NOT in Safe State\n");
            return 0;
        }
    }

    printf("\nSYSTEM IS IN SAFE STATE\n");
    printf("The Safe Sequence is : ");

    for(i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);

    printf("\n\nProcess\tAllocation\tMax\tNeed\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t", i);

        for(j = 0; j < m; j++)
            printf("%d ", alloc[i][j]);

        printf("\t");

        for(j = 0; j < m; j++)
            printf("%d ", max[i][j]);

        printf("\t");

        for(j = 0; j < m; j++)
            printf("%d ", need[i][j]);

        printf("\n");
    }

    return 0;
}
