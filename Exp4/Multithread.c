#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define MAX_NUMBERS 100

int num_arr[MAX_NUMBERS];
int num_len;

double avg;
int max, median;

void bubble_sort(int *arr, int n)
{
    int temp;
    bool flag = true;
    for (int i = 0; i < n - 1 && flag; i++)
    {
        flag = 0;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                flag = false;
            }
        }
    }
}

// Function to calculate average of numbers
void *calculate_average(void *arg)
{
    double sum = 0;
    for (int i = 0; i < num_len; i++)
        sum += num_arr[i];

    avg = sum / num_len;

    pthread_exit(NULL);
}

// Function to get maximum number
void *calculate_maximum(void *arg)
{
    max = num_arr[0];
    for (int i = 1; i < num_len; i++)
        if (num_arr[i] > max)
            max = num_arr[i];

    pthread_exit(NULL);
}

// Function to get median
void *calculate_median(void *arg)
{
    int temp[MAX_NUMBERS];
    for (int i = 0; i < num_len; i++)
        temp[i] = num_arr[i];

    bubble_sort(temp, num_len);

    if (num_len % 2 == 0)
        median = (temp[num_len / 2 - 1] + temp[num_len / 2]) / 2;
    else
        median = temp[num_len / 2];

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("Usage: <number1> <number2> ... <numberN>\n");
        return -1;
    }

    // Get numbers from command line arguments
    num_len = argc - 1;
    for (int i = 0; i < num_len; i++)
        num_arr[i] = atoi(argv[i + 1]);

    // Create 3 threads and assign tasks
    pthread_t threads[3];
    pthread_create(&threads[0], NULL, calculate_average, NULL);
    pthread_create(&threads[1], NULL, calculate_maximum, NULL);
    pthread_create(&threads[2], NULL, calculate_median, NULL);

    // Wait for all threads to finish
    for (int i = 0; i < 3; i++)
        pthread_join(threads[i], NULL);

    // Print results
    printf("Average: %.2lf\n", avg);
    printf("Maximum: %d\n", max);
    printf("Median: %d\n", median);

    return 0;
}
