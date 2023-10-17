#include "shell.h"

/**
 * alias_builtin - implements the alias builtin command
 * @args: an array of strings containing the command
 * and its arguments
 * @aliases: an array to store the aliases
 * Return: 0 on success, 1 on error
 */

int alias_builtin(char **args, alias_t **aliases)
{
	int i = 1;
	char *name, *value;

	if (args[1] == NULL)
	{
		print_all_aliases(aliases);
		return (0);
	}
	while (args[i])
	{
		if (_strstr(args[i], "="))
		{
			name = strtok(args[i], "=");
			value = strtok(NULL, "=");
			create_or_update_alias(aliases, name, value);
		}
		else
			print_alias_value(aliases, args[i]);
		i++;
	}
	return (0);
}

/**
 * print_all_aliases - print all aliases
 * @aliases: an array of aliases
 */

void print_all_aliases(alias_t **aliases)
{
	alias_t *current = *aliases;

	while (current)
	{
		printf("alias %s='%s'\n", current->name, current->value);
		current = current->next;
	}
}

/**
 * print_alias_value - print the value of a specific  alias
 * @aliases: an array of aliases
 * @name: the name of the alias
 */

void print_alias_value(alias_t **aliases, char *name)
{
	alias_t *current = find_alias(aliases, name);

	if (current)
	{
		printf("alias %s='%s'\n", current->name, current->value);
	}
	else
	{
		fprintf(stderr, "alias: %s: not founnd\n", name);
	}
}

/**
 * create_or_update_alias - create or update an alias
 * @aliases: an array of aliases
 * @name: the name of the alias
 * @value: the value of the alias
 */

void create_or_update_alias(alias_t **aliases, char *name, char *value)
{
	alias_t *current = find_alias(aliases, name);
	alias_t *new_alias;

	if (current)
	{
		free(current->value);
		current->value = _strdup(value);
	}
	else
	{
		new_alias = malloc(sizeof(alias_t));
		if (new_alias)
		{
			new_alias->name = _strdup(name);
			new_alias->value = _strdup(value);
			new_alias->next = *aliases;
			*aliases = new_alias;
		}
	}
}

/**
 * find_alias - fiind an alias by name
 * @aliases:: an array of aliases
 * @name: the name of the alias to find
 * Return: a pointer to the found alias or NULL if not found
 */

alias_t *find_alias(alias_t **aliases, char *name)
{
	alias_t *current = *aliases;

	while (current)
	{
		if (_strcmp(current->name, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
