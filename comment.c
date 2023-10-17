#include "shell.h"

/**
 * comment - writes a comment after a variable command
 * Return: 0 on success
 */

int comment(void)
{
	char user_comment[1000];

	printf("enter comments(type 'end'on a new line to stop):\n");
	while (1)
	{
		fgets(user_comment, sizeof(user_comment), stdin);
		if (strcmp(user_comment, "end\n") == 0)
			break;

	printf("Comment: %s", user_comment);
	}
	return (0);
}






