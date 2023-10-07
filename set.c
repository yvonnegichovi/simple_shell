#include"shell.h"
/*
 *
 */
int my_setevn(const char *name, const char *value)
{
	if (name == NULL || value == NULL)
	{
		fprintf(stderr, "usage: of setenv VARIABLE VALUE\n");
		return (1);
	}
	if (setenv(name, value, 1) != 0)
	{
		perror("setevn");
		return (1);
	}
	return (0);
}
int my_unsetevn (const char *name)
{
	if (name == NUll)
	{
		fprintf(stderr, "usage: unsetevn VARIABLE \n")
			return (1);
	}
	if (unsetenv(name) != 0)
	{
		perror("unsetevn")
			return (1);
	}
	return (0);
}
