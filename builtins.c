#include "shell.h"

/**
  * shell_exit - Handles the exit status
  * @args: Arguments to the function
  * @input: Checks the status of exit
  *
  * Return: Status of exit, 1 if otherwise
  */

int shell_exit(char **args, char *input)
{
	char *position_str;
	int exit_position, l;

	if (args[1] != NULL)
	{
		exit_position = 0;
		position_str = args[1];

		for (l = 0; position_str[l] != '\0'; l++)
		{
			if (position_str[l] < '0' || position_str[l] > '9')
			{
				handle_exit(input, 2);
				return (1);
			}
			exit_position = exit_position * 10 + (position_str[l] - '0');
		}
		handle_exit(input, exit_position);
	}
	else
	{
		handle_exit(input, 127);
	}
	return (1);
}

/**
  * handle_cd - changing directory handling
  * @argc: an array input
  * @argv: the args vector
  */

void handle_cd(char **argc, int argv)
{
	const char *home_dir, *old_dir;

	home_dir = getenv("HOME");
	old_dir = getenv("PREVPWD");

	if (argv == 1 || strcmp(argc[1], "~") == 0)
	{
		if (!home_dir)
		{
			perror("Home environ must be set first");
			return;
		}
		if (chdir(home_dir) != 0)
			perror("cd");
	}
	else if (argv == 2 && strcmp(argc[1], "-") == 0)
	{
		if (!old_dir)
		{
			perror("PREVPWD environ must be set");
			return;
		}
		if (chdir(old_dir) != 0)
			perror("cd");
	}
	else
	{
		if (chdir(argc[1]) != 0)
			perror("cd");
	}
}


/**
  * print_env - pwd the current environ variables
  * @env: arg inputs
  */

void print_env(char **env)
{
	while (*env != NULL)
	{
		write(1, *env, strlen(*env));
		write(1, "\n", 1);
		env++;
	}
}


/**
  * handle_exit - exiting the shell code
  * @input: Input value
  * @exit_position: Exit the status code
  */

void handle_exit(char *input, int exit_position)
{
	free(input);
	exit(exit_position);
}
