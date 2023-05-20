#include "shell.h"

/**
 * add_to - adds a node at start of the list
 * @head: address of pointer to head node
 * @str: string field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_to(list_t **head, const char *str, int num)
{
	list_t *new_h;

	if (!head)
		return (NULL);
	new_h = malloc(sizeof(list_t));
	if (!new_h)
		return (NULL);
	set_memo((void *)new_h, 0, sizeof(list_t));
	new_h->num = num;
	if (str)
	{
		new_h->str = string_duplicate(str);
		if (!new_h->str)
		{
			free(new_h);
			return (NULL);
		}
	}
	new_h->next = *head;
	*head = new_h;
	return (new_h);
}

/**
 * add_to_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_to_end(list_t **head, const char *str, int num)
{
	list_t *new_n, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_n = malloc(sizeof(list_t));
	if (!new_n)
		return (NULL);
	set_memo((void *)new_n, 0, sizeof(list_t));
	new_n->num = num;
	if (str)
	{
		new_n->str = string_duplicate(str);
		if (!new_n->str)
		{
			free(new_n);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_n;
	}
	else
		*head = new_n;
	return (new_n);
}

/**
 * print_str_l - prints str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_str_l(const list_t *h)
{
	size_t k = 0;

	while (h)
	{
		print_string(h->str ? h->str : "(nil)");
		print_string("\n");
		h = h->next;
		k++;
	}
	return (k);
}

/**
 * del_node_at - deletes node at given index
 * @head: address of pointer to first node
 * @ind: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int del_node_at(list_t **head, unsigned int ind)
{
	list_t *node, *prev_node;
	unsigned int k = 0;

	if (!head || !*head)
		return (0);

	if (!ind)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (k == ind)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		k++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_l - frees the given nodes.
 * @head_p: address of pointer to head node
 *
 * Return: void
 */
void free_l(list_t **head_p)
{
	list_t *node, *next_n, *head;

	if (!head_p || !*head_p)
		return;
	head = *head_p;
	node = head;
	while (node)
	{
		next_n = node->next;
		free(node->str);
		free(node);
		node = next_n;
	}
	*head_p = NULL;
}
