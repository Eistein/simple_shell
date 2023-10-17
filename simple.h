#ifndef SIMPLE_H
#define SIMPLE_H

int _putchar(char c);

char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

char **_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

void execute_command(const char *cmd, char *arguments[]);
void execute_command_with_args(const char *command_line);
void execute_command_with_path(const char *command_line);
#endif
