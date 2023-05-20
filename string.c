#include "shell.h"
/**
 * string_length - returns the length of a string
 * @m: the string whose length to check
 *
 * Return: integer length of string
 */
int string_length(char *m)
{
	int count = 0;

	if (!m)
		return (0);
	while (*m++)
		count++;
	return (count);
}
/**
 * string_compare - compares two strings
 * @str1: the first string
 * @str2: the second string
 *
 * Return: negative if str1 < str2, positive if str1 > str2, otherwise  0
 */
int string_compare(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}
/**
 * string_starts_with - checks if needle starts with haystack
 * @haystack: string to be checked
 * @needle: the substring to search
 *
 * Return: address of next character of haystack or NULL
 */
char *string_starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
/**
 * string_concatenate - concatenates two strings
 * @mod: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *string_concatenate(char *mod, char *src)
{
	char *ganza = mod;

	while (*mod)
		mod++;
	while (*src)
		*mod++ = *src++;
	*mod = *src;
	return (ganza);
}
