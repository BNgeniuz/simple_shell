#include "shell.h"

/**
  * handle_builtin_commands - Handle all the builtins cmd
  * @arg: builtins cmd input
  * @numb_arg: Num of input
  * @input: input cmd
  * @env: get environ variables
  *
  * Return: 1 if succeed, 0 when fail
  */

int handle_builtin_commands(char **arg, int numb_arg, char *input, char **env)
{
	if (strcmp(arg[0], "exit") == 0)
	{
		return (shell_exit(arg, input));
	}
	else if (strcmp(arg[0], "cd") == 0)
	{
		handle_cd(arg, numb_arg);
		return (1);
	}
	else if (strcmp(arg[0], "env") == 0)
	{
		print_env(env);
		return (1);
	}

	return (0);
}


/**
  * execute_command - Exec the input buff
  * @input: buffer input
  * @argvv: arg arrays
  * @env: Environment inputs
  */

void execute_command(char *input, char *argvv[], char **env)
{
	char *argc[10];
	char *path, *shell_profile;
	int position, numb_arg;
	pid_t child_pid;

	shell_profile = argvv[0];
	numb_arg = tokenize_input(input, argc);

	if (numb_arg == 0)
		return;
	if (handle_builtin_commands(argc, numb_arg, input, env) == 1)
		return;
	path = get_file_path(argc[0]);

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error: creating failed");
		free(input);
		exit(1);
	}
	if (child_pid == 0)
	{
		if (execve(path, argc, NULL) == -1)
		{
			write(2, shell_profile, strlen(shell_profile));
			write(2, ": 1: ", 5);
			write(2, argc[0], strlen(argc[0]));
			write(2, ": not exist\n", 12);
			exit(127);
		}
	}
	else
		wait(&position);

	free(path);
}


/**
  * tokenize_input - read symbols to input strings
  * @input: input arg
  * @argc: array of strings
  *
  * Return: 1 when tokenized, 0 when fail
  */

int tokenize_input(char *input, char *argc[])
{
	int read;
	char *token;

	read = 0;
	token = strtok(input, " \n");

	while (token)
	{
		argc[read] = token;
		token = strtok(NULL, " \n");
		read++;
	}

	argc[read] = NULL;
	return (read);
}


/**
  * print_prompt - Print prompt to user input
  */

void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "BnEShell$ ", 9);
}

/**
  * read_input - functions for the user to read and input
  *
  * Return: 1 when the user is able to read input
  */

char *read_input(void)
{
	char *input_buff;
	size_t buffer_size;
	ssize_t Iread;

	input_buff = NULL;
	buffer_size = 0;
	Iread = getline(&input_buff, &buffer_size, stdin);

	if (Iread == -1)
	{
		free(input_buff);
		exit(0);
	}

	input_buff = handle_comment(input_buff);

	return (input_buff);
}
