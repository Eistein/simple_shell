#include "shell.h"
/**
 * string_to_i - converts string to integer
 * @s: the string to convert
 * Return: 0 if no numbers, converted number otherwise
 *       -1 on error
 */
int string_to_i(char *s)
{
	int k = 0;
	unsigned long int relt = 0;

	if (*s == '+')
		s++;
	for (k = 0;  s[k] != '\0'; k++)
	{
		if (s[k] >= '0' && s[k] <= '9')
		{
			relt *= 10;
			relt += (s[k] - '0');
			if (relt > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (relt);
}
/**
 * display_error - prints an error message
 * @info: the parameter & return info struct
 * @str3: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void display_error(info_t *info, char *str3)
{
	_error(info->fname);
	_error(": ");
	p_decimal(info->line_count, STDERR_FILENO);
	_error(": ");
	_error(info->argv[0]);
	_error(": ");
	_error(str3);
}
/**
 * p_decimal - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fa: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int p_decimal(int input, int fa)
{
	int (*__putchar)(char) = _putchar;
	int k, ct = 0;
	unsigned int _abs_, now;

	if (fa == STDERR_FILENO)
		__putchar = _error_char;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		ct++;
	}
	else
	{
		_abs_ = input;
		now = _abs_;
	}
	for (k = 1000000000; k > 1; k /= 10)
	{
		if (_abs_ / k)
		{
			__putchar('0' + now / k);
			ct++;
		}
		now %= k;
	}
	__putchar('0' + now);
	ct++;
	return (ct);
}
/**
 * convert_num - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_num(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *str;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	str = &buffer[49];
	*str = '\0';
	do	{
		*--str = array[n % base];
		n /= base;
	} while (n != 0);
	if (sign)
		*--str = sign;
	return (str);
}
/**
 * rm_comment - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void rm_comment(char *buf)
{
	int k;

	for (k = 0; buf[k] != '\0'; k++)
		if (buf[k] == '#' && (!k || buf[k - 1] == ' '))
		{
			buf[k] = '\0';
			break;
		}
}
