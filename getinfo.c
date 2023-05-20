#include "shell.h"
/**
 * shell_info - initializes information
 * @info: address
 */
void shell_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
/**
 * _info - initializes info_t struct
 * @info: struct address
 * @v: argument
 */
void _info(info_t *info, char **v)
{
	int n = 0;

	info->fname = v[0];
	if (info->arg)
	{
		info->argv = s_string(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = string_duplicate(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (n = 0; info->argv && info->argv[n]; n++)
		info->argc = n;
		_repalias(info);
		_repvars(info);
	}
}
/**
 * rel_info - frees info_t struct fields
 * @info: address
 * @a: true if freeing all fields
 */
void rel_info(info_t *info, int a)
{
	free_str(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (a)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_l(&(info->env));
		if (info->history)
			free_l(&(info->history));
		if (info->alias)
			free_l(&(info->alias));
		free_str(info->environ);
			info->environ = NULL;
		f_pointer((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
