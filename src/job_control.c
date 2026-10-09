#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>

#include "../include/jobs.h"
#include "../include/job_control.h"

static pid_t shell_pgid = -1;
static struct termios shell_tmodes;
static int job_control_ready = 0;

static void setup_job_control(void)
{
    if (job_control_ready)
        return;

    shell_pgid = getpid();

    if (setpgid(shell_pgid, shell_pgid) < 0)
    {
        if (errno != EACCES && errno != EPERM)
            perror("setpgid");
    }

    /*
     * Do not take terminal control when ShellForge starts.
     * We only take it when an actual foreground job is launched.
     */
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);

    tcgetattr(STDIN_FILENO, &shell_tmodes);

    job_control_ready = 1;
}

void init_job_control(void)
{
    setup_job_control();
    init_jobs();
}

int launch_job(char **argv, const char *command, int background)
{
    setup_job_control();

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return -1;
    }

    if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
        signal(SIGCHLD, SIG_DFL);

        setpgid(0, 0);

        if (!background)
            tcsetpgrp(STDIN_FILENO, getpid());

        execvp(argv[0], argv);

        perror("execvp");
        _exit(127);
    }

    setpgid(pid, pid);

    if (background)
    {
        int id = add_job(pid, command, JOB_RUNNING);

        if (id < 0)
        {
            fprintf(stderr, "Maximum number of jobs reached\n");
            kill(pid, SIGTERM);
            return -1;
        }

        printf("[%d] %d\n", id, pid);
        fflush(stdout);

        return 0;
    }

    tcsetpgrp(STDIN_FILENO, pid);

    int status = 0;

    while (1)
    {
        pid_t result = waitpid(pid, &status, WUNTRACED);

        if (result < 0)
        {
            if (errno == EINTR)
                continue;

            perror("waitpid");
            break;
        }

        break;
    }

    tcsetpgrp(STDIN_FILENO, shell_pgid);

    if (WIFSTOPPED(status))
    {
        int id = add_job(pid, command, JOB_STOPPED);

        if (id >= 0)
        {
            printf("\n[%d]+ Stopped %s\n", id, command);
        }
    }

    return 0;
}

void continue_job_background(int job_id)
{
    Job *job = get_job(job_id);

    if (job == NULL)
    {
        printf("No such job: %d\n", job_id);
        return;
    }

    if (job->state != JOB_STOPPED)
    {
        printf("Job %d is not stopped\n", job_id);
        return;
    }

    if (kill(-job->pgid, SIGCONT) < 0)
    {
        perror("SIGCONT");
        return;
    }

    job->state = JOB_RUNNING;

    printf("[%d]+ Running %s &\n",
           job->id,
           job->command);
}

void bring_job_foreground(int job_id)
{
    Job *job = get_job(job_id);

    if (job == NULL)
    {
        printf("No such job: %d\n", job_id);
        return;
    }

    tcsetpgrp(STDIN_FILENO, job->pgid);

    if (job->state == JOB_STOPPED)
    {
        if (kill(-job->pgid, SIGCONT) < 0)
        {
            perror("SIGCONT");
            tcsetpgrp(STDIN_FILENO, shell_pgid);
            return;
        }

        job->state = JOB_RUNNING;
    }

    int status = 0;

    while (1)
    {
        pid_t result = waitpid(job->pgid, &status, WUNTRACED);

        if (result < 0)
        {
            if (errno == EINTR)
                continue;

            perror("waitpid");
            break;
        }

        break;
    }

    tcsetpgrp(STDIN_FILENO, shell_pgid);

    if (WIFSTOPPED(status))
    {
        job->state = JOB_STOPPED;
    }
    else
    {
        remove_job(job->id);
    }
}

void handle_child_status(void)
{
    update_job_status();
}
