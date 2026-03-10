#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "msh.h"

/* parse user command */
void handleUserCommand(char *input)
{
    if (strchr(input, '|'))   // check pipe
    {
        handlePipe(input);
        return;
    }

    char *args[100];
    int i = 0, bg = 0;

    /* check background execution */
    if (input[strlen(input)-1] == '&')
    {
        bg = 1;
        input[strlen(input)-1] = '\0';
    }

    /* tokenize command */
    args[i] = strtok(input, " ");
    while (args[i])
        args[++i] = strtok(NULL, " ");

    if (!args[0])
        return;

    /* echo variables */
    if (!strcmp(args[0], "echo") && args[1])
    {
        if (!strcmp(args[1], "$?"))
        {
            printf("%d\n", last_exit_status);
            return;
        }
        if (!strcmp(args[1], "$$"))
        {
            printf("%d\n", getpid());
            return;
        }
    }

    /* built in commands */
    if (checkBuiltInCommands(args))
        return;

    executeCommand(args, bg);
}

/* check built-in commands */
int checkBuiltInCommands(char **args)
{
    if (!strcmp(args[0], "exit"))
        exit(0);

    if (!strcmp(args[0], "pwd"))
    {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        printf("%s\n", cwd);
        return 1;
    }

    if (!strcmp(args[0], "cd"))
    {
        changeDirectory(args);
        return 1;
    }

    if (!strcmp(args[0], "jobs"))
    {
        printJobs();
        return 1;
    }

    if (!strcmp(args[0], "fg"))
    {
        bringFg(atoi(args[1]));
        return 1;
    }

    if (!strcmp(args[0], "bg"))
    {
        bringBg(atoi(args[1]));
        return 1;
    }

    return 0;
}

/* execute external command */
void executeCommand(char **args, int bg)
{
    pid_t pid = fork();

    if (pid == 0)   // child process
    {
        handleRedirection(args);
        execvp(args[0], args);
        perror("execvp");
        exit(1);
    }
    else
    {
        if (bg)     // background execution
        {
            insertJob(pid, args[0], BACKGROUND);
            printf("[%d] Running %s\n", pid, args[0]);
        }
        else        // foreground execution
        {
            fg_pid = pid;

            int status;
            waitpid(pid, &status, WUNTRACED);

            if (WIFSTOPPED(status))
            {
                insertJob(pid, args[0], SUSPENDED);
                printf("\n[%d] Stopped\n", pid);
            }

            if (WIFEXITED(status))
                last_exit_status = WEXITSTATUS(status);

            fg_pid = -1;
        }
    }
}

/* change directory */
void changeDirectory(char **args)
{
    if (!args[1])
        chdir(getenv("HOME"));
    else
        chdir(args[1]);
}