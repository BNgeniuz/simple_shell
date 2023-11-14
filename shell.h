#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

void print_numbers(void);
char *tag_comment(char *input);
int main(int argc, char *argv[], char **environ);
void handle_cd(char **argc, int argv);
void handle_exit(char *input, int exit_position);
void print_env(char **environment);
void print_env(void);

/* command functions */
int startswith_forwardslash(char const *str);
char *get_files_path(char *file_name);
char *get_files_loc(char *path, char *file_name);
void execute_command(char *input, char *argv[], char **env);
char *read_input(void);
void print_prompt(void);
int tokenize_input(char *input, char *args[]);

/* Builtins commands */
int handle_builtin_commands(char **args,
		int num_args, char *input,
		char **env);
void print_env(char **env);
void handle_cd(char **args, int num_args);
void handle_exit(char *input, int exit_status);
int shell_exit(char **args, char *input);

/* comment handlers */
char *handle_comment(char *input);



#endif /* SHELL_H */
