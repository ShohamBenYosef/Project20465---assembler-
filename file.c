/*
* file.c
*/
#pragma warning(disable : 4996)
#pragma warning(disable : 6001)

#include "utils.h"
#include "file.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* The file being read. */
FILE* file;

/* The name of the file being currently read, without extension. */
char* file_name_base;



void open_file(const char* file_name, char* ending, char* mod)
{
	printf("IN FILE.C - open file\n");
	char* full_file_name;

	file_name_base = (char*)malloc((strlen(file_name) + 4));
	if (!file_name_base)
		fatal_error(ErrorMemoryAlloc);
	printf("after memory allocation \n");
	strcpy(file_name_base, file_name);
	printf("after strcpy - send to get file name *** file name base = %s\n", file_name_base);
	full_file_name = get_file_name(ending);
	/* Opening. */
	printf(" try to open: %s\n", full_file_name);
	file = fopen(full_file_name, mod);
	if (!file)
	{
		/* TODO*/
		fprintf(stderr, ErrorCantRead, full_file_name);
		fprintf(stderr, "\n");
		free(full_file_name);
		exit(EXIT_FAILURE);
	}

	free(full_file_name);
}

char* get_file_name(const char* ending)
{
	printf("IN FILE.C - get file name**** end =  %s\n", ending);
	char* file_name;


	int totalLength = strlen(file_name_base) + strlen(ending) + 1;
	file_name = (char*)malloc(totalLength);
	if (!file_name)
		fatal_error(ErrorMemoryAlloc);
	printf("after memeory allocation\n");
	strcpy(file_name, file_name_base);
	printf("after strcpy\n");
	strcat(file_name + 1, ending);
	file_name[totalLength] = '\0';
	printf("IN FILE.C end of get file name - back to open file\n file name:   %s\n", file_name);
	return file_name;
}



char* runOnLine(FILE* fp)
{
	printf(" in runOnLine\n");
	/* build array for each line. */
	int line_length = MAX_LINE_LENGTH;
	int current_pos = 0;
	char* line = (char*)malloc(line_length);

	if (!line)
		fatal_error(ErrorMemoryAlloc);
	printf("after memory allocation. \n");
	do {
		line[current_pos++] = getc(fp);
		printf(" line[] = %c\n", line[current_pos]);
		if (!(current_pos % MAX_LINE_LENGTH))
		{
			/* */
			line_length += MAX_LINE_LENGTH;
			line = (char*)realloc(line, line_length);
			if (!line)
				fatal_error(ErrorMemoryAlloc);
		} /* end of IF */
	} while (line[current_pos - 1] != '\n' && line[current_pos - 1] != EOF);

	if (line[0] == EOF)
	{
		free(line);
		return NULL;
	}

	line[current_pos - 1] = '\0';
	printf("all the line is: %s \n", line);
	return line;
}


char* read_word(const char* line, const int line_num, FILE* fp)
{
	printf("IN READ WORD\n");

	if (line)
	{

		char* all[MAX_LINE_LENGTH];
		char* curr_word = (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
		if (!curr_word)
			fatal_error(ErrorMemoryAlloc);

		printf("after memory alocation.\n");
		strcpy(all, line);
		curr_word = strtok(all, "	, ");
		printf("after strtok  curr_word = %s\n", curr_word);
		return curr_word;
	}
	return '\0';
} /* End of func */


void close_file() {
	fclose(file);
}