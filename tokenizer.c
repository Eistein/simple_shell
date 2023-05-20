#include "shell.h"
/**
 * **s_string - split a string into words
 * @str: input
 * @d: a delimeter
 * Return: 0
 */
char **s_string(char *str, char *d)
{
	int l, a, b, c, n = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (l = 0; str[l] != '\0'; l++)
	if (!check_delim(str[l], d) && (check_delim(str[l + 1], d) || !str[l + 1]))
		n++;
	if (n == 0)
		return (NULL);
	s = malloc((1 + n) * sizeof(char *));
	if (!s)
		return (NULL);
	for (l = 0, a = 0; a < n; a++)
	{
		while (check_delim(str[l], d))
			l++;
		b = 0;
		while (!check_delim(str[l + b], d) && str[l + b])
			b++;
		s[a] = malloc((b + 1) * sizeof(char));
		if (!s[a])
		{
			for (b = 0; b < a; b++)
				free(s[b]);
			free(s);
			return (NULL);
		}
		for (c = 0; c < b; c++)
		s[a][c] = str[l++];
		s[a][c] = 0;
	}
	s[a] = NULL;
	return (s);
}
/**
 * **str_tow - separate string into words
 * @str: input
 * @d:  delimeter
 * Return: 0
 */
char **str_tow(char *str, char d)
{
	int l, a, b, c, n = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (l = 0; str[l] != '\0'; l++)
	if ((str[l] != d && str[l + 1] == d) ||
		(str[l] != d && !str[l + 1]) || str[l + 1] == d)
		n++;
	if (n == 0)
		return (NULL);
	s = malloc((1 + n) * sizeof(char *));
	if (!s)
		return (NULL);
	for (l = 0, a = 0; a < n; a++)
	{
		while (str[l] == d && str[l] != d)
			l++;
		b = 0;
		while (str[l + b] != d && str[l + b] && str[l + b] != d)
			b++;
		s[a] = malloc((b + 1) * sizeof(char));
		if (!s[a])
		{
			for (b = 0; b < a; b++)
			free(s[b]);
			free(s);
				return (NULL);
		}
		for (c = 0; c < b; c++)
		s[a][c] = str[l++];
		s[a][c] = 0;
	}
	s[a] = NULL;
	return (s);
}
