#include "shell.h"

/**
 * _shellhistory - list history, one command by line
 * preceded with line numb, begins 0.
 * @info: Struct contain potential arg used to maintain prototype
 *
 *  Return: 0 (builtin history)
 */
int _shellhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * _shellalias - man alias
 * @info: Struct contain potential arg used to maintain valid prototype.
 *
 * Return: 0 (main builtin alias)
 */
int _shellalias(info_t *info)
{
	int l = 0;
	char *q = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (l = 1; info->argv[l]; l++)
	{
		q = _strchr(info->argv[l], '=');
		if (q)
			set_alias(info, info->argv[l]);
		else
			print_alias(node_starts_with(info->alias, info->argv[l], '='));
	}

	return (0);
}

/**
 * _shellcd - change dir. of the program
 * @info: Struct contain potential arg used to maintain
 * valid prototype
 *
 * Return: 0 (change dir)
 */
int _shellcd(info_t *info)
{
	char *x, *dir, buffer[1024];
	int curr_dir;

	x = getcwd(buffer, 1024);
	if (!x)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			curr_dir = /* TODO: what this contain? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			curr_dir = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(x);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		curr_dir = /* TODO: what this contain? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		curr_dir = chdir(info->argv[1]);
	if (curr_dir == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * unset_alias - sets str alias
 * @info: parameter struct
 * @str: str input
 *
 * Return: 0 (builtin alias)
 */
int unset_alias(info_t *info, char *str)
{
	char *q, x;
	int rtn;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	x = *q;
	*q = 0;
	rtn = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*q = x;
	return (rtn);
}



/**
 * _shellhelp - change curr dir of the process
 * @info: Struct contain potential arg used to maintain prototype
 *
 * Return: 0 (chnage dir builtin)
 */
int _shellhelp(info_t *info)
{
	char **ac_array;

	ac_array = info->argv;
	_puts("help call works fnxtn not yet implemented \n");
	if (0)
		_puts(*ac_array); /* temporal att_unused work */
	return (0);
}
