#include "shell.h"
/**
 * f_pointer - free pointer and NULLs the address
 * @n: address of the pointer
 *
 * Return: 0 if not otherwise 1.
 */
int f_pointer(void **n)
{
	if (n && *n)
	{
		free(*n);
		*n = NULL;
		return (1);
	}
	return (0);
}
