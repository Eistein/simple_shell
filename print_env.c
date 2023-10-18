#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "simple.h"

/**
 * sh_exct - execute program launch
 *
 * @args: Null terminated list of arguments
 *
 * Return: 1 to continue running and 0 to terminate
 */

int sh_exct(char **args)
{
	char *builtin_str[] = {
		"cd",
		"exit"};

	int (*builtin_func[])(char **) = {
		&bltn_cmd,
		&bltn_exit};

	int j;

	if (args[0] == NULL)
	{
		return (1);
	}
	for (j = 0; j < num_bltn(); j++)
	{
		if (strcmp(args[0], builtin_str[j]) == 0)
		{
			return ((*builtin_func[j])(args));
		}
	}

	return (sh_lp(args));
}

/**
 * sh_shell - loop that gets inputs and executes functions
 *
 * Return: void
 */

void sh_shell(void)
{
	char *line;
	char **args;
	int status;

	do {
		printf("$ ");
		line = sh_read();
		args = sh_split(line);
		status = sh_exct(args);

		free(line);
		free(args);
	} while (status);
}

/**
 * main - main shell function
 *
 * Return: status code
 */

int main(void)
{
	sh_shell();

	return (EXIT_SUCCESS);
}
