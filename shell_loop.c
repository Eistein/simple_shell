#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @a: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **a)
{
	ssize_t k = 0;
	int builtin_ret = 0;

	while (k != -1 && builtin_ret != -2)
	{
		shell_info(info);
		if (interactive(info))
			print_string("$ ");
		_error_char(BUF_FLUSH);
		k = _getput(info);
		if (k != -1)
		{
			_info(info, a);
			builtin_ret = f_builtin(info);
			if (builtin_ret == -1)
				f_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		rel_info(info, 0);
	}
	write_hi(info);
	rel_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * f_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int f_builtin(info_t *info)
{
	int k, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", my_exit},
		{"env", m_env},
		{"help", m_help},
		{"history", my_story},
		{"set_env", my_set},
		{"rm_env", un_set},
		{"cd", now_dr},
		{"alias", m_alias},
		{NULL, NULL}
	};

	for (k = 0; builtintbl[k].type; k++)
		if (string_compare(info->argv[0], builtintbl[k].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[k].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * f_cmd - finds a command in path
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void f_cmd(info_t *info)
{
	char *path = NULL;
	int k, j;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (k = 0, j = 0; info->arg[k]; k++)
		if (!check_delim(info->arg[j], " \t\n"))
			j++;
	if (!j)
		return;

	path = find_cmd_path(info, ge_to_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fo_cmd(info);
	}
	else
	{
		if ((interactive(info) || ge_to_env(info, "PATH=")
			|| info->argv[0][0] == '/') && _executable(info, info->argv[0]))
			fo_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			display_error(info, "not found\n");
		}
	}
}

/**
 * fo_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fo_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_env(info)) == -1)
		{
			rel_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				display_error(info, "Permission denied\n");
		}
	}
}
