#include "simple.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 *split_command_line - Tokenize the command line into command and arguments.
 *@command_line: The input command line.
 *@cmd: A pointer to store the command.
 *@arguments: An array to store the arguments.
 *
 *This function tokenizes the input command line, separates the command from
 *its arguments, and stores them in the 'cmd' and 'arguments' variables.
 */
void split_command_line(const char *command_line, char **cmd, char **arguments)
{
	int arg_count = 0;
	*cmd = strtok(strdup(command_line), " ");

	while ((arguments[arg_count] = strtok(NULL, " ")) != NULL)
	{
		arg_count++;
	}

	arguments[arg_count] = NULL;
}

/**
 *execute_command_with_path - Execute a command with PATH lookup.
 *@cmd: The command to execute.
 *@arguments: An array of arguments for the command.
 *
 *This function searches for the command in directories specified by PATH and
 *then executes the command if found.
 */
void execute_command_with_path(char *cmd, char *arguments[])
{
	if (cmd)
	{
		pid_t pid;
		int status;
		char *path_env = getenv("PATH"), *path_copy = strdup(path_env);
		char *dir = strtok(path_copy, ":");

		while (dir != NULL)
		{
			char full_path[100];

			snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
			if (access(full_path, X_OK) == 0)
			{
				pid = fork();
				if (pid == -1)
				{
					perror("Fork failed");
				}
				else if (pid == 0)
				{
					execv(full_path, arguments);
					perror("Command execution failed");
					exit(EXIT_FAILURE);
				}
				else
				{
					waitpid(pid, &status, 0);
					break;
				}
			}
			dir = strtok(NULL, ":");
		}
		free(path_copy);
		if (dir == NULL)
		{
			printf("Command not found: %s\n", cmd);
		}
	}
	free(cmd);
}
