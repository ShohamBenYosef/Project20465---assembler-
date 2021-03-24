/*
* main.c
*/

#include "file.h"
#include "error.h"
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "parse.h"
#include "translate.h"



int main(int argc, char* argv[])
{
	int success = 0;

	if (argc >= 2)
	{
		for (; argc > 1; argc--)
		{

			open_file(argv[argc - 1], MainFileEnding, "r");

			success = parse(parser_data.file);
			close_file();

			if (!success) {
				printf("Error found - skipping to the next file\n");
				continue;
			}
			else {
				parse2(parser_data.file);
			}

			freeParserData(parser_data);

		} /* End of for loop*/
	}/* End of if condition. */
	else {
		fatal_error(ErrorMissingArgument);
	}
	return 0;
} /* End of main*/