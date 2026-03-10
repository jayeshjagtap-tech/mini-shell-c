# Mini Shell (msh)

This project is a simple implementation of a Linux mini shell written in C.
It was developed as part of a systems programming project to understand how shells execute commands, manage processes, and handle signals.

The shell reads commands from the user, executes built-in or external commands, and supports features like background execution, pipes, and input/output redirection.

## Features

* Execution of normal Linux commands
* Built-in commands:

  * `cd`
  * `pwd`
  * `exit`
  * `jobs`
  * `fg`
  * `bg`
* Background process execution using `&`
* Job control
* Pipe support (`|`)
* Input and output redirection (`<`, `>`, `>>`)
* Signal handling

  * `Ctrl + C` to terminate foreground process
  * `Ctrl + Z` to suspend process

## Project Structure

```
msh.c                Main shell loop
commands.c           Command parsing and execution
jobs.c               Job control implementation
pipe.c               Pipe handling
redirect.c           Input/Output redirection
prompt.c             Shell prompt display
signal_handling.c    Signal handling logic
msh.h                Header file
Makefile             Compilation file
```

## Compilation

To compile the project:

```
make
```

## Run the Shell

```
./msh
```

Example commands:

```
sleep 20 &
jobs
fg <pid>
bg <pid>
ls | wc
ls > output.txt
```

## Learning Outcome

This project helped in understanding:

* Process creation using `fork()`
* Command execution using `execvp()`
* Process control using `wait()` and signals
* Inter-process communication using pipes
* File descriptor manipulation for redirection

## Author

Jayesh Jagtap

Electronics and Telecommunication Engineering

Dr. D. Y. Patil Institute of Technology
