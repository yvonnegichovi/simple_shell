#include "shell.h"

void out(const char *message)
{
write(STDOUT_FILENO, message, strlen(message));
}
