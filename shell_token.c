#include "shell.h"

/**
 * **strtow - splits str into words
 * repeated delimiters are overlooked
 * @str: str input
 * @d: delimeter str
 *
 * Return: 0 (ptr to array of stri, or NULL when fails)
 */

char **strtow(char *str, char *d)
{
	int l, g, q, n, num_words = 0;
	char **x;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (l = 0; str[l] != '\0'; l++)
		if (!split_delim(str[l], d) && (split_delim(str[l + 1], d) || !str[l + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	x = malloc((1 + num_words) * sizeof(char *));
	if (!x)
		return (NULL);
	for (l = 0, g = 0; g < num_words; g++)
	{
		while (split_delim(str[l], d))
			l++;
		q = 0;
		while (!split_delim(str[l + q], d) && str[l + q])
			q++;
		x[g] = malloc((q + 1) * sizeof(char));
		if (!x[g])
		{
			for (q = 0; q < g; q++)
				free(x[q]);
			free(x);
			return (NULL);
		}
		for (n = 0; n < q; n++)
			x[g][n] = str[l++];
		x[g][n] = 0;
	}
	x[g] = NULL;
	return (x);
}

/**
 * **strtow2 - splits str into readable words
 * @str: str input
 * @d: delimeter
 * Return: 0 (ptr to array of str, or NULL when fails)
 */
char **strtow2(char *str, char d)
{
	int l, g, q, n, num_words = 0;
	char **x;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (l = 0; str[l] != '\0'; l++)
		if ((str[l] != d && str[l + 1] == d) ||
				    (str[l] != d && !str[l + 1]) || str[l + 1] == d)
			num_words++;
	if (num_words == 0)
		return (NULL);
	x = malloc((1 + num_words) * sizeof(char *));
	if (!x)
		return (NULL);
	for (l = 0, l = 0; g < num_words; g++)
	{
		while (str[l] == d && str[l] != d)
			l++;
		q = 0;
		while (str[l + q] != d && str[l + q] && str[l + q] != d)
			q++;
		x[g] = malloc((q + 1) * sizeof(char));
		if (!x[g])
		{
			for (q = 0; q < g; q++)
				free(x[q]);
			free(x);
			return (NULL);
		}
		for (n = 0; n < q; n++)
			x[g][n] = str[l++];
		x[g][n] = 0;
	}
	x[g] = NULL;
	return (x);
}
