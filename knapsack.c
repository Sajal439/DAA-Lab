#include <stdio.h>

void knapsack(int n, float weight[], float profit[], float capacity)
{
    float x[20], totalProfit = 0;
    int i, j, u;
    u = capacity;

    for (i = 0; i < n; i++)
        x[i] = 0.0;

    for (i = 0; i < n; i++)
    {
        if (weight[i] > u)
            break;
        else
        {
            x[i] = 1.0;
            totalProfit += profit[i];
            u -= weight[i];
        }
    }

    if (i < n)
        x[i] = u / weight[i];

    totalProfit += (x[i] * profit[i]);

    printf("\nTotal profit: %f\n", totalProfit);
}

int main()
{
    float weight[20], profit[20], capacity;
    int n, i;

    printf("Enter the number of items: ");
    scanf("%d", &n);

    printf("Enter the weights of the items: ");
    for (i = 0; i < n; i++)
        scanf("%f", &weight[i]);

    printf("Enter the profits of the items: ");
    for (i = 0; i < n; i++)
        scanf("%f", &profit[i]);

    printf("Enter the capacity of knapsack: ");
    scanf("%f", &capacity);

    knapsack(n, weight, profit, capacity);

    return 0;
}