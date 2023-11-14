#include "shell.h"

/**
  * tag_comment - code to handles the '#'
  * @input: value to be inputed
  * By : Edmund and Bruce
  * Return: Always success
  */

char *tag_comment(char *input)
{
	char *comment_harsh;

	comment_harsh = strstr(input, " #");

	if (comment_harsh)
	{
		*comment_harsh = '\0';
	}

	return (input);
}
