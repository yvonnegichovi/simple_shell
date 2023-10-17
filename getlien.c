#include "shell.h"

#define MAX_BUFFER_SIZE 1024

/**
 * _getline - reads a lie from stdin
 * into a dynamically allocated buffer
 * @line: pointer to a pointer that points to the
 * dynamically allocated buffer
 * @n: pointer to a size_t variable
 * that specifiees the size of theh buffer
 * @stream: stream from which the program reads from
 * Return: number of characters read, inncluding newline,
 * or -1 on failure
 */

ssize_t _getline(char **line, size_t *n, FILE *stream)
{
	char *buffer = *line, c;
	size_t bufferSize = *n;
	size_t bytesRead = 0;

	if (line == NULL  || n == NULL || stream == NULL)
		return (-1);
	while (1)
	{
		c = fgetc(stream);
		if (c == EOF || c == '\n')
		{
			if (c == EOF && bytesRead == 0)
				return (-1);
			if (bytesRead >= bufferSize)
			{
				bufferSize += MAX_BUFFER_SIZE;
				buffer = (char *)realloc(buffer, bufferSize);
				if (buffer == NULL)
					return (-1);
				*line = buffer, *n = bufferSize;
			}
			buffer[bytesRead] = '\0';
			return (bytesRead);
		}
		if (bytesRead >= bufferSize)
		{
			bufferSize += MAX_BUFFER_SIZE;
			buffer = (char *)realloc(buffer, bufferSize);
			if (buffer == NULL)
				return (-1);
			*line = buffer, *n = bufferSize;
		}
		buffer[bytesRead++] = c;
	}
}
