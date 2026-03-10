#ifndef MSH_H
#define MSH_H

#include <sys/types.h>

/* Job states */
#define FOREGROUND 'F'
#define BACKGROUND 'B'
#define SUSPENDED  'S'

/* Job structure */
typedef struct job
{
    pid_t pid;           // process id
    char cmd[1024];      // command name
    char state;          // job state
    struct job *next;    // next job
} t_job;

/* global variables */
extern int last_exit_status;
extern pid_t fg_pid;

/* prompt */
void welcomeScreen();
void shellPrompt();

/* command handling */
void handleUserCommand(char *input);
int checkBuiltInCommands(char **args);
void executeCommand(char **args, int bg);

/* built-in command */
void changeDirectory(char **args);

/* job control */
void insertJob(pid_t pid, char *cmd, char state);
void deleteJob(pid_t pid);
t_job *getJob(pid_t pid);
void printJobs();
void bringFg(pid_t pid);
void bringBg(pid_t pid);

/* signals */
void initSignals();
void sigintHandler(int sig);
void sigtstpHandler(int sig);
void sigchldHandler(int sig);

/* pipe and redirection */
void handlePipe(char *input);
int handleRedirection(char **args);

#endif