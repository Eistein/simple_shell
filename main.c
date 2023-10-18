#include <stdio.h>
#include <stdlib.h>
#include "simple.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
int main(void)
{
	while (1)
	{
		char input[100];
		char *cmd;
		char *arguments[100];
		size_t length = strlen(input);

		printf("my_simple_shell > ");
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			if (strcmp(input, "exit\n") == 0)
			{
				printf("Exiting the shell...\n");
				exit(0);
			}
			printf("\n");
			break;
		}

		if (length > 0 && input[length - 1] == '\n')
		{
			input[length - 1] = '\0';
		}

		split_command_line(input, &cmd, arguments);
		execute_command_with_path(cmd, arguments);
		execute_command_with_args(input);
		execute_command(input, NULL);
		shell_loop();
	}

	return (0);
}
