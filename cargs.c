#include "simple.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 *execute_command - Execute a command.
 *@cmd: The command to execute.
 *@arguments: Array of arguments.
 */
void execute_command(const char *cmd, char *arguments[])
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
	}
	else if (pid == 0)
	{
		execv(cmd, arguments);
		perror("Command execution failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

/**
 *execute_command_with_args - Execute a command with arguments.
 *@command_line: The input command line.
 */
void execute_command_with_args(const char *command_line)
{
	char *cmd = strtok(strdup(command_line), " "), *arguments[100];
	int arg_count = 0;

	while ((arguments[arg_count] = strtok(NULL, " ")) != NULL)
	{
		arg_count++;
	}

	arguments[arg_count] = NULL;
	if (cmd)
	{
		if (strchr(cmd, '/') != NULL)
		{
			execute_command(cmd, arguments);
		}
		else
		{
			char *path = getenv("PATH"), *path_copy = strdup(path);
			char *dir = strtok(path_copy, ":");

			while (dir != NULL)
			{
				char full_path[100];

				snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
				if (access(full_path, X_OK) == 0)
				{
					execute_command(full_path, arguments);
					break;
				}
				dir = strtok(NULL, ":");
			}
			free(path_copy);
			if (dir == NULL)
			{
				printf("Command not found: %s\n", cmd);
			}
		}
	}
	free(cmd);
}
