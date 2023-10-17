#include "shell.h"

/**
 * my_setenv - Initialize a new environment variable,
 * or modify an existing one
 * @name: name of the new environment variable
 * @value: value of the new environment
 * Return: 0 on success
 */

int my_setenv(const char *name, const char *value)
{
	if (name == NULL || value == NULL)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return (-1);
	}
	if (setenv(name, value, 1) != 0)
	{
		perror("setenv");
		return (-1);
	}
	return (0);
}

/**
 * my_unsetenv - Remove an environment variable
 * @name: name of environment variable to be removed
 * Return: 0 on success
 */

int my_unsetenv(const char *name)
{
	if (name == NULL)
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return (-1);
	}
	if (unsetenv(name) != 0)
	{
		perror("unsetenv");
		return (-1);
	}
	return (0);
}
