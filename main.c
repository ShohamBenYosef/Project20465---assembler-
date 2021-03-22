/*
* main.c
*/

#include "file.h"
#include "error.h"
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "asm.h"
#include "translate.h"

extern file;
/*******************************/
int main(int argc, char* argv[])
{
	int success = 0;
	printf("in main - start 1\n");

	printf("before check arg\n");
	if (argc >= 2)
	{
		printf("before for loop\n");
		for (; argc > 1; argc--)
		{

			printf("in main - start 2   open file\n");
			open_file(argv[argc - 1], MainFileEnding, "r");
			printf("after open\n");
			success = parse(file);
			close_file();

			if (!success)
			{
				printf("Errors found, skipping translation.\n****************************************************************************************************************************\n");
				/*clean();*/
				continue;
			}
			printf("back to main  \n");


		} /* End of for loop*/
	}/* End of if condition. */
	else {
		fatal_error(ErrorMissingArgument);
	}
	printf("END OF PROGRAM");
	return 0;
} /* End of main*/