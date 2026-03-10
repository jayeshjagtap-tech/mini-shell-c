#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include "msh.h"

t_job *job_list = NULL;

/* insert job in list */
void insertJob(pid_t pid, char *cmd, char state)
{
    t_job *j = malloc(sizeof(t_job));

    j->pid = pid;
    snprintf(j->cmd, 1024, "%s", cmd);
    j->state = state;

    j->next = job_list;
    job_list = j;
}

/* delete job */
void deleteJob(pid_t pid)
{
    t_job **cur = &job_list;

    while (*cur)
    {
        if ((*cur)->pid == pid)
        {
            t_job *tmp = *cur;
            *cur = (*cur)->next;
            free(tmp);
            return;
        }
        cur = &(*cur)->next;
    }
}

/* get job by pid */
t_job *getJob(pid_t pid)
{
    t_job *j = job_list;

    while (j)
    {
        if (j->pid == pid)
            return j;
        j = j->next;
    }
    return NULL;
}

/* print job list */
void printJobs()
{
    t_job *j = job_list;

    while (j)
    {
        printf("[%d] %c %s\n", j->pid, j->state, j->cmd);
        j = j->next;
    }
}

/* bring job to foreground */
void bringFg(pid_t pid)
{
    t_job *j = getJob(pid);

    if (!j)
    {
        printf("No such job\n");
        return;
    }

    fg_pid = pid;

    kill(pid, SIGCONT);

    int status;
    waitpid(pid, &status, WUNTRACED);

    if (WIFSTOPPED(status))
        j->state = SUSPENDED;
    else
        deleteJob(pid);

    fg_pid = -1;
}

/* resume job in background */
void bringBg(pid_t pid)
{
    t_job *j = getJob(pid);

    if (!j)
    {
        printf("No such job\n");
        return;
    }

    kill(pid, SIGCONT);
    j->state = BACKGROUND;

    printf("[%d] Running %s\n", pid, j->cmd);
}