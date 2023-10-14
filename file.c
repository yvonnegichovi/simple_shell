#include "shell.h"
/*
*
*/
int fold(int argc, char *argv[]) 
{
	 const char *filename = argv[1];
	  char command[1000];
	   FILE *file = fopen(filename, "r");
    if (argc != 2) {
        printf("Usage: %s [filename]\n", argv[0]);
        return 1;
    }


    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    while (fgets(command, sizeof(command), file) != NULL) {
        int exit_status = system(command);
        if (exit_status == -1) {
            perror("system");
        }
    }

    fclose(file);
    return 0;
}

