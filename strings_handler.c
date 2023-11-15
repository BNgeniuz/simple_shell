#include "shell.h"

/**
 * _strcpy - cpying str
 * @destn: destination
 * @source: str source
 *
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

/**
 * _strcmp - lexicogarphic comparison of 2 str performance
 * @x1: input first str
 * @x2: input second str
 *
 * Return: neg val if x1 < x2, pos val if x1 > x2, 0 if x1 == x2
 */
int _strcmp(char *x1, char *x2)
{
	while (*x1 && *x2)
	{
		if (*x1 != *x2)
			return (*x1 - *x2);
		x1++;
		x2++;
	}
	if (*x1 == *x2)
		return (0);
	else
		return (*x1 < *x2 ? -1 : 1);
}

/**
 * starts_with - verifies if needle starts with hystack
 * @haystack: str search
 * @needle: substr to find
 *
 * Return: addr of next xter of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - linked 2 str
 * @destn: destination buffer
 * @source: the source buffer
 *
 * Return: ptr to dest buf
 */
char *_strcat(char *destn, char *source)
{
	char *sct = destn;

	while (*destn)
		destn++;
	while (*source)
		*destn++ = *source++;
	*destn = *source;
	return (sct);
}
