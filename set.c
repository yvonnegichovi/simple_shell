#include "shell.h"
/**
* allows you to use the setenv and unsetenv commands. 
* You can compile and run this C program to test the functionality.
*  To exit the shell, simply enter the "exit" command.
*/
int my_setenv(const char *name, const char *value)
{
	if (name == NULL || value == NULL)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return (-1);
	}

	if (setenv(name, value, 1) !=0)
	{
		perror("setenv");
		return (-1);
	}
	return (0);
}


int my_unsetenv(const char *name)
{
	if (name == NULL)
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return (-1);
	}

	if (unsetenv(name) !=0)
	{
		perror("unsetenv");
		return (-1);
	}
	return (0);
}
