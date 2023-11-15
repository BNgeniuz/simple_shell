#include "shell.h"
/**
  *print_numbers - Prints numbers from 0 to 9.
  */

void print_numbers(void)
{
	char digit;

	digit = '0';
	while (digit <= '9')
	{
		write(1, &digit, 1);
		digit++;
	}
}

/**
  *main - Entry point of the program.
  *
  *Return: Always 0
  */
int main(void)
{
	print_numbers();
	return (0);
}
