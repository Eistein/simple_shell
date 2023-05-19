#include "shell.h"
/**
 * _inbuf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t _inbuf(info_t *info, char **buf, size_t *len)
{
	ssize_t m = 0;
	size_t len_o = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sig_int_Hler);
#if USE_GETLINE
		m = getline(buf, &len_o, stdin);
#else
		m = tk_line(info, buf, &len_o);
#endif
		if (m > 0)
		{
			if ((*buf)[m - 1] == '\n')
			{
				(*buf)[m - 1] = '\0';
				m--;
			}
			info->linecount_flag = 1;
			rm_comment(*buf);
			build_hi_list(info, *buf, info->histcount++);
		}
	}
	return (m);
}
/**
 * _getput - gets a line except the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t _getput(info_t *info)
{
	static char *buf;
	static size_t k, l, len;
	ssize_t m = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	m = _inbuf(info, &buf, &len);
	if (m == -1)
		return (-1);
	if (len)
	{
		l = k;
		p = buf + k;
		_testch(info, buf, &l, k, len);
		while (l < len)
		{
			if (is_delm(info, buf, &l))
				break;
			l++;
		}
		k = l + 1;
		if (k >= len)
		{
			k = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*buf_p = p;
		return (string_length(p));
	}
	*buf_p = buf;
	return (m);
}
/**
 * _rdbuf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @k: size
 *
 * Return: m if it is true otherwise 0
 */
ssize_t _rdbuf(info_t *info, char *buf, size_t *k)
{
	ssize_t m = 0;

	if (*k)
		return (0);
	m = read(info->readfd, buf, READ_BUF_SIZE);
	if (m >= 0)
		*k = m;
	return (m);
}
/**
 * tk_line - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int tk_line(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t d, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;
	p = *ptr;
	if (p && length)
		s = *length;
	if (d == len)
		d = len = 0;
	r = _rdbuf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = str_character(buf + d, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = re_alloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);
	if (s)
		strn_concat(new_p, buf + d, k - d);
	else
		strn_copy(new_p, buf + d, k - d + 1);
	s += k - d;
	d = k;
	p = new_p;
	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
/**
 * sig_int_Hler - blocks ctrl-C
 * @sig_n: the signal number
 *
 * Return: void
 */
void sig_int_Hler(__attribute__((unused))int sig_n)
{
	print_string("\n");
	print_string("$ ");
	_putchar(BUF_FLUSH);
}
