#include "shell.h"

/**
 * m_env - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int m_env(info_t *info)
{
	print_str_l(info->env);
	return (0);
}

/**
 * ge_to_env - gets the value of an environ
 * @info: Structure containing potential arguments. Used to maintain
 * @nam: env var name
 *
 * Return: the value
 */
char *ge_to_env(info_t *info, const char *nam)
{
	list_t *node = info->env;
	char *s;

	while (node)
	{
		s = string_starts_with(node->str, nam);
		if (s && *s)
			return (s);
		node = node->next;
	}
	return (NULL);
}

/**
 * my_set - Initialize a new environment variable,
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int my_set(info_t *info)
{
	if (info->argc != 3)
	{
		_error("Incorrect number of arguements\n");
		return (1);
	}
	if (set_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * un_set - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int un_set(info_t *info)
{
	int k;

	if (info->argc == 1)
	{
		_error("Too few arguements.\n");
		return (1);
	}
	for (k = 1; k <= info->argc; k++)
		rm_env(info, info->argv[k]);

	return (0);
}

/**
 * pop_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int pop_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t v;

	for (v = 0; environ[v]; v++)
		add_to_end(&node, environ[v], 0);
	info->env = node;
	return (0);
}
