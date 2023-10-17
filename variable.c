#include "shell.h"

/**
 * vito - retrieves the process ID using getpid() and prints it
 * Return: 0 on success
 *
 * Description: It sets up a loop to continuously read user input.
 * It uses fgets to read a line of input from the user.
 * It removes the newline character at the end of the input
 * to make it more user-friendly.
 * It checks if the input is equal to "$" and,
 * if so, retrieves the process ID using getpid() and prints it.
 */

int vito(void)
{
	char input[MAX_INPUT_LENGTH];

	while (1)
	{
		fgets(input, sizeof(input), stdin);
		if (strcspn(input, "$ ") == 0)
		{
			pid_t pid = getpid();

			printf("Process ID (PID): %d/n", pid);
		}
	}
	return (0);
}
