#include "shell.h"

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
