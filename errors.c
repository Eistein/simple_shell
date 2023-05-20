#include "shell.h"
/**
 *_error - prints an input
 * @str: a string to print
 *
 * Return: nothing
 */
void _error(char *str)
{
	int k = 0;

	if (!str)
		return;
	while (str[k] != '\0')
	{
		_error_char(str[k]);
		k++;
	}
}
/**
 * _error_char - writes the character c
 * @n: a character to be printed
 *
 * Return: 0
 * On error, -1 is returned, and errno is the set appropriately.
 */
int _error_char(char n)
{
	static int k;
	static char buf[WRITE_BUF_SIZE];

	if (n == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(2, buf, k);
		k = 0;
	}
	if (n != BUF_FLUSH)
		buf[k++] = n;
	return (1);
}
/**
 * _filedescriptor - writes a character c to given file
 * @n: a character
 * @file: a file descriptor
 *
 * Return: 0
 * On error, -1 is returned, and errno is set appropriately.
 */
int _filedescriptor(char n, int file)
{
	static int k;
	static char buf[WRITE_BUF_SIZE];

	if (n == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(file, buf, k);
		l = 0;
	}
	if (n != BUF_FLUSH)
		buf[k++] = n;
	return (1);
}
/**
 *_print_to_fd - prints an input
 * @str: the string to be printed
 * @file: the filedescriptor to write to
 *
 * Return: 0
 */
int _print_to_fd(char *str, int file)
{
	int l = 0;

	if (!str)
		return (0);
	while (*str)
	{
		l +=  _filedescriptor(*str++, file);
	}
	return (l);
}
