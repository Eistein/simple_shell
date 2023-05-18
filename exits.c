#include "shell.h"

/**
 **strn_copy - copies a given string
 *@destin: the destination of string
 *@sour: the source string
 *@n: the amount of characters to copy
 *Return: the concatenated string
 */
char *strn_copy(char *destin, char *sour, int n)
{
	int k, j;
	char *s = destin;

	k = 0;
	while (sour[k] != '\0' && k < n - 1)
	{
		destin[k] = sour[k];
		k++;
	}
	if (k < n)
	{
		j = k;
		while (j < n)
		{
			destin[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **strn_concat - concatenates two strings
 *@destin: destinated string
 *@sour: second string
 *@n: amount of bytes to be used
 *Return: the concatenated string
 */
char *strn_concat(char *destin, char *sour, int n)
{
	int k, j;
	char *s = destin;

	k = 0;
	j = 0;
	while (destin[k] != '\0')
	k++;
	while (sour[j] != '\0' && j < n)
	{
		destin[k] = sour[j];
		k++;
		j++;
	}
	if (j < n)
		destin[k] = '\0';
	return (s);
}

/**
 **str_character - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to be located
 *Return: (s) a pointer to the memory area s
 */
char *str_character(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
