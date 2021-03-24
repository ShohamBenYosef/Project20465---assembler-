/*
* file.c
*/
#pragma warning(disable : 4996)
#include "utils.h"
#include "file.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"



void open_file(const char* file_name, char* ending, char* mod)
{
	char* full_file_name;

	parser_data.file_name_base = (char*)malloc((strlen(file_name) + 4));
	if (!parser_data.file_name_base)
		fatal_error(ErrorMemoryAlloc);
	
	strcpy(parser_data.file_name_base, file_name);
	
	full_file_name = get_file_name(ending);
	
	/* Opening. */
	parser_data.file = fopen(full_file_name, mod);
	if (!parser_data.file)
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

	char* file_name;

	int totalLength = strlen(parser_data.file_name_base) + strlen(ending) + 1;
	file_name = (char*)malloc(totalLength);
	if (!file_name)
		fatal_error(ErrorMemoryAlloc);
	
	strcpy(file_name, parser_data.file_name_base);
	strcat(file_name + 1, ending);

	file_name[totalLength] = '\0';
	
	return file_name;
}

char* runOnLine(FILE* fp)
{
	/* build array for each line. */
	int line_length = MAX_LINE_LENGTH;
	int current_pos = 0;
	char* line = (char*)malloc(line_length);

	if (!line)
		fatal_error(ErrorMemoryAlloc);

	do {
		line[current_pos++] = getc(fp);

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
	return line;
}

char* read_word(const char* line, const int line_num, FILE* fp)
{

	if (line)
	{

		char* all[MAX_LINE_LENGTH];
		char* curr_word = (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
		if (!curr_word)
			fatal_error(ErrorMemoryAlloc);

		strcpy(all, line);
		curr_word = strtok(all, "	, ");

		return curr_word;
	}
	return '\0';
} /* End of func */

void close_file() {
	fclose(parser_data.file);
}