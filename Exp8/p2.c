#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHM_KEY 80
#define SHM_SIZE 1024

int main()
{
    char *shared_memory;
    int shmid;

    shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
    if (shmid == -1)
    {
        perror("shmget");
        exit(1);
    }
    printf("shared memory created\n");

    shared_memory = shmat(shmid, NULL, 0);
    if (shared_memory == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }

    sem_t *sem_user1, *sem_user2;

    sem_user1 = sem_open("/sem_user1", 0);
    if (sem_user1 == SEM_FAILED)
    {
        // Cleanup the existing semaphore
        sem_unlink("/sem_user1");

        // Recreate the semaphore
        sem_user1 = sem_open("/sem_user1", O_CREAT | O_EXCL, 0644, 0);
        if (sem_user1 == SEM_FAILED)
        {
            perror("sem_open");
            exit(EXIT_FAILURE);
        }
    }

    sem_user2 = sem_open("/sem_user2", 1);
    if (sem_user2 == SEM_FAILED)
    {
        // Cleanup the existing semaphore
        sem_unlink("/sem_user2");

        // Recreate the semaphore
        sem_user2 = sem_open("/sem_user2", O_CREAT | O_EXCL, 0644, 1);
        if (sem_user2 == SEM_FAILED)
        {
            perror("sem_open");
            exit(EXIT_FAILURE);
        }
    }

    while (1)
    {
        sem_wait(sem_user1); // Wait for User 1 to write
        printf("********** USER 2: USER 1 MESSAGED **********\n");
        printf("User1: %s", shared_memory);
        printf("User2: ");
        fgets(shared_memory, SHM_SIZE, stdin);
        sem_post(sem_user2); // Signal User 2 has written
    }
    return 0;
}