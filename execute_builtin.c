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
	else if (_strcmp(args[0], "cd") == 0 || _strcmp(args[0], "env") == 0
			|| _strcmp(args[0], "alias") == 0 ||  _strcmp(args[0], "exit") == 0)
	{
		return (1);
	}
	else
	{
		return (0);
	}
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
		if (_strcmp(args[1], "HBTN") == 0)
		{
			fprintf(stderr, "./hsh: exit: Illegal number: HBTN\n");
			free_args(args), errno = 2;
			exit(errno);
		}

		status = atoi(args[1]);
		if (status < 0 && args[1][0] != '0')
		{
			fprintf(stderr, "./hsh: exit: Illegal number: %d\n", status);
			free_args(args), errno = 2;
			exit(errno);
		}
		if (status == 0)
		{
			free_args(args);
			exit(status);
		}
	}
	if (errno != 0)
	{
		free_args(args);
		exit(2);
	}
	free_args(args);
	exit(status);
}

/**
 * execute_builtin - Executes builtin commands
 * @args: An array of strings inputted
 * @env: An array of environment variables
 *
 * Return: 0 on success
 */

int execute_builtin(char **args, char **env)
{
	alias_t **aliases = NULL;

	if (args == NULL || args[0] == NULL)
		return (1);
	if (_strcmp(args[0], "exit") == 0)
		return (_exitbuiltin(args, env));
	if (_strcmp(args[0], "env") == 0)
		return (_envbuiltin(args, env));
	if (_strcmp(args[0], "cd") == 0)
		return (_cdbuiltin(args, env));
	if (_strcmp(args[0], "alias") == 0)
	{
		return (alias_builtin(args, aliases));
	}
	free_args(args);
	return (0);
}
