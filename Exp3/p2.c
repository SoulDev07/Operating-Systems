#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();

    if (pid > 0)
    {
        // Parent process
        wait(NULL);
        printf("Parent: The child with process ID %d has terminated.\n", pid);
        printf("Parent: My process ID is: %d\n", getpid());
        printf("Parent: The child process ID is: %d\n", pid);
    }
    else if (pid == 0)
    {
        // Child process
        printf("Child: My process ID is: %d\n", getpid());
        printf("Child: The parent process ID is: %d\n", getppid());
    }

    return 0;
}
