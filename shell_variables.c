#include "shell.h"

/**
 * my_chain - check if curr char in buffer is delimeter of chain
 * @info: par struct type
 * @buf: char buffer
 * @q: addr of curr positn in buf
 *
 *By: Edmund and Bruce
 * Return: 0 (delimeter chain)
 */
int my_chain(info_t *info, char *buf, size_t *q)
{
	size_t g = *q;

	if (buf[g] == '|' && buf[g + 1] == '|')
	{
		buf[g] = 0;
		g++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[g] == '&' && buf[g + 1] == '&')
	{
		buf[g] = 0;
		g++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[g] == ';') /* found this cmd end */
	{
		buf[g] = 0; /* semicolon replaced with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*q = g;
	return (1);
}

/**
 * check_chain - checks continue chains based on last status
 * @info: par struct type
 * @buf: xter buffer
 * @q: addr of curr positn in buf
 * @l: input point in buf
 * @length: length of buf
 *
 * Return: 0 (void)
 */
void check_chain(info_t *info, char *buf, size_t *q, size_t l, size_t length)
{
	size_t g = *q;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[l] = 0;
			g = length;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[l] = 0;
			g = length;
		}
	}

	*q = g;
}

/**
 * replace_alias - replaced aliase in tokenized str
 * @info: par struct type
 *
 * Return: 0 (alaise var)
 */
int replace_alias(info_t *info)
{
	int l;
	list_t *node;
	char *q;

	for (l = 0; l < 10; l++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		q = _strchr(node->str, '=');
		if (!q)
			return (0);
		q = _strdup(q + 1);
		if (!q)
			return (0);
		info->argv[0] = q;
	}
	return (1);
}

/**
 * replace_vars - replaces variables in tokenized str
 * @info: par struct type
 *
 * Return: 0 (replace vars)
 */
int replace_vars(info_t *info)
{
	int l = 0;
	list_t *node;

	for (l = 0; info->argv[l]; l++)
	{
		if (info->argv[l][0] != '$' || !info->argv[l][1])
			continue;

		if (!_strcmp(info->argv[l], "$?"))
		{
			replace_string(&(info->argv[l]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[l], "$$"))
		{
			replace_string(&(info->argv[l]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[l][1], '=');
		if (node)
		{
			replace_string(&(info->argv[l]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[l], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replac str
 * @old: addr of an existing str
 * @new: new str
 *
 * Return: 0 (replace old with new)
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
