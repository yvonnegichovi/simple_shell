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
	char **tokens = NULL, *stoks, *path_copy = NULL;
	int i = 0, num_tokens = 0;

	path_copy = _strdup(path);
	stoks = strtok(path_copy, ":");
	while (stoks != NULL)
		num_tokens++, stoks = strtok(NULL, ":");
	tokens = malloc(sizeof(char *) * (num_tokens + 1));
	if (tokens == NULL)
	{
		perror("Error tokenizing");
		free(path_copy);
		return (NULL);
	}
	free(path_copy);
	path_copy = _strdup(path);
	stoks = strtok(path_copy, ":");
	for (i = 0; i < num_tokens; i++)
	{
		tokens[i] = _strdup(stoks);
		stoks = strtok(NULL, ":");
	}
	tokens[i] = NULL;
	free(path_copy);
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
			perror("Forking failed"), free_args(args);
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (args[0] != NULL && _strstr(args[0], "/") != NULL)
			{
				if (execve(args[0], args, env) == -1)
					perror("Execution failed"),  free_args(args), exit(EXIT_FAILURE);
			}
			else
			{
				path = find_command(args[0], env);
				if (path != NULL)
				{
					if (execve(path, args, env) == -1)
						perror("Exec failed"), free(path), free_args(args), exit(EXIT_FAILURE);
				}
				else
				{
					perror("Command not found"), free(path), free_args(args);
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
	char *path_env = find_path(env), **paths, *full_path = NULL;
	int i = 0;

	if (path_env != NULL)
	{
		paths = split_path(path_env);
		for (i = 0; paths[i] != NULL; i++)
		{
			if  (paths[i] != NULL && command != NULL)
			{
				full_path = malloc(strlen(paths[i]) + strlen(command) + 2);
				if (full_path != NULL)
				{
					sprintf(full_path, "%s/%s", paths[i], command);
					if (access(full_path, X_OK) == 0)
					{
						free_tokens(paths);
						return (full_path);
					}
					free(full_path);
				}
				else
				{
					perror("Memory allocation failed");
					free_tokens(paths);
					return (NULL);
				}
			}
			else
			{
				perror("Error: path or command is empty");
			}
		}
	}
	free_tokens(paths);
	return (NULL);
}

/**
* free_tokens - frees tokens
* @tokens: a pointer to a pointer to an array of tokens
*/

void free_tokens(char **tokens)
{
	int i = 0;

	while (tokens[i] != NULL)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
