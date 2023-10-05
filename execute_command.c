#include "shell.h"

/**
 * find_path - finds the path of the user input
 * and returns a pointer to the path variable
 * @env: an array of environment variables
 * Return: pointer to the path
 */

char *find_path(char **env)
{
	char *path = NULL;
	int i = 0;

	while (env[i])
	{
		if (_strstr(env[i], "PATH") && env[i][0] == 'P' && env[i][4] == '=')
		{
			path = env[i];
			break;
		}
		i++;
	}
	if (path != NULL)
	{
		for (i = 0; i < 6; i++)
			path++;
	}
	return (path);
}

/**
 * split_path - splits the path
 * @path: path found and to be splitted
 * Return: an array of splitted path
 */

char **split_path(char *path)
{
	char **tokens = NULL, *stoks;
	int i = 0, num_tokens = 0;

	stoks = strtok(path, ":");
	while (stoks != NULL)
		num_tokens++, stoks = strtok(NULL, ":");
	tokens = malloc(sizeof(char *) * (num_tokens + 1));
	if (tokens == NULL)
	{
		perror("Error tokenizing");
		return (NULL);
	}
	stoks = strtok(path, ":");
	for (i = 0; i < num_tokens; i++)
	{
		tokens[i] = _strdup(stoks);
		stoks = strtok(NULL, ":");
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
 * execute_command - executes all the commands inputted
 * @args: an array of strings inputted
 * @env: an array of environment variables
 */

void execute_command(char **args, char **env)
{
	pid_t pid;
	int status;
	char *path;

	if (is_builtin(args, env))
		execute_builtin(args, env);
	else
	{
		pid = fork();
		if (pid < 0)
		{
			perror("Forking failed");
			return;
		}
		else if (pid == 0)
		{
			if (args[0] != NULL && _strstr(args[0], "/") != NULL)
			{
				if (execve(args[0], args, env) == -1)
					perror("Execution failed"), exit(EXIT_FAILURE);
			}
			else
			{
				path = find_command(args[0], env);
				if (path != NULL)
				{
					if (execve(path, args, env) == -1)
						perror("Execution failed"), exit(EXIT_FAILURE);
				}
				else
				{
					printf("%s: Command not found\n", args[0]);
					exit(EXIT_FAILURE);
				}
			}
		}
		else
			wait(&status), errno = status;
	}
}

/**
 * find_command - finds the command for relative path
 * @command: an array of strings inputted
 * @env: an array of environmant variables
 * Return: full path
 */

char *find_command(char *command, char **env)
{
	char *path_env = find_path(env), **paths, *path_bin, *full_path = NULL;
	int i = 0;

	if (path_env != NULL)
	{
		path_bin = _strstr(path_env, "/usr/bin");
		paths = split_path(path_bin);
		{
			for (i = 0; paths[i] != NULL; i++)
			{
				full_path = malloc(_strlen(paths[i]) + _strlen(command) + 2);
				if (full_path == NULL)
					perror("Memory allocation failed"), exit(EXIT_FAILURE);
				sprintf(full_path, "%s/%s", paths[i], command);
				if (access(full_path, X_OK) == 0)
				{
					free_args(paths);
					return (full_path);
				}
				free(full_path);
			}
		}
	}
	return (NULL);
}

/**
 * free_tokens - frees tokens
 * @tokens: a pointer to a pointer to an array of tokens
 */

void free_tokens(char **tokens)
{
	int i = 0;

	if (tokens != NULL)
	{
		for (i = 0; tokens[i] != NULL; i++)
		{
			free(tokens[i]);
		}
		free(tokens);
	}
}

