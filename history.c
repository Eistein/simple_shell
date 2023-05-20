#include "shell.h"
/**
 * get_hi_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */
char *get_hi_file(info_t *info)
{
	char *buf, *dir;

	dir = ge_to_env(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) *
			(string_length(dir) + string_length(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	string_copy(buf, dir);
	string_concatenate(buf, "/");
	string_concatenate(buf, HIST_FILE);
	return (buf);
}
/**
 * write_hi - creates a file or appends to existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_hi(info_t *info)
{
	ssize_t fa;
	char *filename = get_hi_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);
	fa = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fa == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_print_to_fd(node->str, fa);
		_filedescriptor('\n', fa);
	}
	_filedescriptor(BUF_FLUSH, fa);
	close(fa);
	return (1);
}
/**
 * read_hi - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_hi(info_t *info)
{
	int k, last = 0, linecount = 0;
	ssize_t fa, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_hi_file(info);

	if (!filename)
		return (0);
	fa = open(filename, O_RDONLY);
	free(filename);
	if (fa == -1)
		return (0);
	if (!fstat(fa, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fa, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fa);
	for (k = 0; k < fsize; k++)
		if (buf[k] == '\n')
		{
			buf[k] = 0;
			build_hi_list(info, buf + last, linecount++);
			last = k + 1;
		}
	if (last != k)
		build_hi_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		del_node_at(&(info->history), 0);
	renum_history(info);
	return (info->histcount);
}
/**
 * build_hi_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_hi_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_to_end(&node, buf, linecount);
	if (!info->history)
		info->history = node;
	return (0);
}
/**
 * renum_history - recount the history linked list
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renum_history(info_t *info)
{
	list_t *node = info->history;
	int k = 0;

	while (node)
	{
		node->num = k++;
		node = node->next;
	}
	return (info->histcount = k);
}
