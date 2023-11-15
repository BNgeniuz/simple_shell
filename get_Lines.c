#include "shell.h"

/**
 * input_buf - prints buffer chain cmds
 * @info: par struct type
 * @buf: addr of buff
 * @length: addr of varaible length
 *
 * Return: 0 ( bytes read)
 */
ssize_t input_buf(info_t *info, char **buf, size_t *length)
{
	ssize_t k = 0;
	size_t length_q = 0;

	if (!*length) /* if buffer is empty, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		k = getline(buf, &length_q, stdin);
#else
		k = _getline(info, buf, &length_q);
#endif
		if (k > 0)
		{
			if ((*buf)[k - 1] == '\n')
			{
				(*buf)[k - 1] = '\0'; /* rm trailing newline */
				k--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is is cmd chain? */
			{
				*length = k;
				info->cmd_buf = buf;
			}
		}
	}
	return (k);
}

/**
 * get_input - line minus newline
 * @info: par struct type
 *
 * Return: 0 (bytes read)
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' cmd chain buff */
	static size_t l, g, length;
	ssize_t k = 0;
	char **buf_q = &(info->arg), *q;

	_putchar(BUF_FLUSH);
	k = input_buf(info, &buf, &length);
	if (k == -1) /* EOF */
		return (-1);
	if (length) /* we have cmds remain in chain buffer */
	{
		g = l; /* initialize new iterator to current buf pos */
		q = buf + l; /* get ptr for return */

		check_chain(info, buf, &g, l, length);
		while (g < length) /* iterate to semi colon ; or end */
		{
			if (is_chain(info, buf, &g))
				break;
			g++;
		}

		l = g + 1; /* increase past nulled ';'' */
		if (l >= length) /* reach buffer end? */
		{
			l = length = 0; /* reset positn n  len */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_q = q; /* pass ptr back to current cmd positn */
		return (_strlen(q)); /* return len of current cmd */
	}

	*buf_q = buf; /* else if not a chain, pass buff bck frm _getline() */
	return (k); /* return buff length frm _getline() */
}

/**
 * read_buf - prints buffer
 * @info: par struct type
 * @buf: buffer
 * @l: size
 *
 * Return: 0 (read buffer)
 */
ssize_t read_buf(info_t *info, char *buf, size_t *l)
{
	ssize_t k = 0;

	if (*l)
		return (0);
	k = read(info->readfd, buf, READ_BUF_SIZE);
	if (k >= 0)
		*l = k;
	return (k);
}

/**
 * _getline - gets d next line of input frm STDIN
 * @info: par struct type
 * @ptr: addr of ptr to buf, preallocated or NULL
 * @length: preallocated ptr size buf if not NULL
 *
 * Return: 0 (getline)
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t l, lenf;
	size_t c;
	ssize_t w = 0, x = 0;
	char *q = NULL, *new_q = NULL, *a;

	q = *ptr;
	if (q && length)
		x = *length;
	if (l == lenf)
		l = lenf = 0;

	w = read_buf(info, buf, &lenf);
	if (w == -1 || (w == 0 && lenf == 0))
		return (-1);

	a = _strchr(buf + l, '\n');
	c = a ? 1 + (unsigned int)(a - buf) : lenf;
	new_q = _realloc(q, x, x ? x + c : c + 1);
	if (!new_q) /* MALLOC FAILS! */
		return (q ? free(q), -1 : -1);

	if (x)
		_strncat(new_q, buf + l, c - l);
	else
		_strncpy(new_q, buf + l, c - l + 1);

	x += c - l;
	l = c;
	q = new_q;

	if (length)
		*length = x;
	*ptr = q;
	return (x);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: signal numb
 *
 * Return: 0 (void)
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
