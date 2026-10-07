#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int execute_redirection(char **args)
{
    int i;

    for (i = 0; args[i] != NULL; i++)
    {
        /* Output redirection: > */
        if (strcmp(args[i], ">") == 0)
        {
            if (args[i + 1] == NULL)
            {
                fprintf(stderr, "Invalid redirection command\n");
                return 1;
            }

            char *filename = args[i + 1];
            args[i] = NULL;

            int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

            if (fd < 0)
            {
                perror("open");
                return 1;
            }

            pid_t pid = fork();

            if (pid < 0)
            {
                perror("fork");
                close(fd);
                return 1;
            }

            if (pid == 0)
            {
                if (dup2(fd, STDOUT_FILENO) < 0)
                {
                    perror("dup2");
                    close(fd);
                    exit(EXIT_FAILURE);
                }

                close(fd);

                execvp(args[0], args);
                perror("execvp");
                exit(EXIT_FAILURE);
            }

            close(fd);
            waitpid(pid, NULL, 0);
            return 1;
        }

        /* Append redirection: >> */
        if (strcmp(args[i], ">>") == 0)
        {
            if (args[i + 1] == NULL)
            {
                fprintf(stderr, "Invalid redirection command\n");
                return 1;
            }

            char *filename = args[i + 1];
            args[i] = NULL;

            int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);

            if (fd < 0)
            {
                perror("open");
                return 1;
            }

            pid_t pid = fork();

            if (pid < 0)
            {
                perror("fork");
                close(fd);
                return 1;
            }

            if (pid == 0)
            {
                if (dup2(fd, STDOUT_FILENO) < 0)
                {
                    perror("dup2");
                    close(fd);
                    exit(EXIT_FAILURE);
                }

                close(fd);

                execvp(args[0], args);
                perror("execvp");
                exit(EXIT_FAILURE);
            }

            close(fd);
            waitpid(pid, NULL, 0);
            return 1;
        }

        /* Input redirection: < */
        if (strcmp(args[i], "<") == 0)
        {
            if (args[i + 1] == NULL)
            {
                fprintf(stderr, "Invalid redirection command\n");
                return 1;
            }

            char *filename = args[i + 1];
            args[i] = NULL;

            int fd = open(filename, O_RDONLY);

            if (fd < 0)
            {
                perror("open");
                return 1;
            }

            pid_t pid = fork();

            if (pid < 0)
            {
                perror("fork");
                close(fd);
                return 1;
            }

            if (pid == 0)
            {
                if (dup2(fd, STDIN_FILENO) < 0)
                {
                    perror("dup2");
                    close(fd);
                    exit(EXIT_FAILURE);
                }

                close(fd);

                execvp(args[0], args);
                perror("execvp");
                exit(EXIT_FAILURE);
            }

            close(fd);
            waitpid(pid, NULL, 0);
            return 1;
        }

        /* Error redirection: 2> */
        if (strcmp(args[i], "2>") == 0)
        {
            if (args[i + 1] == NULL)
            {
                fprintf(stderr, "Invalid redirection command\n");
                return 1;
            }

            char *filename = args[i + 1];
            args[i] = NULL;

            int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

            if (fd < 0)
            {
                perror("open");
                return 1;
            }

            pid_t pid = fork();

            if (pid < 0)
            {
                perror("fork");
                close(fd);
                return 1;
            }

            if (pid == 0)
            {
                if (dup2(fd, STDERR_FILENO) < 0)
                {
                    perror("dup2");
                    close(fd);
                    exit(EXIT_FAILURE);
                }

                close(fd);

                execvp(args[0], args);
                perror("execvp");
                exit(EXIT_FAILURE);
            }

            close(fd);
            waitpid(pid, NULL, 0);
            return 1;
        }
    }

    return 0;
}
