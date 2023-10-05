#include "shell.h"

/**
 * split_string - splits an array of string
 * @input: array of strings inputed
 * Return: an array of string
 */

char **split_string(char *input)
{
	char **tokens, *delimeter = " \"\n\t\r", *input_copy = NULL;
	char *stoks;
	int i = 0, num_tokens = 0;

	input_copy = _strdup(input);
	stoks = strtok(input_copy, delimeter);
	while (stoks != NULL)
		num_tokens++, stoks = strtok(NULL, delimeter);
	num_tokens++;
	tokens = malloc(sizeof(char *) * (num_tokens + 1));
	if (tokens == NULL)
	{
		perror("Error allocating memory for tokenizing");
		free(input_copy);
		return (NULL);
	}
	free(input_copy);
	input_copy = _strdup(input);
	stoks = strtok(input_copy, delimeter);
	for (i = 0; stoks != NULL; i++)
	{
		tokens[i] = _strdup(stoks);
		stoks = strtok(NULL, delimeter);
	}
	tokens[i] = NULL;
	free(input_copy);
	return (tokens);
}

/**
 * free_args - frees args
 * @args: array of strings
 */

void free_args(char **args)
{
	int i = 0;

	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

