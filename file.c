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
* save pointer to the file (full_file_name).
*
*/
FILE* open_file(const char* file_name)
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
	return fp;
}

/*
* closing the file. (full_file_name)
*/
void close_file()
{
	fclose(fp);
}

/*----------------------------*/
char* runOnLine()
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
	int word_length;
	int curr_word_index;
	int curr_char_index;
	char curr_char;
	int word_char;
	char* curr_word;

	if (line == NULL)
		return NULL;

	word_length = MAX_LINE_LENGTH;
	curr_word = (char*)malloc((size_t)word_length * sizeof(char));

	curr_word_index = 0;
	curr_char = line[curr_char_index];

	while (curr_char != '\0' && !IsBlank(curr_char))
	{
		curr_char_index++;
		curr_char = line[curr_char_index];
	} /* end of while */

	while (IsBlank(curr_char))
	{
		curr_char_index++;
		curr_char = line[curr_char_index];
	}

	curr_word_index++;


	/**/
	word_char = 0;
	while (curr_char != '\0' && !IsBlank(curr_char))
	{
		if (word_char - 1 == word_length)
		{
			word_length += MAX_LINE_LENGTH;
			curr_word = (char*)realloc((word_length + 1) * sizeof(char));
		}

		curr_word[word_char] = curr_char;
		curr_char_index++;
		curr_char++;
		curr_char = line[curr_char_index];
	}/* end of while */

	curr_word[word_char] = '\0';

	if (strlen(curr_word) == 0)
		return NULL;
	return curr_word;
} /* End of func */