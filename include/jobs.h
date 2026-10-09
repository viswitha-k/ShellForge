#ifndef JOBS_H
#define JOBS_H

#include <sys/types.h>

#define MAX_JOBS 32

#define JOB_RUNNING 1
#define JOB_STOPPED 2
#define JOB_DONE 3

typedef struct
{
    int id;
    pid_t pgid;
    char command[256];
    int state;
} Job;

void init_jobs(void);
int add_job(pid_t pgid, const char *command, int state);
void remove_job(int id);
Job *get_job(int id);
void list_jobs(void);
void update_job_status(void);

#endif
