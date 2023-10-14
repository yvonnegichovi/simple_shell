#include "shell.h"
/*
 *
 */

int vito () {
    int status;
    char* path = getenv("PATH");

    status = system("ls /var");

    printf("$ echo $?\n%d\n", WEXITSTATUS(status));

    printf("$ echo $$\n%d\n", getpid());

    printf("$ echo $PATH\n%s\n", path);

    return 0;
}
