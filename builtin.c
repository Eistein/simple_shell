#include "shell.h"

/**
 * my_exit - exit a shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int my_exit(info_t *info)
{
	int exitk;

	if (info->argv[1])
	{
		exitk = string_to_i(info->argv[1]);
		if (exitk == -1)
		{
			info->status = 2;
			display_error(info, "Illegal number: ");
			_error(info->argv[1]);
			_error_char('\n');
			return (1);
		}
		info->err_num = string_to_i(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * now_dr - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int now_dr(info_t *info)
{
	char *t, *dir, buffer[1024];
	int ch_ret;

	t = getcwd(buffer, 1024);
	if (!t)
		print_string("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = ge_to_env(info, "HOME=");
		if (!dir)
			ch_ret = /* TODO: what should this be? */
				chdir((dir = ge_to_env(info, "PWD=")) ? dir : "/");
		else
			ch_ret = chdir(dir);
	}
	else if (string_compare(info->argv[1], "-") == 0)
	{
		print_string(ge_to_env(info, "OLDPWD=")), _putchar('\n');
			chdir((dir = ge_to_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		ch_ret = chdir(info->argv[1]);
	if (ch_ret == -1)
	{
		display_error(info, "can't cd to ");
		_error(info->argv[1]), _error_char('\n');
	}
	else
	{
		set_env(info, "OLDPWD", ge_to_env(info, "PWD="));
		set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * m_help - changes the current directory
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int m_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	print_string("help call work. Function not yet implemented \n");
	if (0)
		print_string(*arg_array);
	return (0);
}
