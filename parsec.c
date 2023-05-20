#include "shell.h"
/**
 * _executable - checks if the file is an executable
 * @info: a pointer to info
 * @p: path to file
 *
 * Return: 0
 */
int _executable(info_t *info, char *p)
{
	struct stat st;
	(void)info;

	if (!p || stat(p, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * duplicate_c - duplicates characters
 * @p_str: PATH string
 * @start: start index
 * @stp: stop index
 *
 * Return: 0
 */
char *duplicate_c(char *p_str, int start, int stp)
{
	static char buf[1024];
	int l = 0, n = 0;

	for (n = 0, l = start; l < stp; l++)
	if (p_str[l] != ':')
		buf[n++] = p_str[l];
	buf[n] = 0;
	return (buf);
}
/**
 * find_cmd_path - finds path of command in the PATH
 * @info: a pointer to info
 * @p_str: the PATH string
 * @cmd: the cmd to find
 *
 * Return: path of cmd or NULL
 */
char *find_cmd_path(info_t *info, char *p_str, char *cmd)
{
	int l = 0, curr_pos = 0;
	char *path;

	if (!p_str)
		return (NULL);
	if ((string_length(cmd) > 2) && string_starts_with(cmd, "./"))
	{
		if (_executable(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!p_str[l] || p_str[l] == ':')
		{
			path = duplicate_c(p_str, curr_pos, l);
			if (!*path)
			string_concatenate(path, cmd);
			else
			{
				string_concatenate(path, "/");
				string_concatenate(path, cmd);
			}
			if (_executable(info, path))
				return (path);
			if (!p_str[l])
				break;
			curr_pos = l;
		}
		l++;
	}
	return (NULL);
}
