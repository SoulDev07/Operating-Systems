#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/file.h>

#define MAX_BUFFER_SIZE 64
#define NUM_READERS 5

int line = 1;

void *writeFile(void *arg)
{
    while (1)
    {
        int target_file = open("file.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
        if (target_file == -1)
        {
            printf("\nThe file is not opened. The program will now exit.");
            exit(EXIT_FAILURE);
        }

        // Get Exclusive Lock
        if (flock(target_file, LOCK_EX) == -1)
        {
            printf("\nThe file cannot be locked. The program will now exit.");
            exit(EXIT_FAILURE);
        }

        char str[MAX_BUFFER_SIZE];
        sprintf(str, "Line %d\n", line);
        write(target_file, str, strlen(str)); // Write string to file
        printf("\nWriter has written line %d", line);
        line++;

        // Unlock file
        if (flock(target_file, LOCK_UN) == -1)
        {
            printf("\nThe file cannot be unlocked. The program will now exit.");
            exit(EXIT_FAILURE);
        }
        close(target_file);
        sleep(1);
    }
    return NULL;
}

void *readFile(void *arg)
{
    int id = *(int *)arg;

    while (1)
    {
        int target_file = open("file.txt", O_RDONLY | O_CREAT, 0644);
        // Read from the file
        printf("\nReader %d is reading\n", id);
        if (target_file == -1)
        {
            printf("\nThe file is not opened. The program will now exit.");
            exit(EXIT_FAILURE);
        }
        // Get Shared Lock
        if (flock(target_file, LOCK_SH) == -1)
        {
            printf("\nThe file cannot be locked. The program will now exit.");
            exit(EXIT_FAILURE);
        }

        char buf[MAX_BUFFER_SIZE];
        printf("\n");
        while (read(target_file, buf, MAX_BUFFER_SIZE) > 0)
            printf("%s", buf);

        // Unlock file
        if (flock(target_file, LOCK_UN) == -1)
        {
            printf("\nThe file cannot be unlocked. The program will now exit.");
            exit(EXIT_FAILURE);
        }
        close(target_file);
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t writer_thread;
    pthread_t reader_threads[NUM_READERS];

    // Create writer thread
    pthread_create(&writer_thread, NULL, writeFile, NULL);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++)
    {
        int *reader_id = malloc(sizeof(int));
        *reader_id = i + 1;
        pthread_create(&reader_threads[i], NULL, readFile, (void *)reader_id);
    }

    while (1)
        sleep(1);

    return 0;
}
