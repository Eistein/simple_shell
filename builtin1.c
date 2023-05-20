#include "shell.h"

/**
 * my_story - displays the history list, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int my_story(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * un_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int un_alias(info_t *info, char *str)
{
	char *p, k;
	int resu;

	p = str_character(str, '=');
	if (!p)
		return (1);
	k = *p;
	*p = 0;
	resu = del_node_at(&(info->alias),
		get_index(info->alias, node_st_with(info->alias, str, -1)));
	*p = k;
	return (resu);
}

/**
 * set_as - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_as(info_t *info, char *str)
{
	char *j;

	j = str_character(str, '=');
	if (!j)
		return (1);
	if (!*++j)
		return (un_alias(info, str));

	un_alias(info, str);
	return (add_to_end(&(info->alias), str, 0) == NULL);
}

/**
 * pr_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int pr_alias(list_t *node)
{
	char *p = NULL, *l = NULL;

	if (node)
	{
		p = str_character(node->str, '=');
		for (l = node->str; l <= p; l++)
			_putchar(*l);
		_putchar('\'');
		print_string(p + 1);
		print_string("'\n");
		return (0);
	}
	return (1);
}

/**
 * m_alias - mimics the alias builtin
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int m_alias(info_t *info)
{
	int k = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			pr_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (k = 1; info->argv[k]; k++)
	{
		p = str_character(info->argv[k], '=');
		if (p)
			set_as(info, info->argv[k]);
		else
			pr_alias(node_st_with(info->alias, info->argv[k], '='));
	}

	return (0);
}
