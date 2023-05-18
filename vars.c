#include "shell.h"

/**
 * is_delm - test if char is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @dtr: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_delm(info_t *info, char *buf, size_t *dtr)
{
	size_t l = *dtr;

	if (buf[l] == '|' && buf[l + 1] == '|')
	{
		buf[l] = 0;
		l++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[l] == '&' && buf[l + 1] == '&')
	{
		buf[l] = 0;
		l++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[l] == ';')
	{
		buf[l] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*dtr = l;
	return (1);
}

/**
 * _testch - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @dtr: address of current position in buf
 * @k: starting position in buf
 * @len: length of buf
 *
 * Return: nothing
 */
void _testch(info_t *info, char *buf, size_t *dtr, size_t k, size_t len)
{
	size_t j = *dtr;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[k] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[k] = 0;
			j = len;
		}
	}

	*dtr = j;
}

/**
 * _repalias - replaces an aliases in a string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _repalias(info_t *info)
{
	int a;
	list_t *node;
	char *p;

	for (a = 0; a < 10; a++)
	{
		node = node_st_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = str_character(node->str, '=');
		if (!p)
			return (0);
		p = string_duplicate(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * _repvars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _repvars(info_t *info)
{
	int a = 0;
	list_t *node;

	for (a = 0; info->argv[a]; a++)
	{
		if (info->argv[a][0] != '$' || !info->argv[a][1])
			continue;

		if (!string_compare(info->argv[a], "$?"))
		{
			rep_string(&(info->argv[a]),
				string_duplicate(convert_num(info->status, 10, 0)));
			continue;
		}
		if (!string_compare(info->argv[a], "$$"))
		{
			rep_string(&(info->argv[a]),
				string_duplicate(convert_num(getpid(), 10, 0)));
			continue;
		}
		node = node_st_with(info->env, &info->argv[a][1], '=');
		if (node)
		{
			rep_string(&(info->argv[a]),
				string_duplicate(str_character(node->str, '=') + 1));
			continue;
		}
		rep_string(&info->argv[a], string_duplicate(""));

	}
	return (0);
}

/**
 * rep_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
