#include "shell.h"

/**
  * tag_comment - code to handles the '#'
  * @input: value to be inputed
  * By : Edmund and Bruce
  * Return: Always success
  */

char *tag_comment(char *input)
{
	char *comment_harsh;

	comment_harsh = strstr(input, " #");

	if (comment_harsh)
	{
		*comment_harsh = '\0';
	}

	return (input);
}

#include "shell.h"

/**
 * *_strncpy - str copying
 * @dest: destination of strings to copy
 * @src: str source
 * @n: the amount of str input
 *
 * Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int l, g;
	char *x = dest;

	l = 0;
	while (src[l] != '\0' && l < n - 1)
	{
		dest[l] = src[l];
		l++;
	}
	if (l < n)
	{
		g = l;
		while (g < n)
		{
			dest[g] = '\0';
			g++;
		}
	}
	return (x);
}

/**
 * *_strncat - concatenates 2 strs
 * @dest: str first input
 * @src: str second input
 * @n: number of bytes to be use
 *
 * Return: 0 (link string)
 */
char *_strncat(char *dest, char *src, int n)
{
	int l, g;
	char *x = dest;

	l = 0;
	g = 0;
	while (dest[l] != '\0')
		l++;
	while (src[g] != '\0' && g < n)
	{
		dest[l] = src[g];
		l++;
		g++;
	}
	if (g < n)
		dest[l] = '\0';
	return (x);
}

/**
 * *_strchr - find a xter in a str
 * @x: str arg parsed
 * @a: xter to find
 *
 * Return: 0 (locating str)
 */
char *_strchr(char *x, char a)
{
	do {
		if (*x == a)
			return (x);
	} while (*x++ != '\0');

	return (NULL);
}
