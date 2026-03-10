#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "msh.h"

/* handle I/O redirection */
int handleRedirection(char **args)
{
    for (int i = 0; args[i]; i++)
    {
        if (!strcmp(args[i], ">"))
        {
            int fd = open(args[i+1], O_CREAT|O_WRONLY|O_TRUNC, 0644);
            dup2(fd, 1);
            close(fd);
            args[i] = NULL;
            return 1;
        }

        if (!strcmp(args[i], ">>"))
        {
            int fd = open(args[i+1], O_CREAT|O_WRONLY|O_APPEND, 0644);
            dup2(fd, 1);
            close(fd);
            args[i] = NULL;
            return 1;
        }

        if (!strcmp(args[i], "<"))
        {
            int fd = open(args[i+1], O_RDONLY);
            dup2(fd, 0);
            close(fd);
            args[i] = NULL;
            return 1;
        }
    }

    return 0;
}