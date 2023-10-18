#ifndef SIMPLE_H
#define SIMPLE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

int _putchar(char c);

void execute_command(const char *cmd, char *arguments[]);
void execute_command_with_args(const char *command_line);
void execute_command_with_path(char *cmd, char *arguments[]);
void split_command_line(const char *command_line, char **cmd, char **arguments);
void shell_loop(void);
void print_environment(void);
#endif
