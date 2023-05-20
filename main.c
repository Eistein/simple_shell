#include "shell.h"
/**
 * main - entry point
 * @c: arg count
 * @v: arg vector
 *
 * Return: 0 on success, otherwise 1
 */
int main(int c, char **v)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));
	if (c == 2)
	{
		fd = open(v[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_error(v[0]);
				_error(": 0: Can't open ");
				_error(v[1]);
				_error_char('\n');
				_error_char(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	pop_env_list(info);
	read_hi(info);
	hsh(info, v);
	return (EXIT_SUCCESS);
}
