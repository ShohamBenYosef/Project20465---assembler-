
#include "asm.h"
#include "file.h"
#include "error.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

char* curr_lebel[80];
char* current_char;


mainList extract_data(mainList* mhead, char* word, int const line_num, char* line)
{
	int param_count = 0, comma_count = 0; 
	long data_num;
	short its_negative = 0;
	mainList* node;
	char* first_dig;


	while (*word != '\n')
	{
		
		NextWord(word);

		/* if the argument is empty. */
		if (*word == '\0' && param_count == 0)
			error_log("Error, There is no data", line_num);
		
		/* illigal characters and words */
		if (!isdigit(*word) && *word != '+' && *word != '-') {
			error_set("Error, The line contain illegal number.", line_num);
			continue;
		}
		
		word++;

		while (!isblank(*word) && *word != '\0' && *word !=',')
		{
			if (*word == '-')
				its_negative = 1; /* flag */
			if (isdigit(*word))
			{
				data_num += *word - '0';
			}
			else
			{
				error_log("Error, the line contain illigal characters", line_num);
				continue;
			}
		} /* end of while */

		if (its_negative)
		{
			data_num = (MAX_DATA_NUM - data_num); /* Complement 2 */
		}
		IC++; /* the actual address*/
		_main_line* dataOfNode;
		/* */
		dataOfNode->address = IC;
		dataOfNode->name = data_num;
		dataOfNode->are = 'A';

		/* */
		CreateAndaddToList(mhead, node);
		(_main_line*)(node->data) = dataOfNode;

		nextWord(*word);


		if (*word == ',')
		{
			word++;
			comma_count++;
		}
	}/* End of first while*/
	
	if (comma_count != (param_count - 1)) {
		error_log("Error, there are too many commas", line_num);
	} 

} /* End of func */


/* String */
mainList extract_string(mainList* mhead, char* word, int const line_num, char* line)
{
	mainList node;
	char* current_char;
	nextWord(word);

	if (*word != '"') {
		error_set("Error, there's no string ", line_num);
		return 0;
	}

	current_char = line + strlen(line) - 1; /* current_char is now on the end of the currect line. */
	
	while (isblank(current_char)) current_char--; /* set the pointer on the end of the string. */

	if (*(current_char) != '"' || current_char == word) { /* check if there is an argument. */
		error_log("Error, String expected after \".string\".\n", line_num);
		return mhead;
	}
	/* adding line in table for every char in the string.*/
	while (word + 1 < current_char)
	{
		IC++; /* the actual address*/
		_main_line* dataOfNode;
		/* */
		dataOfNode->address = DC;
		dataOfNode->name = *(word + 1);
		dataOfNode->are = 'A';

		/* */
		CreateAndaddToList(mhead,node);
		(_main_line*)(node->data) = dataOfNode;

		word++;
	} /* end of while */
	/* for '\0'  char. */
	IC++;
	_main_line* dataOfNode;
	/* */
	dataOfNode->address = DC;
	dataOfNode->name = '0';
	dataOfNode->are = 'A';
	/**/
	CreateAndaddToList(mhead, node);
	(_main_line*)(node->data) = dataOfNode;
	return mhead;
}


/* extern   not finished */
symbolList extern_line(symbolList* shead, char* word, int const line_num, char* line)
{

	node_pointer node;
	_symbol_line* extData;
	char* tempArray;
	char* temp = word;
	while (*word != '\n')
	{
			NextWord(temp);
			while (word <= temp)
			{

			}

		/*if (word != ' ' && word != '\t')
		*/
	}
	IC++;
	extData->symbol = curr_lebel;
	extData->value = 0;
	extData->type = 4;

	CreateAndaddToList(shead, node);
	(_main_line*)(node->data) = extData;

	return shead;
} /* End of func */
