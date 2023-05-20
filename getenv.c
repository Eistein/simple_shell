#include "shell.h"

/**
 * get_env - returns string copy of our env
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_env(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strs(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * rm_env - Remove environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int rm_env(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t k = 0;
	char *ptr;

	if (!node || !var)
		return (0);

	while (node)
	{
		ptr = string_starts_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			info->env_changed = del_node_at(&(info->env), k);
			k = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		k++;
	}
	return (info->env_changed);
}

/**
 * set_env - Initialize a new environment variable,
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int set_env(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *s;

	if (!var || !value)
		return (0);

	buf = malloc(string_length(var) + string_length(value) + 2);
	if (!buf)
		return (1);
	string_copy(buf, var);
	string_concatenate(buf, "=");
	string_concatenate(buf, value);
	node = info->env;
	while (node)
	{
		s = string_starts_with(node->str, var);
		if (s && *s == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_to_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
