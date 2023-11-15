#include "shell.h"

/**
 * _myenv - prints curr environ
 * @info: Struct contain potential arg used to maintain valid prototype.
 *
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - inputs environ variable value
 * @info: Struct contain potential arg used to maintain valid prototype
 * @name: environ name
 *
 * Return: 0 (environment)
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *q;

	while (node)
	{
		q = starts_with(node->str, name);
		if (q && *q)
			return (q);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - new environ var init or modify an existing one
 * @info: Struct containi potential arg used to maintain valid prototype
 *
 *  Return: 0 (environment)
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - delete environ var
 * @info: Struct contain potential arg used to maintain validprototype
 *
 * Return: 0 (environ)
 */
int _myunsetenv(info_t *info)
{
	int l;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (l = 1; l <= info->argc; l++)
		_unsetenv(info, info->argv[l]);

	return (0);
}

/**
 * populate_env_list - duplicate env linked list
 * @info: Struct contain potential arg used to maintain prototype
 *
 * Return: 0 (environ)
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t l;

	for (l = 0; environ[l]; l++)
		add_node_end(&node, environ[l], 0);
	info->env = node;
	return (0);
}
