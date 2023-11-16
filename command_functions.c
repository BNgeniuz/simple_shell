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


/**
 * my_cmd - check if a file is an executable cmd
 * return 1 if true, 0 otherwise
 * @info: info struct type
 * @path: file path
 *
 * Return: 0 (command path)
 */
int my_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - characters duplication
 * @pathstr: str path
 * @start: index input starting
 * @stop: index stopping
 *
 * Return: 0 (ptr to new buff)
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buff[1024];
	int l = 0, c = 0;

	for (c = 0, l = start; l < stop; l++)
		if (pathstr[l] != ':')
			buff[c++] = pathstr[l];
	buff[c] = 0;
	return (buff);
}

/**
 * find_path - finds str path command
 * @info: info struct type
 * @pathstr: str path
 * @cmd: command to find
 *
 * Return: 0 (full path of cmd if found or NULL)
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int l = 0, curr_ptr = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (my_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[l] || pathstr[l] == ':')
		{
			path = dup_chars(pathstr, curr_ptr, l);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (my_cmd(info, path))
				return (path);
			if (!pathstr[l])
				break;
			curr_ptr = l;
		}
		l++;
	}
	return (NULL);
}
