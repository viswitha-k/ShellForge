#ifndef JOB_CONTROL_H
#define JOB_CONTROL_H

#include <sys/types.h>

void init_job_control(void);

int launch_job(char **argv,
               const char *command,
               int background);

void bring_job_foreground(int job_id);

void continue_job_background(int job_id);

void handle_child_status(void);

#endif
