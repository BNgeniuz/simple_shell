#include "shell.h"

/**
 * print_alias - prints str alias
 * @node: the alias node
 *
 *By: Edmund and Bruce
 * Return: 0 (builtin alias prints)
 */
int print_alias(list_t *node)
{
	char *q = NULL, *z = NULL;

	if (node)
	{
		q = _strchr(node->str, '=');
		for (z = node->str; z <= q; z++)
		_putchar(*z);
		_putchar('\'');
		_puts(q + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * set_alias - sets str alias
 * @info: parameter struct
 * @str: str input
 *
 * Return: 0 (builtin alias set)
 */
int set_alias(info_t *info, char *str)
{
	char *q;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (set_alias(info, str));

	set_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * _shellexit - quits shell
 * @info: Struct defining potential args sed to maintain
 * valid prototype exits with a given exit status
 * (0) if info.argv[0] != "exit"
 *
 * Return: 0 (shell exits)
 */
int _shellexit(info_t *info)
{
	int quits;

	if (info->argv[1]) /* If exit arguement */
	{
		quits = _erratoi(info->argv[1]);
		if (quits == -1)
		{
			info->status = 2;
			print_error(info, "Illegal num: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
