#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include<stdlib.h>
#include <sys/wait.h>
#include "msh.h"

/* handle pipe command */
void handlePipe(char *input)
{
    char *cmds[10];
    int i = 0;

    cmds[i] = strtok(input, "|");

    while (cmds[i])
        cmds[++i] = strtok(NULL, "|");

    int fd[2];
    int in = 0;

    for (int j = 0; j < i; j++)
    {
        pipe(fd);

        if (fork() == 0)
        {
            dup2(in, 0);

            if (cmds[j+1])
                dup2(fd[1], 1);

            close(fd[0]);

            execlp("sh", "sh", "-c", cmds[j], NULL);
            exit(1);
        }
        else
        {
            wait(NULL);
            close(fd[1]);
            in = fd[0];
        }
    }
}