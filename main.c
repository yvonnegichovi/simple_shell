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

	for (;;)
	{
		if (mode == 1)
			write(STDOUT_FILENO, prompt, _strlen(prompt));
		nlength = getline(&buffer, &buffsize, stdin);
		if (nlength == -1)
		{
			if (mode == 1)
				write(STDOUT_FILENO, "\n", 1);
			free(buffer);
			continue;
		}
		args = split_string(buffer), buffer = NULL;
		execute_command(args, env);
		free(buffer);
		free_args(args);
	}
	return (0);
}

