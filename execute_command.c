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
