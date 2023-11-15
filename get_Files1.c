#include "shell.h"

/**
 * add_node - adds a node to the start of linked list
 * @head: ptr address to head node
 * @str: str field of node
 * @num: node index
 *
 * Return: 0 (size of list)
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *newhead;

	if (!head)
		return (NULL);
	newhead = malloc(sizeof(list_t));
	if (!newhead)
		return (NULL);
	_memset((void *)newhead, 0, sizeof(list_t));
	newhead->num = num;
	if (str)
	{
		newhead->str = _strdup(str);
		if (!newhead->str)
		{
			free(newhead);
			return (NULL);
		}
	}
	newhead->next = *head;
	*head = newhead;
	return (newhead);
}

/**
 * add_node_end - adds node to the list end
 * @head: ptr to head node
 * @str: str node fielded
 * @num: node index used by history
 *
 * Return: 0 (size of list)
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *newnode, *node;

	if (!head)
		return (NULL);

	node = *head;
	newnode = malloc(sizeof(list_t));
	if (!newnode)
		return (NULL);
	_memset((void *)newnode, 0, sizeof(list_t));
	newnode->num = num;
	if (str)
	{
		newnode->str = _strdup(str);
		if (!newnode->str)
		{
			free(newnode);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = newnode;
	}
	else
		*head = newnode;
	return (newnode);
}

/**
 * print_list_str - prints str element of a list_t linked list only
 * @h: ptr to first node
 *
 * Return: 0 (size of list)
 */
size_t print_list_str(const list_t *h)
{
	size_t l = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		l++;
	}
	return (l);
}

/**
 * delete_node_at_index - deletes index of a given node
 * return 1 on success, 0 on failure
 * @head: node addr of ptr
 * @index: delete index node
 *
 * Return: 0 (index node deletion)
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *old_node;
	unsigned int l = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (l == index)
		{
			old_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		l++;
		old_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all linked list node
 * @head_ptr: ptr head node
 *
 * Return: 0 (void)
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *nextnode, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		nextnode = node->next;
		free(node->str);
		free(node);
		node = nextnode;
	}
	*head_ptr = NULL;
}
