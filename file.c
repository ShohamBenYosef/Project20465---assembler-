/*
* file.c
*/

#pragma warning(disable : 4996)

/*#include "error.h"*/
#include "file.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>

FILE* fp;

/*
* open a file for reading.
* save pointer to the file in global variable (full_file_name).
*
*/
void open_file(const char* file_name)
{

	/*char**/ full_file_name = (char*)malloc((strlen(file_name) + 4));

	if (!full_file_name)
		fatal_error(ErrorMemoryAlloc);

	strcpy(full_file_name, file_name);
	strcat(full_file_name, FileEnding);

	fp = fopen(full_file_name, "r");
	if (!fp)
	{
		fprintf(stderr, ErrorCantRead, full_file_name);
		fprintf(stderr, "\n");
		free(full_file_name);
		exit(EXIT_FAILURE);
	}

	free(full_file_name);
}

/*
* closing the file. (full_file_name)
*/
void close_file()
{
	fclose(fp);
}

/**/