#include "shell.h"

/**
  * main - shell barsh program
  * @argc: the argument counter
  * @argv: vector of array for input
  * @environ: variables to declare for envirment
  *
  * Return: Always success
  */

int main(int argc, char *argv[], char **environ)
{
	char *buffer_input;
	(void)argc;

	while (1)
	{
		print_prompt();
		buffer_input = read_input();
		execute_command(buffer_input, argv, environ);
		free(buffer_input);
	}

	return (0);
}
