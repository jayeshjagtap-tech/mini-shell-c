#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include "msh.h"

/* ctrl + c */
void sigintHandler(int sig)
{
    if (fg_pid > 0)
        kill(fg_pid, SIGINT);

    printf("\n");
}

/* ctrl + z */
void sigtstpHandler(int sig)
{
    if (fg_pid > 0)
    {
        kill(fg_pid, SIGTSTP);

        insertJob(fg_pid, "Stopped", SUSPENDED);

        printf("\n[%d] Stopped\n", fg_pid);

        fg_pid = -1;
    }
}

/* handle background process termination */
void sigchldHandler(int sig)
{
    int status;
    pid_t pid;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
        deleteJob(pid);
}

/* register signals */
void initSignals()
{
    signal(SIGINT, sigintHandler);
    signal(SIGTSTP, sigtstpHandler);
    signal(SIGCHLD, sigchldHandler);
}