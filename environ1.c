#include "shell.h"

/**
 * get_environ - returns str array cpy of the environ
 * @info: struct contain potential arg used to maintain valid prototype
 *
 * Return: 0 (get environ)
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove environ var
 * @info: struct contain valid arg used to maintain prototype
 * @var: str envirn var input
 *
 * Return: 0 (unset environ)
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t l = 0;
	char *q;

	if (!node || !var)
		return (0);

	while (node)
	{
		q = starts_with(node->str, var);
		if (q && *q == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), l);
			l = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		l++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Init new environ var or edit an existing one
 * @info: struct contain valid arg used to maintain prototype
 * @var: the string env var property
 * @value: str env var value
 *  Return: 0 (set environ)
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *q;

	if (!var || !value)
		return (0);

	buffer = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, var);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = info->env;
	while (node)
	{
		q = starts_with(node->str, var);
		if (q && *q == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}
