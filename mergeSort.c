#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void generateRandomArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000;
    }
}

int main()
{
    FILE *file = fopen("mergeSortData.txt", "w");
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
        mergeSort(arr, 0, n - 1);
        clock_t end = clock();

        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        double space_used = n * sizeof(int) + (n * sizeof(int) * 2); // Array size + temporary arrays

        fprintf(file, "%d %f %f\n", n, time_taken, space_used);

        free(arr);
    }

    fclose(file);

    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe)
    {
        fprintf(gnuplotPipe, "set title 'Merge Sort Performance'\n");
        fprintf(gnuplotPipe, "set xlabel 'Number of Elements (n)'\n");
        fprintf(gnuplotPipe, "set ylabel 'Time Taken (seconds)'\n");
        fprintf(gnuplotPipe, "set y2label 'Space Used (bytes)'\n");
        fprintf(gnuplotPipe, "set ytics nomirror\n");
        fprintf(gnuplotPipe, "set y2tics\n");
        fprintf(gnuplotPipe, "plot 'mergeSortData.txt' using 1:2 with linespoints title 'Time Complexity', 'mergeSortData.txt' using 1:3 axes x1y2 with linespoints title 'Space Complexity'\n");
        pclose(gnuplotPipe);
    }
    else
    {
        printf("Error opening Gnuplot!\n");
    }
    printf("Graph plotted using Gnuplot.\n");

    return 0;
}