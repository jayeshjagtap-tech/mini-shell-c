#include <stdio.h>
#include <string.h>
#include "msh.h"

int last_exit_status = 0;   // last command exit status
pid_t fg_pid = -1;          // foreground process id

int main()
{
    char input[1024];

    welcomeScreen();   // print welcome message
    initSignals();     // register signals

    while (1)
    {
        shellPrompt(); // show shell prompt

        if (!fgets(input, sizeof(input), stdin))
            continue;

        input[strcspn(input, "\n")] = 0;   // remove newline

        if (strlen(input) == 0)
            continue;

        handleUserCommand(input);  // process command
    }

    return 0;
}