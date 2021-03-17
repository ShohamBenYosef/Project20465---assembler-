/*
* main.c
*/

#include "file.h"
#include "error.h"
#include <stdlib.h>
#include <stdio.h>




/*******************************/
int main(int argc, char* argv[])
{
	FILE* fp;
	int succsses = 0;

	if (argc >= 2)
	{
		while (--argc > 0)
		{
			open_file(*++argv,MainFileEnding, "r");

			succsses= parse();
			close_file(full_file_name, MainFileEnding);
			if (succsses)
			{
				printf("round 1 works successfuly.\n");
				succsses = parse2();
				if (succsses)
					printf("file assembled.");
				else {
					printf("Errors in round 2.\n");
				}
			}
			else {
				printf("Error Found!, continue to the next file(?).\n");
				/*assembler_clean();*/
				continue;
			}

			/*clean();  in assambler file...*/  /*  לכתוב - פונקציה שמנקה את מחסנית הקריאות ומאפסת את הדגלים*/
		} /* End of while loop*/
	}/* End of if condition. */
	else {
		fatal_error(ErrorMissingArgument);
	}
	printf("END OF PROGRAM");
	return 0;
} /* End of main*/