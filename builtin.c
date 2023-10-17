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
	char *new_dir = NULL;
	(void)env;

	if (args[1] == NULL || _strcmp(args[1], "~") == 0)
		new_dir = getenv("HOME");
	else if (_strcmp(args[1], "-") == 0)
		new_dir = getenv("OLDPWD");
	else
		new_dir = args[1];
	if (!new_dir)
	{
		fprintf(stderr, "Error: env variable not found\n");
		return (-1);
	}
	if (change_directory(new_dir) == -1)
		return (-1);
	if (update_pwd(new_dir, env) == -1)
		return (-1);
	return (0);
}

/**
 * change_directory - changes the directory
 * @new_dir: the new directory
 * Return: 0 on success
 */

int change_directory(char *new_dir)
{
	if (chdir(new_dir) == -1)
	{
		perror("chdir");
		return (-1);
	}
	return (0);
}

/**
 * update_pwd - updates the new pwd
 * @new_dir:the new new directory to be updated
 * @env: an array of environment variables
 * Return: 0 on success
 */

int update_pwd(char *new_dir, char **env)
{
	char *new_current_dir = NULL, *current_dir = NULL;
	(void)new_dir;
	(void)env;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
	{
		perror("getcwd");
		return (-1);
	}
	if (setenv("OLDPWD", current_dir, 1) == -1)
	{
		perror("setenv"), free(current_dir);
		return (-1);
	}
	free(current_dir);
	new_current_dir = getcwd(NULL, 0);
	if (!new_current_dir)
	{
		perror("getcwd");
		return (-1);
	}
	if (setenv("PWD", new_current_dir, 1) == -1)
	{
		perror("setenv"), free(new_current_dir);
		return (-1);
	}
	free(new_current_dir);
	return (0);
}
