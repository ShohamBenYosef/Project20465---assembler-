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
	int works= 0;/* דגל לבדיקה אם היו איזשהן תקלות בסיבוב הראשון*/

	if (argc >= 2)
	{
		while (--argc > 0)
		{
			open_file(*++argv,MainFileEnding, "r");

			/*it_works = assembler_rd1(); /* ROUND 1*/   /*סיבוב ראשון*/
			close_file();
			if (works)
			{
				printf("round 1 works successfuly.\n");
				/*it_works = assembler_rd2() /* ROUND 2 */  /* סיבוב שני*/
				if (works)
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