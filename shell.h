#ifndef SHELL_H
#define SHELL_H

/**
 * Header File - shell.h
 *
 * Authors: Godwin Bruce - Edmund Boateng
 * Cohort: 19
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
#include <limits.h>
#include <signal.h>
#include <fcntl.h>

/* handle read or write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* handle command chains */
#define CMD_NORM 0
#define CMD_OR	 1
#define CMD_AND	 2
#define CMD_CHAIN 3

/* handle convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* handle system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;


	int (*func)(info_t *);
} builtin_table;


/* handle_shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* handle_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* handle_loophsh.c */
int loophsh(char **);

/* handle_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* handle_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* handle_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char c);

/* handle_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* handle_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* handle_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* handle_memory.c */
int bfree(void **);

/* handle_atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* handle_errors1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* handle_builtin.c */
int _shellexit(info_t *);
int _shellcd(info_t *);
int _shellhelp(info_t *);

/* handle_builtin1.c */
int _shellhistory(info_t *);
int _shellalias(info_t *);

/* handle_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* handle_getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* handle_environ.c */
char *_getenv(info_t *, const char *);
int _shellenv(info_t *);
int _shellsetenv(info_t *);
int _shellunsetenv(info_t *);
int populate_env_list(info_t *);

/* handle_getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* handle_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info); /**
 * struct liststr - singly str link list
 * @num: the numb input
 * @str: str
 * @next: pts to next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - pseudo-arguements to pass a function,
 * uniform prototype for fnxtn ptr struct
 * @arg: str generated from getline containing args
 * @argv: array vector str for arg
 * @path: str command path
 * @argc: arg count
 * @line_count: error count
 * @err_num: error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: input filename
 * @env: linked list cp of environ
 * @environ: cmodified cp of environ from LL envrn
 * @history:  node
 * @alias: alias node
 * @env_changed: environ changed
 * @status: return status of last exec.  command
 * @cmd_buf: addr of ptr to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: file descriptor from which to read line input
 * @histcount: history line numb cnt
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* ptr to cmd ; chain buffer, for memory mgt */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin - contains builtin str n related fnxtn
 * @type: builtin cmd flag
 * @func: fnxtn
 */
typedef struct builtin
{
	char *type;

int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* handle_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* handle_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* handle_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);


#endif /* _SHELL_H_ */

