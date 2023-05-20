#include "shell.h"

/**
 * list_lght - dispaly length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_lght(const list_t *h)
{
	size_t k = 0;

	while (h)
	{
		h = h->next;
		k++;
	}
	return (k);
}

/**
 * list_to_strs - returns an array of strings
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strs(list_t *head)
{
	list_t *node = head;
	size_t k = list_lght(head), j;
	char **str1;
	char *str;

	if (!head || !k)
		return (NULL);
	str1 = malloc(sizeof(char *) * (k + 1));
	if (!str1)
		return (NULL);
	for (k = 0; node; node = node->next, k++)
	{
		str = malloc(string_length(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < k; j++)
				free(str1[j]);
			free(str1);
			return (NULL);
		}

		str = string_copy(str, node->str);
		str1[k] = str;
	}
	str1[k] = NULL;
	return (str1);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t k = 0;

	while (h)
	{
		print_string(convert_num(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		print_string(h->str ? h->str : "(nil)");
		print_string("\n");
		h = h->next;
		h++;
	}
	return (k);
}

/**
 * node_st_with - returns starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_st_with(list_t *node, char *prefix, char c)
{
	char *w = NULL;

	while (node)
	{
		w = string_starts_with(node->str, prefix);
		if (w && ((c == -1) || (*w == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
size_t get_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
