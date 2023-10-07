#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <stdbool.h>
#include <errno.h>
#include <fcntl.h>

#define MAX_ENV_LEN 100

int my_setenv(const char *name, const char *value);
extern char **environ;
char **split_string(char *input);
void free_args(char **args);
int is_builtin(char **args, char **env);
int _envbuiltin(char **args, char **env);
int _exitbuiltin(char **args, char **env);
int _cdbuiltin(char **args, char **env);
int execute_builtin(char **args, char **env);
char *find_path(char **env);
char **split_path(char *path);
void execute_command(char **args, char **env);
char *find_command(char *command, char **env);
void free_tokens(char **tokens);

/* strings functions */

char *_strchr(char *s, char c);
char *_strcpy(char *dest, char *src);
int _strlen(char *s);
char *_strdup(const char *str);
int _strcmp(char *str1, char *str2);
char *_strcat(char *dest, char *src);
char *_strstr(char *s, char *c);

/* built-in functions */


#endif /* SHELL_H */

