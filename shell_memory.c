#include "shell.h"

/**
 * bfree - free ptr n NULLs d addr
 * @pointer: addr of ptr to free
 *
 *By:Edmund and Bruce
 * Return: 0 (freed)
 */
int bfree(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}
