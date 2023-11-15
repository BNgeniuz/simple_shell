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



/**
 * get_history_file - prints history file
 * @info: par struct type
 *
 * Return: 0 (allocated str contan history file)
 */

char *get_history_file(info_t *info)
{
	char *buf_fer, *dir_tory;

	dir_tory = _getenv(info, "HOME=");
	if (!dir_tory)
		return (NULL);
	buf_fer = malloc(sizeof(char) * (_strlen(dir_tory) + _strlen(HIST_FILE) + 2));
	if (!buf_fer)
		return (NULL);
	buf_fer[0] = 0;
	_strcpy(buf_fer, dir_tory);
	_strcat(buf_fer, "/");
	_strcat(buf_fer, HIST_FILE);
	return (buf_fer);
}

/**
 * write_history - write file, or merge to an existing file
 * @info: the par struct type
 *
 * Return: 0 (history file)
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *file_name = get_history_file(info);
	list_t *node = NULL;

	if (!file_name)
		return (-1);

	fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - writes history frm file
 * @info: par struct type
 *
 * Return: 0 (read history)
 */
int read_history(info_t *info)
{
	int l, end = 0, line_count = 0;
	ssize_t fd, rdlength, fsize = 0;
	struct stat st;
	char *buffer = NULL, *file_name = get_history_file(info);

	if (!file_name)
		return (0);

	fd = open(file_name, O_RDONLY);
	free(file_name);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlength = read(fd, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlength <= 0)
		return (free(buffer), 0);
	close(fd);
	for (l = 0; l < fsize; l++)
		if (buffer[l] == '\n')
		{
			buffer[l] = 0;
			build_history_list(info, buffer + end, line_count++);
			end = l + 1;
		}
	if (end != l)
		build_history_list(info, buffer + end, line_count++);
	free(buffer);
	info->histcount = line_count;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - enter entry to a history file
 * @info: struct contain valid arg used to maintain
 * @buf: buffer
 * @linecount: history linecount, histcount
 *
 * Return: 0 (build history file)
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - re-number the history file list after changes
 * @info: struct contain valid arg used to maintain
 *
 * Return: 0 (new histcount)
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int l = 0;

	while (node)
	{
		node->num = l++;
		node = node->next;
	}
	return (info->histcount = l);
}

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
