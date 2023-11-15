#include "shell.h"

/**
  * handle_builtin_commands - Handle all the builtins cmd
  * @arg: builtins cmd input
  * @numb_arg: Num of input
  * @input: input cmd
  * @env: get environ variables
  *
  *By: Edmund and Bruce
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
	path = get_files_path(argc[0]);

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
		if (!is_delim(str[l], d) && (is_delim(str[l + 1], d) || !str[l + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	x = malloc((1 + num_words) * sizeof(char *));
	if (!x)
		return (NULL);
	for (l = 0, g = 0; g < num_words; g++)
	{
		while (is_delim(str[l], d))
			l++;
		q = 0;
		while (!is_delim(str[l + q], d) && str[l + q])
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

	input_buff = tag_comment(input_buff);

	return (input_buff);
}

#include "shell.h"

/**
 * my cmd - check if a file is an executable cmd
 * return 1 if true, 0 otherwise
 * @info: info struct type
 * @path: file path
 *
 * Return: 0 (command path)
 */
int my cmd(info_t *info, char *path)
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
		if (my cmd(info, cmd))
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
			if (my cmd(info, path))
				return (path);
			if (!pathstr[l])
				break;
			curr_ptr = l;
		}
		l++;
	}
	return (NULL);
}
