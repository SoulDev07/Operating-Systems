#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void createChild(int n)
{
    if (n == 0)
        return;

    pid_t pid = fork();

    if (pid == 0)
    {
        // Child process
        printf("Child %d: My process ID is %d\n", n, getpid());

        createChild(n - 1);

        printf("Child %d: Exiting\n", n);
        _exit(0);
    }
    else if (pid > 0)
    {
        // Parent process
        wait(NULL);
    }
}

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    printf("Parent: My process ID is %d\n", getpid());
    createChild(n);
    return 0;
}
