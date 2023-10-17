#include "shell.h"

/**
 * _envbuiltin - prints the environment of the current directory
 * @env: array of environment variables
 * @args: an array of strings inputted
 * Return: 0 on success
 */

int _envbuiltin(char **args, char **env)
{
	int i = 0, j = 0;
	(void)args;

	while (env[i])
	{
		while (env[i][j])
		{
			write(1, &env[i][j], 1);
			j++;
		}
		j = 0;
		i++;
		write(1, "\n", 1);
	}
	return (0);
}

/**
 * _cdbuiltin - changes the current directory
 * @args: array of commmands tokenized
 * @env: an array of environment variables
 * Return: 0 on success, -1 on error
 */

int _cdbuiltin(char **args, char **env)
{
	char *new_dir = NULL, *current_dir = NULL, *new_current_dir = NULL;
	(void)env;

	if (args[1] == NULL || _strcmp(args[1], "~") == 0)
		new_dir = getenv("HOME");
	else if (_strcmp(args[1], "-") == 0)
		new_dir = getenv("OLDPWD");
	else
		new_dir = args[1];
	if (new_dir == NULL)
	{
		fprintf(stderr, "Error: environment variable not found\n");
		return (-1);
	}
	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
	{
		perror("malloc");
		return (-1);
	}
	if (chdir(new_dir) == -1)
	{
		perror("chdir"), free(current_dir);
		return (-1);
	}
	if (setenv("OLDPWD", current_dir, 1) == -1)
	{
		perror("setenv"), free(current_dir);
		return (-1);
	}
	new_current_dir = getcwd(NULL, 0);
	if (new_current_dir == NULL)
	{
		perror("getcwd"), free(current_dir);
		return (-1);
	}
	if (setenv("PWD", new_current_dir, 1) == -1)
	{
		perror("setenv"), free(current_dir), free(new_current_dir);
		return (-1);
	}
	free(current_dir), free(new_current_dir);
	return (0);
}
