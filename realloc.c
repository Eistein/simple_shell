#include "shell.h"

/**
 * set_memo - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @b: the byte to fill
 * @amou: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *set_memo(char *s, char b, unsigned int amou)
{
	unsigned int k;

	for (k = 0; k < n; k++)
		s[k] = b;
	return (s);
}

/**
 * free_str - frees a string of strings
 * @ss: string of strings
 */
void free_str(char **ss)
{
	char **a = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(a);
}

/**
 * re_alloc - reallocates a block of memory
 * @ptr: pointer to previous mallocated block
 * @old_s: size of previous block
 * @new_s: size of new block
 *
 * Return: pointer to old block.
 */
void *re_alloc(void *ptr, unsigned int old_s, unsigned int new_s)
{
	char *p;

	if (!ptr)
		return (malloc(new_s));
	if (!new_s)
		return (free(ptr), NULL);
	if (new_s == old_s)
		return (ptr);

	p = malloc(new_s);
	if (!p)
		return (NULL);

	old_s = old_s < new_s ? old_s : new_s;
	while (old_s--)
		p[old_s] = ((char *)ptr)[old_s];
	free(ptr);
	return (p);
}
