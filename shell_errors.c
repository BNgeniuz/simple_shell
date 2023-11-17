#include "shell.h"

/**
 * _erratoi - converts an ASCII str to an integer
 * @c: the str to convert
 *By: Edmund and Bruce
 * Return: 0 (ASCII to an integer)
 */
int _erratoi(char *c)
{
	int l = 0;
	unsigned long int output = 0;

	if (*c == '+')
		c++;  /* TODO: why make main return 255? */
	for (l = 0;  c[l] != '\0'; l++)
	{
		if (c[l] >= '0' && c[l] <= '9')
		{
			output *= 10;
			output += (c[l] - '0');
			if (output > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (output);
}

/**
 * print_error - prints error msg
 * @info: input info struct
 * @erstr: str contain specific error type
 *
 * Return: 0 (error msg)
 */
void print_error(info_t *info, char *erstr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(erstr);
}

/**
 * print_d - fnxtn prints a dec. (integer) numb - base 10
 * @input: num- base input
 * @fd: file discriptor
 *
 * Return: 0 (num-base error)
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int l, read = 0;
	unsigned int _abs_, curr_ent;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		read++;
	}
	else
		_abs_ = input;
	curr_ent = _abs_;
	for (l = 1000000000; l > 1; l /= 10)
	{
		if (_abs_ / l)
		{
			__putchar('0' + curr_ent / l);
			read++;
		}
		curr_ent %= l;
	}
	__putchar('0' + curr_ent);
	read++;

	return (read);
}

/**
 * convert_number - convert fnxtn, clone of itoa
 * @num: numb input
 * @base: base input
 * @flags: arg flags
 *
 * Return: 0 (num convertion)
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buff[50];
	char str = 0;
	char *ptr;
	unsigned long x = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		x = -num;
		str = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buff[49];
	*ptr = '\0';

	do	{
		*--ptr = array[x % base];
		x /= base;
	} while (x != 0);

	if (str)
		*--ptr = str;
	return (ptr);
}
