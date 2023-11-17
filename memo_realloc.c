#include "shell.h"

/**
 * _memset - fill memo with a byte (byte is contant)
 * @x: memory area to be fill
 * @d: byte to fill *x with
 * @m: amount of bytes to be fill
 *
 * Return: (x) ptr to memory area x
 */
char *_memset(char *x, char d, unsigned int m)
{
	unsigned int l;

	for (l = 0; l < m; l++)
		x[l] = d;
	return (x);
}

/**
 * ffree - frees str of strings
 * @qq: str of strings
 */
void ffree(char **qq)
{
	char **z = qq;

	if (!qq)
		return;
	while (*qq)
		free(*qq++);
	free(z);
}

/**
 * _realloc - memory block reallocations
 * @ptr: input malloc'ated block
 * @old_memsize: old byte block size
 * @new_memsize: new byte block size
 *
 * Return: 0 (newmem to oldmem)
 */
void *_realloc(void *ptr, unsigned int old_memsize, unsigned int new_memsize)
{
	char *q;

	if (!ptr)
		return (malloc(new_memsize));
	if (!new_memsize)
		return (free(ptr), NULL);
	if (new_memsize == old_memsize)
		return (ptr);

	q = malloc(new_memsize);
	if (!q)
		return (NULL);

	old_memsize = old_memsize < new_memsize ? old_memsize : new_memsize;
	while (old_memsize--)
		q[old_memsize] = ((char *)ptr)[old_memsize];
	free(ptr);
	return (q);
}
