#include <stdio.h>

int n, m; // Number of processes and resources

// Function to display the matrix
void display(int mat[][m], int rows, int cols) 
{
    for (int i = 0; i < rows; i++) 
    {
        printf("\n");
        for (int j = 0; j < cols; j++) 
        {
            printf("%d ", mat[i][j]);
        }
    }
}

int main() 
{
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], need[n][m];
    int available[m];

    // Input Allocation Matrix
    printf("\nEnter Allocation Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            printf("alloc[%d][%d]: ", i + 1, j + 1);
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input Max Matrix
    printf("\nEnter Max Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            printf("max[%d][%d]: ", i + 1, j + 1);
            scanf("%d", &max[i][j]);
        }
    }

    // Input Available Resources
    printf("\nEnter Available Resources Array (size %d):\n", m);
    for (int i = 0; i < m; i++) 
    {
        printf("available[%d]: ", i + 1);
        scanf("%d", &available[i]);
    }

    // Display Matrices
    printf("\nDisplaying Allocation Matrix:");
    display(alloc, n, m);
    printf("\n\nDisplaying Max Matrix:");
    display(max, n, m);
    printf("\n\nDisplaying Available Array:\n");
    for (int i = 0; i < m; i++) 
    {
        printf("%d ", available[i]);
    }

    // Step 1: Calculate Need Matrix
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    printf("\n\nDisplaying Need Matrix:");
    display(need, n, m);

    // Step 2: Initialize Flag Array
    int flag[n];
    for (int i = 0; i < n; i++) 
    {
        flag[i] = 0;
    }

    // Step 3: Finding Safe Sequence
    int safe_seq[n], ct = 0;
    int i, j, k, f;
    for (k = 0; k < n; k++) 
    {
        for (i = 0; i < n; i++) 
        {
            f = 1;
            if (flag[i] == 1) 
            {
                continue;
            }
            for (j = 0; j < m; j++) 
            {
                if (available[j] < need[i][j]) 
                {
                    f = 0;
                    break;
                }
            }
            if (f == 1) 
            {
                flag[i] = 1;
                break;
            }
        }
        if (i == n) 
        {
            continue;
        }
        if (flag[i] == 1) 
        {
            safe_seq[ct] = i;
            ct++;
            for (j = 0; j < m; j++) 
            {
                available[j] += alloc[i][j];
            }
        }
    }

    // Checking if a Safe Sequence is Present
    f = 0;
    for (i = 0; i < n; i++) 
    {
        if (flag[i] == 0) 
        {
            printf("\n\nSafe Sequence Not Present!");
            f = 1;
            break;
        }
    }

    // Printing Safe Sequence if Present
    if (f == 0) 
    {
        printf("\n\nSafe Sequence: ");
        for (i = 0; i < n; i++) 
        {
            printf("P%d ", safe_seq[i] + 1);
            if (i < n - 1) 
                printf("-> ");
        }
    }
    return 0;
}
