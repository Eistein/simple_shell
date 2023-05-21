#include "shell.h"

/**
 * string_copy - copies a given string
 * @destin: the destination of the new string
 * @sour: the source to get the string
 *
 * Return: pointer to destination string
 */
char *string_copy(char *destin, char *sour)
{
	int k = 0;

	if (destin == sour || sour == 0)
		return (destin);
	while (sour[k])
	{
		destin[k] = sour[k];
		k++;
	}
	destin[k] = 0;
	return (destin);
}

/**
 * string_duplicate - duplicates a string
 * @p: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *string_duplicate(const char *p)
{
	int length = 0;
	char *result;

	if (p == NULL)
		return (NULL);
	while (*p++)
		length++;
	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);
	for (length++; length--;)
		result[length] = *--p;
	return (result);
}

/**
 * print_string - prints an input string
 *@ptr: the string to print
 *
 * Return: Nothing
 */
void print_string(char *ptr)
{
	int n = 0;

	if (!ptr)
		return;
	while (ptr[n] != '\0')
	{
		_putchar(ptr[n]);
		n++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar (char c)
{
	static int n;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(1, buffer, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buffer[n++] = c;
	return (1);
}
