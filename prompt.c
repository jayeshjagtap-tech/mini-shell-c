#include <stdio.h>
#include <stdlib.h>
#include "msh.h"

/* welcome message */
void welcomeScreen()
{
    printf("******** MINI SHELL ********\n");
}

/* print shell prompt */
void shellPrompt()
{
    char *ps1 = getenv("PS1");

    if (ps1)
        printf("%s", ps1);
    else
        printf("msh> ");

    fflush(stdout);
}