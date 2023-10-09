#include "shell.h"
/*
 *
 */
int main ()
{
	char user_comment[1000];

		printf("enter comments(type 'end'on a new line to stop):\n");
	while (1){
		fgets(user_comment, sizeof(user_comment ),stdin);
	
	if (strcmp(user_comment ,"end\n")==0)
                {
                        break;
                }
         printf("Comment: %s",user_comment);
	}

    return (0);
}






