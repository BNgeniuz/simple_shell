#include "shell.h"

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
