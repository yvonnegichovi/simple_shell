#include "shell.h"

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *det;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	det = malloc(sizeof(char) * (length + 1));
	if (!det)
		return (NULL);
	for (length++; length--;)
		det[length] = *--str;
	return (det);
}

/**
 * _strcmp - compares two strings
 * @str1: first string to compare
 * @str2: second string to compare
 * Return: 0 if str1 and str2 are equal,
 * less than 0 if str1 is less than str2
 * more than 0 if str1 is greater than str2
 */

int _strcmp(char *str1, char *str2)
{
	while (*str1 == *str2)
	{
		if (*str1 == '\0')
		{
			return (0);
		}
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

/**
 * _strstr - locates a substring
 * @s: input
 * @c: input
 * Return: Always 0 (Success)
 */
char *_strstr(char *s, char *c)
{
	int i, j;

	for (i = 0; s[i] != '\0'; i++)
	{
		for (j = 0; c[j] != '\0'; j++)
		{
			if (s[i + j] != c[j])
				break;
		}
		if (!c[j])
			return (&s[i]);
	}
	return (0);
}

