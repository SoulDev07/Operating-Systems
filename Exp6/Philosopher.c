#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + num_philosophers - 1) % num_philosophers
#define RIGHT (phnum + 1) % num_philosophers

int *state;
int num_philosophers;
sem_t mutex;
sem_t *S;

void test(int phnum)
{
    // Check if the philosopher is hungry and if their neighbors are not eating
    if (state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        state[phnum] = EATING;
        sleep(2);
        printf("Philosopher %d takes fork %d and %d\n", phnum + 1, LEFT + 1, phnum + 1);
        printf("Philosopher %d is Eating\n", phnum + 1);
        sem_post(&S[phnum]);
    }
}

void take_fork(int phnum)
{
    sem_wait(&mutex);
    state[phnum] = HUNGRY;
    printf("Philosopher %d is Hungry\n", phnum + 1);
    test(phnum);
    sem_post(&mutex);
    sem_wait(&S[phnum]);
    sleep(1);
}

void put_fork(int phnum)
{
    sem_wait(&mutex);
    state[phnum] = THINKING;
    printf("Philosopher %d putting fork %d and %d down\n", phnum + 1, LEFT + 1, phnum + 1);
    printf("Philosopher %d is thinking\n", phnum + 1);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void *philosopher(void *num)
{
    int phnum = *((int *)num);

    while (1)
    {
        sleep(1);
        take_fork(phnum);
        sleep(0);
        put_fork(phnum);
    }
}

int main(int argc, char *argv[])
{
    printf("Enter no. of Philosophers: ");
    scanf("%d", &num_philosophers);

    state = malloc(num_philosophers * sizeof(int));
    S = malloc(num_philosophers * sizeof(sem_t));
    pthread_t *thread_id = malloc(num_philosophers * sizeof(pthread_t));

    sem_init(&mutex, 0, 1);
    for (int i = 0; i < num_philosophers; i++)
        sem_init(&S[i], 0, 0);

    // Create threads for each philosopher
    for (int i = 0; i < num_philosophers; i++)
    {
        int *philosopher_id = malloc(sizeof(int));
        *philosopher_id = i;
        pthread_create(&thread_id[i], NULL, philosopher, philosopher_id);
        printf("Philosopher %d is thinking\n", i + 1);
    }

    for (int i = 0; i < num_philosophers; i++)
        pthread_join(thread_id[i], NULL);

    free(state);
    free(S);
    free(thread_id);

    return 0;
}
