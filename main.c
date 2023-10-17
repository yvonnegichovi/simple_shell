#include "shell.h"

/**
 * main - simple shell code
 * @argc: number of arguments passed into the shell program
 * @argv: an array of arguments passed into the shell program
 * @env: an array of environment variables
 * Return: 0 on success
 */

int main(int argc, char **argv, char **env)
{
	char *buffer = NULL, *prompt = "$ ", **args = NULL;
	size_t buffsize = 0;
	ssize_t nlength;
	int mode = isatty(0);
	(void)argc;
	(void)argv;

	while (1)
	{
		if (mode == 1)
			write(STDOUT_FILENO, prompt, _strlen(prompt));
		nlength = _getline(&buffer, &buffsize, stdin);
		if (nlength == -1)
		{
			if (mode == 1)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		args = split_string(buffer);
		if (args == NULL)
		{
			free(buffer), free_args(args);
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
		execute_command(args, env);
		free_args(args);
		if (buffer)
			free(buffer), buffer = NULL;
	}
	if (buffer)
		free(buffer);
	return (0);
}
