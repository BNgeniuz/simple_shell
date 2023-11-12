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

int add_numbers(int a, int b);
char *tag_comment(char *input);
int main(int argc, char *argv[], char **environ);
void handle_cd(char **argc, int argv)
void handle_exit(char *input, int exit_position)
void print_env(char **environment)
int shell_exit(char **args, char *input)


#endif /* SHELL_H */
