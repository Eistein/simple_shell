#ifndef SIMPLE_H
#define SIMPLE_H

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
#define LSH_USE_STD_GETLINE

int bltn_cmd(char **args);
int bltn_exit(char **args);
int num_bltn(void);
int sh_lp(char **args);
int sh_exect(char **args);
char *sh_read(void);
char **sh_split(char *line);
void sh_shell(void);
int main(void);
#endif
