#include "shell.h"

/**
 * list_len - determines linked list length
 * @h: first node ptr input
 *
 * Return: 0 (size of list)
 */
size_t list_len(const list_t *h)
{
	size_t l = 0;

	while (h)
	{
		h = h->next;
		l++;
	}
	return (l);
}

/**
 * list_to_strings - ret array of strs of the list->str
 * @head: first node ptr input
 *
 * Return: 0 (array of strs)
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t l = list_len(head), g;
	char **strs;
	char *str;

	if (!head || !l)
		return (NULL);
	strs = malloc(sizeof(char *) * (l + 1));
	if (!strs)
		return (NULL);
	for (l = 0; node; node = node->next, l++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (g = 0; g < l; g++)
				free(strs[g]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[l] = str;
	}
	strs[l] = NULL;
	return (strs);
}

/**
 * print_list - prints list_t linked list elements
 * @h: first node ptr input
 *
 * Return: 0 (size of list)
 */
size_t print_list(const list_t *h)
{
	size_t l = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		l++;
	}
	return (l);
}

/**
 * node_starts_with - ret string starts with node prefix
 * @node: ptr list head input
 * @prefix: str input
 * @b: nxt xter after prefix to input
 *
 * Return: 0 (match node or null)
 */
list_t *node_starts_with(list_t *node, char *prefix, char b)
{
	char *q = NULL;

	while (node)
	{
		q = starts_with(node->str, prefix);
		if (q && ((b == -1) || (*q == b)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - get node index
 * @head: ptr list head input
 * @node: ptr node
 *
 * Return: 0 (index of node or -1)
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t l = 0;

	while (head)
	{
		if (head == node)
			return (l);
		head = head->next;
		l++;
	}
	return (-1);
}
