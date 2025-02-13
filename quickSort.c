#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to swap elements
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function for Quick Sort
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Quick Sort function
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Generate random array
void generateRandomArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 10000;
    }
}

// Main program to perform sorting and plot graph
int main()
{
    FILE *file = fopen("sorting_times.dat", "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

    srand(time(0));

    for (int n = 1000; n <= 50000; n += 5000)
    {
        int *arr = (int *)malloc(n * sizeof(int));
        if (arr == NULL)
        {
            printf("Memory allocation failed!\n");
            return 1;
        }

        generateRandomArray(arr, n);

        clock_t start = clock();
        quickSort(arr, 0, n - 1);
        clock_t end = clock();

        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        double space_used = n * sizeof(int); // Array size

        fprintf(file, "%d %f %f\n", n, time_taken, space_used);

        free(arr);
    }

    fclose(file);

    // Open Gnuplot and plot
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe)
    {
        fprintf(gnuplotPipe, "set title 'Quick Sort Performance'\n");
        fprintf(gnuplotPipe, "set xlabel 'Number of Elements (n)'\n");
        fprintf(gnuplotPipe, "set ylabel 'Time Taken (seconds)'\n");
        fprintf(gnuplotPipe, "set y2label 'Space Used (bytes)'\n");
        fprintf(gnuplotPipe, "set ytics nomirror\n");
        fprintf(gnuplotPipe, "set y2tics\n");
        fprintf(gnuplotPipe, "set grid\n");
        fprintf(gnuplotPipe, "plot 'sorting_times.dat' using 1:2 with linespoints title 'Time Complexity', 'sorting_times.dat' using 1:3 axes x1y2 with linespoints title 'Space Complexity'\n");
        pclose(gnuplotPipe);
    }
    else
    {
        printf("Error opening Gnuplot!\n");
    }

    printf("Graph plotted using Gnuplot.\n");

    return 0;
}