#include "utils.h"
#include "asm.h"
#include "file.h"
#include "error.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h> /*for alphanomeric*/
#include <string.h>

#pragma warning(disable : 4996)


int DCF, ICF; /* save DC and IC for the second round. */
int IC, DC;


const char* command_names[] = { "mov", "cmp", "add", "sub","lea", "clr","not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop" };

extern main_list_head, lebel_list_head;

/* DATA*/
Line extract_data(char* word, int const line_num)
{
	int param_count = 0, comma_count = 0;
	long data_num = 0;
	short its_negative = 0;
	Line* node;
	char* first_char;


	while (*word != '\n')
	{
		/* if(*word == '\0') continue; */
		NextWord(word);

		/* if the argument is empty. */
		if (*word == '\0' && param_count == 0)
			error_log("Error, There is no data", line_num);

		/* illigal characters and words */
		if (!isdigit(*word) && *word != '+' && *word != '-') {
			error_log("Error, The line contain illegal number.", line_num);
			continue;
		}

		word++;

		while (!IsBlank(*word) && *word != '\0' && *word != ',')
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
		DC++; /* the actual address*/
		newLineNode(&node, DC, 1, 'A');
		node->lebel = NULL;
		node->bcode.allBits = data_num;

		addToMainList(main_list_head, node);

		NextWord(*word);

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

/* STRING */
Line* extract_string(char* word, int const line_num, char* line)
{
	Line* node;
	char* curr_char;
	/* move to start*/
	NextWord(word);

	/* check if its realy string */
	if (*word != '"') {
		error_log("Error, there's no string ", line_num);
		return main_list_head;
	}

	curr_char = line + strlen(line) - 1; /* current_char is now on the end of the currect line. */

	while (IsBlank(curr_char)) curr_char--; /* set the pointer on the end of the string. */

	if (*(curr_char) != '"' || curr_char == word) { /* check if there is an argument. and if its string */
		error_log("Error, String expected after \".string\".\n", line_num);
		return 0;
	}
	/* adding line in table for every char in the string.*/
	while (word + 1 < curr_char)
	{
		DC++; /* the actual address*/
		/* */
		newLineNode(&node, DC, 1, 'A');
		node->lebel = NULL;
		node->bcode.allBits = *(word + 1);

		addToMainList(main_list_head, node);

		word++;
	} /* end of while */
	/* for '\0'  char. */
	DC++;

	newLineNode(&node, DC, 1, 'A');
	node->lebel = NULL;
	node->bcode.allBits = 0;

	addToMainList(main_list_head, node);

	return main_list_head;
}
/* Ext and Ent */
void extract_lebel(char* word, char* curr_char, int const line_num, char* line, Attributes type)
{
	Lebel* lebel;
	word = curr_char;

	/* set pointer to the start of the next word */
	NextWord(word);

	if (!isalpha(*word))
	{
		error_log("Error, illigal char in Lebel ", line_num);
		return;
	}

	/* set pointer to the end of line and the move to*/
	curr_char = word;

	while (!IsBlank(curr_char))
		curr_char++;

	/* build the node of lebel */
	NewLebelNode(lebel);
	lebel->lebel = (char*)malloc(MAX_LINE_LENGTH + 1);
	if (!lebel->lebel)
		fatal_error(ErrorMemoryAlloc);

	strcpy(lebel->lebel, word);
	if (getLineLebel(lebel->lebel, line_num))
	{
		/*Attributes*/
		if (type == externType)
		{
			lebel->type = externType;
			lebel->line = 0;
			/* add to symbol list n  ---------------------------*/
		}
		else if (type == entryType)
		{
			lebel->type = entryType;
			lebel->line = line_num;
			/* add to symbol list -----------------------------*/
		}
	}
}

/* check if the line start with 'LEBEL:' */
char* getLineLebel(char* line, int line_num)
{
	int length = 0;
	char* lebel;
	const char* temp = line;

	lebel = (char*)malloc(MAX_LINE_LENGTH + 1);
	if (!lebel)
		fatal_error(ErrorMemoryAlloc);

	/* check capital letters. */
	if (!isalpha(*temp))
		return NULL;

	while (isalnum(*temp) && length < MAX_LINE_LENGTH)
	{
		temp++;
		length++;
	}

	if (line[length] == ':') {
		strncpy(lebel, line, length);
		lebel[length] = '\0';
		return lebel;
	}
	free(lebel);
	return NULL;
}
/* get the lebel - use after extern and entry */
/**
* יש מצב שלא נצטרך
*/
int check_valid_lebel(char* lebel, int line_num)
{
	int index;
	char* word = lebel;
	while (!IsBlank(word))
	{
		if (!isalpha(word) || !isalnum(word))
		{
			error_log("Error, illigal char in lebel ", line_num);
			return 0;
		}
		word++;
	}
	if (word != ':')
	{
		error_log("Error, illigal char in lebel ", line_num);
		return 0;
	}
	return 1;
}

int parse(FILE* fp)
{
	/* 1 */
	IC = 99, DC = 0;

	Lebel* lebel; /* Lebel line */

	Line* node; /* main node line */

	char* line; /*hod the string line*/

	int line_num = 0; /* line count */

	/* pointer that help us to 'run' on the line*/
	char* word, * curr_char;

	/* nodes for the lists - main and symbol. */
	Lebel* symbol_node = NULL;
	Line* main_node = NULL;

	int lebel_flag = 0, index = 0;

	/* command type */
	char cmd_type[NUM_OF_REG];
	int commandNum = 0;


	/* check if there is a line */
	while (line = runOnLine(fp)) /* 2*/
	{
		line_num++;

		if (strlen(line) > MAX_LINE_LENGTH)
			error_log("Error, line is too ", line_num);

		if (line != ';')
		{

			/* get the lebel of the line */
			NewLebelNode(lebel);
			lebel->lebel = getLineLebel(line, line_num);
			if (lebel->lebel) /* if its lebel */
				lebel_flag = check_valid_lebel(lebel->lebel, line_num);
			/* ending of the first word */


			word = line;
			NextWord(word);

			/* Empty line. */
			if (*word == '\0')
			{
				free(lebel);
				continue;
			}
			/* if the first word is lebel so jmp to the beginning of the next word. */
			if (lebel->lebel) {
				word = line + strlen(lebel->lebel) + 1;
				NextWord(word);
			}
			/* */
			if (*word == '\0' && lebel->lebel)
			{
				error_log("Error, only lebel in line ", line_num);
				free(lebel);
				continue;
			}

			curr_char = word + 1;
			while (!IsBlank(*curr_char) && *curr_char != '\0')
				curr_char++;

			/*5*/
			/* if its not data or string so its a symbol line*/
			if (((!strncmp(word, ".data", 5) && (curr_char - word) == 5 && *curr_char != '/')
				|| (!strncmp(word, ".string", 7) && (curr_char - word) == 7 && *curr_char != '/'))
				&& lebel->lebel) {

				lebel->line = DC + 1;
				lebel->type = dataType;
				/* Add the label to the labels list. */
				addToSymbolList(lebel_list_head, lebel); /* check if its alredy in the list    T0D0 or change "CreateAndaddtolist" */
			}
			/* if its symbol line*/
			/*7*/

			/* Data line. */  /* i deleted  siman kria!!!---------------------   TODO*/
			if (strncmp(word, ".data", 5) && (curr_char - word) == 5 && *curr_char != '/') {
				extract_data(curr_char, line_num);
				continue;
			}

			/* String line. */
			if (strncmp(word, ".string", 7) && (curr_char - word) == 7 && *curr_char != '/') {
				extract_string(curr_char, line_num, line);
				continue;
			}
			/*8*/
			/*9*/
			/* Entry label declaration line. */
			if (strncmp(word, ".entry", 6) && (curr_char - word) == 6 && *curr_char != '/') {
				extract_lebel(word, curr_char, line_num, line, entryType);
				continue;
			}
			/*10*/
			/* External label declaration line. */
			if (strncmp(word, ".extern", 7) && (curr_char - word) == 7 && *curr_char != '/') {
				extract_lebel(word, curr_char, line_num, line, externType);
				continue;
			}
			/* add to main list */
			/* need to add func to check if the lebel is alredy exist in the list---------*/

			IC++;
			newLineNode(&node, IC, 0, 'A');
			node->lebel = lebel;

			/*add to symbol table */
			/* need to add func to check if the lebel is alredy exist in the list*/
			/* 11 */
			if (lebel->lebel) {
				lebel->type = codeType;
				lebel->line = DC + 1;
				addToSymbolList(lebel_list_head, lebel); /* check if its alredy in the list    T0D0 or change "CreateAndaddtolist" */
			}

			/* check if too much */
			if (strlen(line) > MAX_LINE_LENGTH) {
				error_log("Error, Line length is over 81 characters.\n", line_num);
				continue;
			}
			/****************************************************************
			*******************************************************************/
			/* cmp the command with */
			/*commandNum = typeOfCommand(*word);*/

			/* start to build the binary opcode*/
			/* need to add more thing to the bit field. - mayby we should usee more func..-----------------------------------*/


			/* to do V----------------------------------------------------------------------------------------------------------*/
			/* Find '/0' or /1 , assuming /0 is not followed by other options. */
			NextWord(curr_char);
			/* jmp to the start of the next word and Check what is the cmd*/
			cmd_type[0] = *curr_char;

			if (*curr_char != '\0')
			{
				curr_char++;
				NextWord(curr_char);

				cmd_type[1] = *curr_char;
				curr_char[2] = '\0';
			}
			/*^*/
			/* extract first operand*/
			NextWord(curr_char);

			/* 13*/
			/* נתח את מבנה האופרנדים של ההוראה, וחשב מהו מס המילים הכולל שתופסת ההוראה בקוד מכונה ונקראה לו אל גדול    L*/
			/*14*/
			/* בניית קוד בינארי של המילה הראשונה, ןשל כל מילת-מידע נוספת המקודדת  אופרנד במיעון מיידי*/

		}/* end of if  */
			/****************************************************************
			*******************************************************************/
	}/* end of while*/

	if (errors_count > 0)
		return 0;

	/* 18 */
	ICF = IC;
	DCF = DC;

	/* 19 */
	/*update_line_in_symbol_list(); to do*/

	return 1;
	/* 17 */
}
