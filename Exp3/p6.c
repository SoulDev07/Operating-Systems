#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();

    if (pid > 0)
    {
        // Parent process
        printf("Parent: My process ID is: %d\n", getpid());
        printf("Parent: The child process ID is: %d\n", pid);

        sleep(60);

        wait(NULL);
    }
    else if (pid == 0)
    {
        // Child process
        printf("Child: My process ID is: %d\n", getpid());
        printf("Child: The parent process ID is: %d\n", getppid());

        getchar();
    }

    return 0;
}
