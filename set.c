#include "shell.h"
/*
 *
 */


int my_setenv(const char *name, const char *value) {
    if (name == NULL || value == NULL) {
        fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
        return -1;
    }

    if (setenv(name, value, 1) != 0) {
        perror("setenv");
        return -1;
    }

    return 0;
}

int my_unsetenv(const char *name) {
    if (name == NULL) {
        fprintf(stderr, "Usage: unsetenv VARIABLE\n");
        return -1;
    }

    if (unsetenv(name) != 0) {
        perror("unsetenv");
        return -1;
    }

    return 0;
}

int main() {
    char input[MAX_ENV_LEN * 2];
    char *command, *variable, *value;

    while (1) {
        printf("Enter a command (setenv, unsetenv, or exit): ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("fgets");
            exit(EXIT_FAILURE);
        }

        input[strcspn(input, "\n")] = '\0';

        command = strtok(input, " ");
        if (command == NULL) {
            printf("Please enter a command.\n");
            continue;
        }

        if (strcmp(command, "setenv") == 0) {
            variable = strtok(NULL, " ");
            value = strtok(NULL, " ");
            if (my_setenv(variable, value) == -1) {
                fprintf(stderr, "Failed to set environment variable.\n");
            }
        } else if (strcmp(command, "unsetenv") == 0) {
            variable = strtok(NULL, " ");
            if (my_unsetenv(variable) == -1) {
                fprintf(stderr, "Failed to unset environment variable.\n");
            }
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            fprintf(stderr, "Unknown command: %s\n", command);
        }
    }

    return 0;
}
