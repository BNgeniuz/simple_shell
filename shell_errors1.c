#include "shell.h"

/**
 * remove_comments - fnxtn replace first inst of '#' with '\0'
 * @buf: addr of the str to edit
 *
 * Return: 0 (comment reove)
 */
void remove_comments(char *buf)
{
	int l;

	for (l = 0; buf[l] != '\0'; l++)
		if (buf[l] == '#' && (!l || buf[l - 1] == ' '))
		{
			buf[l] = '\0';
			break;
		}
}

/**
 * _eputs - input str
 * @str: str to be inputed
 *
 * Return: 0 (error eputs)
 */
void _eputs(char *str)
{
	int l = 0;

	if (!str)
		return;
	while (str[l] != '\0')
	{
		_eputchar(str[l]);
		l++;
	}
}

/**
 * _eputchar - prints the xter x to std error
 * @x: str xter to input
 *
 * Return: 0 (error eputchar)
 */
int _eputchar(char x)
{
	static int l;
	static char buf[WRITE_BUF_SIZE];

	if (x == BUF_FLUSH || l >= WRITE_BUF_SIZE)
	{
		write(2, buf, l);
		l = 0;
	}
	if (x != BUF_FLUSH)
		buf[l++] = x;
	return (1);
}

/**
 * _putfd - prints xter x to a given file discriptor, return
 * -1 on error and errno is set appropr.
 *
 * @x: str xter to input
 * @fd: file descriptor
 *
 * Return: 0 (error on file discriptor)
 */
int _putfd(char x, int fd)
{
	static int l;
	static char buf[WRITE_BUF_SIZE];

	if (x == BUF_FLUSH || l >= WRITE_BUF_SIZE)
	{
		write(fd, buf, l);
		l = 0;
	}
	if (x != BUF_FLUSH)
		buf[l++] = x;
	return (1);
}

/**
 * _putsfd - prints an input str for file discriptor
 * @str: str input
 * @fd: file discriptor
 *
 * Return: 0 (error on putfd)
 */
int _putsfd(char *str, int fd)
{
	int l = 0;

	if (!str)
		return (0);
	while (*str)
	{
		l += _putfd(*str++, fd);
	}
	return (l);
}
