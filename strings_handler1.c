#include "shell.h"

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
