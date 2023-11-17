#include "shell.h"

/**
 * _strcpy - cpying str
 * @destn: destination
 * @source: str source
 *
 *By: Edmund and Bruce
 * Return: pointer to destination
 */
char *_strcpy(char *destn, char *source)
{
	int l = 0;

	if (destn == source || source == 0)
		return (destn);
	while (source[l])
	{
		destn[l] = source[l];
		l++;
	}
	destn[l] = 0;
	return (destn);
}

/**
 * _strdup - str duplication
 * @str: str to duplicate
 *
 * Return: ptr to duplicated str
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *sdup;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	sdup = malloc(sizeof(char) * (len + 1));
	if (!sdup)
		return (NULL);
	for (len++; len--;)
		sdup[len] = *--str;
	return (sdup);
}

/**
 * _puts - print an input string
 * @str: str to prints
 *
 * Return: 0 (put)
 */
void _puts(char *str)
{
	int l = 0;

	if (!str)
		return;
	while (str[l] != '\0')
	{
		_putchar(str[l]);
		l++;
	}
}

/**
 * _putchar - print xter c to stdout, return 1 on successo
 * on error, -1 is returned, and errno is set appropriately
 * @c: xter to print
 *
 * Return: 0 (putchar)
 */
int _putchar(char c)
{
	static int l;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || l >= WRITE_BUF_SIZE)
	{
		write(1, buf, l);
		l = 0;
	}
	if (c != BUF_FLUSH)
		buf[l++] = c;
	return (1);
}

/**
 * _strlen - returns len of a str
 * @x: str len to check
 *
 * Return: 0 (integer len of str)
 */
int _strlen(char *x)
{
	int l = 0;

	if (!x)
		return (0);

	while (*x++)
		l++;
	return (l);
}
