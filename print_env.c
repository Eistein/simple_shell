#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "simple.h"
/**
 *print_environment - Prints the current environment variables.
 */
void print_environment(void)
{
	extern char **environ;
	char **env;

	for (env = environ; *env; env++)
	{
		printf("%s\n", *env);
	}
}

/**
 *shell_loop - Main loop of the simple shell.
 */
void shell_loop(void)
{
	char input[100];
	char *username = getenv("USER");
	char *homedir = getenv("HOME");

	while (1)
	{
		char cwd[1024];

		getcwd(cwd, sizeof(cwd));

		printf("%s@%s:%s$ ", username, homedir, cwd);

		fgets(input, sizeof(input), stdin);

		input[strcspn(input, "\n")] = '\0';

		if (strcmp(input, "env") == 0)
		{
			print_environment();
		}
	}
}
