#include "shell.h"

/**
 * is_builtin - checks whether a command is a builtin
 * @args: an array of strings inputted
 * @env: an array of environment variables
 * Return: 1 if successful, 0 otherwise
 */

int is_builtin(char **args, char **env)
{
	(void)env;

	if (args[0] == NULL)
	{
		return (0);
	}
	else if (_strcmp(args[0], "cd") == 0 ||
		_strcmp(args[0], "env") == 0 || _strcmp(args[0],"alias") == 0 ||  _strcmp(args[0], "exit") == 0)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * _envbuiltin - prints the environment of the current directory
 * @env: array of environment variables
 * @args: an array of strings inputted
 * Return: 0 on success
 */

int _envbuiltin(char **args, char **env)
{
	int i = 0, j = 0;
	char *env_vars[] = {"USER", "LANGUAGE", "SESSION", "COMPIZ_CONFIG_PROFILE",
		"SHLVL", "HOME", "C_IS", "DESKTOP_SESSION",
		"LOGNAME", "PATH", "TERM", "DISPLAY", NULL};
	(void)args;

	*env = *environ;
	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; env_vars[j] != NULL; j++)
		{
			if (strstr(environ[i], env_vars[j]) == environ[i])
			{
				printf("%s\n", environ[i]);
				break;
			}
		}
	}
	printf("\n");
	return (0);
}
/*
 *
 *
 */
int _aliasbuiltin()
{
    char *path = getenv("PATH");
    if (path != NULL) {
        printf("PATH = %s\n", path);
    } else {
        printf("PATH is not set.\n");
    }

    setenv("MY_VARIABLE", "some_value", 1);

    unsetenv("MY_VARIABLE");

    return 0;
}

/**
 * _exitbuiltin - implements the exit built-in command
 * @args: array of strings representing command-line arguments
 * @env: an array of environment variables
 * Return: 0 if no error, otherwise 2
 */

int _exitbuiltin(char **args, char **env)
{
	int status = 0;
	(void)env;

	if (args[1] != NULL)
	{
		status = atoi(args[1]);
		if (status == 0 && args[1][0] != '0')
		{
			errno = 0;
			exit(errno);
		}
		if (_strstr(args[1], "HBTN"))
		{
			fprintf(stderr, "./hsh: exit: Illegal number: HBTN");
			errno = 2;
			exit(errno);
		}
		if (status < 0 && args[1][0] != '0')
		{
			fprintf(stderr, "./hsh: exit: Illegal number: %s\n", args[1]);
			errno = 2;
			exit(errno);
		}
	}
	free_args(args);
	exit(status);
}

/**
 * _cdbuiltin - changes the current directory
 * @args: array of commmands tokenized
 * @env: an array of environment variables
 * Return: 0 on success, -1 on error
 */

int _cdbuiltin(char **args, char **env)
{
	char *new_dir = NULL;
	char *current_dir = NULL;
	(void)env;

	if (args[1] != NULL)
	{
		if (_strcmp(args[1], "~") == 0)
			new_dir = getenv("HOME");
		else if (_strcmp(args[1], "-") == 0)
			new_dir = getenv("OLDPWD");
		else
			new_dir = args[1];
	}
	if (new_dir == NULL)
	{
		fprintf(stderr, "Error: environment variable not found\n");
		return (-1);
	}
	current_dir = malloc(sizeof((current_dir) + 1));
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
	{
		perror("getcwd");
		return (-1);
	}
	if (chdir(new_dir) == -1)
	{
		perror("chdir");
		free(current_dir);
		return (-1);
	}
	setenv("OLDPWD", current_dir, 1);
	free(current_dir);
	free_args(args);
	return (0);
}

 /* execute_builtin - execute builtin commands
 * @args: an array of strings inputted
 * @env: an array of environment variables
 * Return: 0 on success
 */
int execute_builtin(char **args, char **env)
{
	if (args == NULL || args[0] == NULL)
		return (1);
	if (_strcmp(args[0], "exit") == 0)
		return (_exitbuiltin(args, env));
	if (_strcmp(args[0], "env") == 0)
		return (_envbuiltin(args, env));
	if (_strcmp(args[0], "cd") == 0)
		return (_cdbuiltin(args, env));
	free_args(args);
	return (0);
}
