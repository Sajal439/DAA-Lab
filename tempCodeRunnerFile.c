#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to perform Insertion Sort
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Function to generate a random array
void generateRandomArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000;
    }
}

int main()
{
    FILE *file = fopen("insertionSortData.txt", "w");
    if (!file)
    {
        printf("Error opening file!\n");
        return 1;
    }

    srand(time(0));

    for (int n = 1000; n <= 10000; n += 1000)
    {
        int *arr = (int *)malloc(n * sizeof(int));
        if (!arr)
        {
            printf("Memory allocation failed!\n");
            return 1;
        }

        generateRandomArray(arr, n);

        clock_t start = clock();
        insertionSort(arr, n);
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
        fprintf(gnuplotPipe, "set title 'Insertion Sort Performance'\n");
        fprintf(gnuplotPipe, "set xlabel 'Number of Elements (n)'\n");
        fprintf(gnuplotPipe, "set ylabel 'Time Taken (seconds)'\n");
        fprintf(gnuplotPipe, "set y2label 'Space Used (bytes)'\n");
        fprintf(gnuplotPipe, "set ytics nomirror\n");
        fprintf(gnuplotPipe, "set y2tics\n");
        fprintf(gnuplotPipe, "set grid\n");
        fprintf(gnuplotPipe, "plot 'insertionSortData.txt' using 1:2 with linespoints title 'Time Complexity', 'insertionSortData.txt' using 1:3 axes x1y2 with linespoints title 'Space Complexity'\n");
        pclose(gnuplotPipe);
    }
    else
    {
        printf("Error opening Gnuplot!\n");
    }

    printf("Graph plotted using Gnuplot.\n");

    return 0;
}