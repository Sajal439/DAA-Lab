#include <stdio.h>

struct Item
{
    int weight;
    int value;
};

void knapsack(struct Item items[], int n, int max_capacity)
{
    int current_weight = 0;
    float current_value = 0.0;
    float ratio[n];

    for (int i = 0; i < n; i++)
        ratio[i] = (float)items[i].value / items[i].weight;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (ratio[j] < ratio[j + 1])
            {
                float temp_ratio = ratio[j];
                ratio[j] = ratio[j + 1];
                ratio[j + 1] = temp_ratio;

                struct Item temp_item = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp_item;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (current_weight + items[i].weight <= max_capacity)
        {
            current_weight += items[i].weight;
            current_value += items[i].value;
        }
        else
        {
            int remaining_capacity = max_capacity - current_weight;
            current_value += items[i].value * ((float)remaining_capacity / items[i].weight);
            break;
        }
    }

    printf("Maximum value in knapsack = %.2f\n", current_value);
}

int main()
{
    int n;
    printf("Enter the number of items: ");
    scanf("%d", &n);

    struct Item items[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter weight and value of item %d: ", i + 1);
        scanf("%d %d", &items[i].weight, &items[i].value);
    }

    int max_capacity;
    printf("Enter the maximum capacity of the knapsack: ");
    scanf("%d", &max_capacity);

    knapsack(items, n, max_capacity);

    return 0;
}
