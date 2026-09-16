#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int execute(char **tokens)
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid == 0)
    {
        if (execvp(tokens[0], tokens) == -1)
        {
            perror("ShellForge");
        }

        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        perror("fork");
    }
    else
    {
        do
        {
            waitpid(pid, &status, WUNTRACED);

        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}
