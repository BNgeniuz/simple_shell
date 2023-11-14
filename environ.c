#include "shell.h"

/**
  *print_env - Print the current environment
  */
void print_env(void)
{
	extern char **environ;
	int i = 0;

	while (environ[i] != NULL)
	{
		write(1, environ[i], strlen(environ[i]));
		write(1, "\n", 1);
		i++;
	}
}

/**
  *main - Entry point of the program
  *
  *Return: Always 0
  */
int main(void)
{
	char *input = NULL;
	size_t bufsize = 0;

	while (1)
	{
		write(1, "$", 2);
		input = getline(&input, $bufsize, stdin);
		return (input);
	}
	retrun (0);
}
