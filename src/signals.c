#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

static void sigint_handler(int sig)
{
    (void)sig;

    printf("\nShellForge: Press 'exit' to quit.\n");
    printf("myshell> ");
    fflush(stdout);
}

static void sigchld_handler(int sig)
{
    (void)sig;
}

void initialize_signals(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGCHLD, sigchld_handler);
}
