#include "shell.h"

int last_exit_status = 0;

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
	else if (_strcmp(args[0], "echo") == 0 && _strcmp(args[1], "$?") == 0)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * echo_last_exit_status - prints the last exit status
 * Return: 0 on success
 */

int echo_last_exit_status(void)
{
	printf("%d\n", last_exit_status);
	return (0);
}

 /**
 * execute_builtin - Executes builtin commands
 * @args: An array of strings inputted
 * @env: An array of environment variables
 *
 * Return: 0 on success
 */

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
			printf("args[1]: \"%s\"\n", args[1]);
			fprintf(stderr, "./hsh: exit: Illegal number: HBTN\n");
			errno = 2, last_exit_status = errno;
			exit(errno);
		}

		status = atoi(args[1]);
		if (status == 0 && args[1][0] != '0')
		{
			errno = 0, last_exit_status = errno;
			exit(errno);
		}
		else if (status < 0 && args[1][0] != '0')
		{
			fprintf(stderr, "./hsh: exit: Illegal number: %d\n", status);
			errno = 2, last_exit_status = errno;
			exit(errno);
		}
	}
	free_args(args), last_exit_status = status;
	exit(status);
}

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
	if (_strcmp(args[0], "echo") == 0 && _strcmp(args[1], "&?") == 0)
	{
		return (echo_last_exit_status());
	}
	free_args(args);
	return (0);
}
