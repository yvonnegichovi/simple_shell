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
 * _aliasbuiltin - prints alias variables
 * Return: 0 on success
 */

int _aliasbuiltin(void)
{
	char *path = getenv("PATH");

	if (path != NULL)
		printf("PATH = %s\n", path);
	else
	{
		printf("PATH is not set.\n");
	}
	setenv("MY_VARIABLE", "some_value", 1);
	unsetenv("MY_VARIABLE");
	return (0);
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
