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
#define MAX_INPUT_LENGTH 1024

/* user-defined functions */

int my_setenv(const char *name, const char *value);
extern char **environ;
int fold(int argc, char *argv[]);
int vito(void);
char **split_string(char *input);
void free_args(char **args);
char *find_path(char **env);
char **split_path(char *path);
void execute_command(char **args, char **env);
char *find_command(char *command, char **env);
void free_tokens(char **tokens);
ssize_t _getline(char **line, size_t *n, FILE *stream);
int comment(void);

/* strings functions */

char *_strchr(char *s, char c);
char *_strcpy(char *dest, char *src);
int _strlen(char *s);
char *_strdup(const char *str);
int _strcmp(char *str1, char *str2);
char *_strcat(char *dest, char *src);
char *_strstr(char *s, char *c);

/* builtin functions */

int is_builtin(char **args, char **env);
int _envbuiltin(char **args, char **env);
int _exitbuiltin(char **args, char **env);
int _cdbuiltin(char **args, char **env);
int update_pwd(char *new_dir, char **env);
int change_directory(char *new_dir);
int execute_builtin(char **args, char **env);

/* alias functions */

/**
 * struct alias_s - user defined struct to handle alias command
 * @name: name of thr alias
 * @value: value of the alias
 * @next: pointer to the next alias(for a linked lisst)
 */

typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;
alias_t *find_alias(alias_t **aliases, char *name);
void create_or_update_alias(alias_t **aliases, char *name, char *value);
void print_alias_value(alias_t **aliases, char *name);
void print_all_aliases(alias_t **aliases);
int alias_builtin(char **args, alias_t **aliases);

#endif /* SHELL_H */
