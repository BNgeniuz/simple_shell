#include "shell.h"

/**
 * hsh - main shell loop used.
 * @info: parameter & return info for struct type
 * @ag: arg vector from main hsh
 *
 * Return: 0 (shell loop)
 */
int hsh(info_t *info, char **ag)
{
	ssize_t w = 0;
	int builtin_ret = 0;

	while (w != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		w = get_input(info);
		if (w != -1)
		{
			set_info(info, ag);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - this finds builtin cmd
 * @info: the parameter & return infor structure.
 * Return: -1 if the builtin is not found,
 *	0 if the builtin executed is successfully,
 *	1 if the builtin is found but not successful,
 *	2 if the builtin signals exit().
 */
int find_builtin(info_t *info)
{
	int l, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _shellexit},
		{"env", _shellenv},
		{"help", _shellhelp},
		{"history", _shellhistory},
		{"setenv", _shellsetenv},
		{"unsetenv", _shellunsetenv},
		{"cd", _shellcd},
		{"alias", _shellalias},
		{NULL, NULL}
	};

	for (l = 0; builtintbl[l].type; l++)
		if (_strcmp(info->argv[0], builtintbl[l].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[l].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - this finds a cmd path
 * @info: par & return info struct type
 * Return: void or nil.
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int l, c;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (l = 0, c = 0; info->arg[l]; l++)
		if (!is_delim(info->arg[l], " \t\n"))
			c++;
	if (!c)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && my_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks an executed thread to run the command
 * @info: par & return info struct type
 * Return: 0 (fork)
 */
void fork_cmd(info_t *info)
{
	pid_t child_pld;

	child_pld = fork();
	if (child_pld == -1)
	{
		/* TODO: PUTS ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pld == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUTS ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

