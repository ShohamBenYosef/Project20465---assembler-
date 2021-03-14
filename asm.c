
#include "asm.h"
#include "file.h"
#include "error.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h> /*for alphanomeric*/
#include <string.h>

char* curr_lebel[80];

int DCF, ICF; /* save DC and IC for the second round. */
mainList* mhead; /* main list head pointer*/
symbolList* shead; /* symbol list head pointer*/

const char* command_names[] = { "mov", "cmp", "add", "sub","lea", "clr","not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop" };


/* DATA*/
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
			error_log("Error, The line contain illegal number.", line_num);
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
		dataOfNode->lebel = data_num;
		dataOfNode->are = 'A';

		/* */
		CreateAndaddToList(mhead, node);
		(_main_line*)(node.data) = dataOfNode;

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

/* STRING */
mainList* extract_string(mainList* mhead, char* word, int const line_num, char* line)
{
	mainList node;
	char* curr_char;
	nextWord(word);

	if (*word != '"') {
		error_set("Error, there's no string ", line_num);
		return 0;
	}

	curr_char = line + strlen(line) - 1; /* current_char is now on the end of the currect line. */
	
	while (isBlank(curr_char)) curr_char--; /* set the pointer on the end of the string. */

	if (*(curr_char) != '"' || curr_char == word) { /* check if there is an argument. */
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
		dataOfNode->lebel = *(word + 1);
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
	dataOfNode->lebel = '0';
	dataOfNode->are = 'A';
	/**/
	CreateAndaddToList(mhead, node);
	(_main_line*)(node->data) = dataOfNode;
	return mhead;
}

/* extern!!!  -----   not finished */
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
	extData->lebel = curr_lebel;
	extData->value = 0;
	extData->type = 4;

	CreateAndaddToList(shead, node);
	(_main_line*)(node->data) = extData;

	return shead;
} /* End of func */

  /* check if the line start with LEBEL:.. */
char*  getLineLebel(char* line, int line_num)
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
	return NULL;
}

void extract_lebel(char* word, char* curr_char, int const line_num, char* line,Attributes type)
{
	Lebel* lebel;
	word = current_char;

	NextWord(word);

	if (!isalpha(*word))
	{
		error_log("Error, illigal char in Lebel ", line_num);
		return;
	}
	/* set pointer to the end of line and the move to*/
	curr_char = word;
	while (!isBlank(current_char))
		current_char++;
	/* build the node of lebel */
	newLebel(lebel);
	lebel->lebel = (char*)malloc(MAX_LINE_LENGTH + 1);
	if (!lebel->lebel)
		fatal_error(ErrorMemoryAlloc);
	
	strcpy(lebel->lebel, word);
	if (getLineLebel(lebel->lebel,line_num))
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

int parse()
{
	/* 1 */
	IC = 100, DC = 0; 
	Lebel* lebel;
	
	
	char* line; /*hod the string line*/
	int line_num=0; 
	char* word, * curr_char; /* pointer that help us to 'run' on the line*/
	/* nodes for the lists - main and symbol. */
	_symbol_line* symbol_node = NULL; 
	_main_line* main_node = NULL;

	int lebel_flag = 0, index = 0;
	/*?*/
	char cmd_type[NUM_OF_REG];

	while ((line = runOnLine())) /* 2*/
	{
		line_num++;

		if (strlen(line) > MAX_LINE_LENGTH)
			error_log("Error, line is too ", line_num);

		if (line != ';')
		{
			NewLabelNode(lebel);
			lebel->lebel = getLineLebel(line, line_num);
			if (lebel->lebel) /* if its lebel */
				lebel_flag = check_valid_lebel(lebel->lebel, line_num);
			
			/* ending of the first word */

			word = line;
			nextWord(word);

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

			current_char = word + 1;
			while (!IsBlank(*curr_char) && *curr_char != '\0')
				curr_char++;

			/*5*/
			/* if its not data or string so its a symbol line*/
			if (((!strncmp(word, ".data", 5) && (current_char - word) == 5 && *current_char != '/')
				|| (!strncmp(word, ".string", 7) && (current_char - word) == 7 && *current_char != '/'))
				&& lebel->lebel) {

				lebel->line = DC + 1;
				lebel->type = dataType;
				/* Add the label to the labels list. */
				shead = addToList(shead, lebel); /* check if its alredy in the list    T0D0 or change "CreateAndaddtolist" */
			}
			/* if its symbol line*/
			/*7*/

			/* Data line. */  /* i deleted  siman kria!!!---------------------   TODO*/
			if (strncmp(word, ".data", 5) && (current_char - word) == 5 && *current_char != '/') {
				extract_data_number(current_char, line_num);
				continue;
			}

			/* String line. */
			if (strncmp(word, ".string", 7) && (current_char - word) == 7 && *current_char != '/') {
				extract_string(mhead,current_char, line_num, line);
				continue;
			}
			/*8*/
			/*9*/
			/* Entry label declaration line. */
			if (strncmp(word, ".entry", 6) && (current_char - word) == 6 && *current_char != '/') {
				extract_label(word, current_char, line_num, line, entryType);
				continue;
			}
			/*10*/
			/* External label declaration line. */
			if (strncmp(word, ".extern", 7) && (current_char - word) == 7 && *current_char != '/') {
				extract_label(word, current_char, line_num, line, externType);
				continue;
			}
			/* add to main list */
			/* need to add func to check if the lebel is alredy exist in the list---------*/

			IC++;
			newMainNode(main_node);
			main_node->address = IC;
			main_node->lebel = lebel;
			main_node->are = 'A';

			/*add to symbol table */
			/* need to add func to check if the lebel is alredy exist in the list*/
			/* 11 */
			if (lebel->lebel) {
				lebel->type = codeType;
				lebel->line = DC + 1;
				shead = addToList(shead, lebel); /* check if its alredy in the list    T0D0 or change "CreateAndaddtolist" */
			}

			/* cmp the command with */
			while (index < NUM_OF_CMD)
			{
				strncmp(word, command_names[index], current_char - word);
				index++;
			}
			if (index == NUM_OF_CMD)
			{
				error_log("Error, Unknown command.\n", line_num);
				continue;
			}
			
			/* start to build the binary opcode*/
			/* need to add more thing to the bit field. - mayby we should usee more func..-----------------------------------*/
			main_node->bcode.opcode = index;
			
			/* to do V----------------------------------------------------------------------------------------------------------*/
			/* Find '/0' or /1 , assuming /0 is not followed by other options. */
			nextWord(curr_char);
			/* jmp to the start of the next word and Check what is the cmd*/
			cmd_type[0] = *curr_char;

			if (*curr_char != '\0')
			{
				curr_char++;
				nextWord(curr_char);

				cmd_type[1] = *curr_char;
				curr_char[2] = '\0';
			}
			/*^*/
			/* extract first operand*/
			NextWord(current_char);

			/* 13*/
			/* נתח את מבנה האופרנדים של ההוראה, וחשב מהו מס המילים הכולל שתופסת ההוראה בקוד מכונה ונקראה לו אל גדול    L*/
			/*14*/
			/* בניית קוד בינארי של המילה הראשונה, ןשל כל מילת-מידע נוספת המקודדת  אופרנד במיעון מיידי*/

		}/* end of if ';' */
	}/* end of while*/

	if (errors_count > 0)
		return 0;

	/* 18 */
	ICF = IC;
	DCF = DC;

	/* 19 */
	update_line_in_symbol_list();/* to do*/

	return 1;
	/* 17 */
}




int parse2(FILE* fp)
{
	char* line,* word;
	int ent_flag = 0, ext_flag = 0;
	Lebel* tmp_lebel = NULL;
	Lebel* fnd_lebel = NULL;
	int address, line_num = 0;
	/* nodes for the lists - main and symbol. */
	_symbol_line* symbol_node = NULL;
	_main_line* main_node = NULL;
	int entry_flag = 0, extern_flag = 0;

	/* 1 */
	while ((line = runOnLine()))\
	{
		if (line != ';')
		{
			line_num++;

			nextWord(word);
			NewLabelNode(tmp_lebel);
			/* 2 */
			tmp_lebel->lebel = getLineLebel(line, line_num);
			fnd_lebel = search_in_list(symbol_node, tmp_lebel, &lebel_compere);
			free(tmp_lebel);

			if (!fnd_lebel)
			{
				error_log("Error, lebel not found on the sec ", line_num);
				continue;
			}
			word = line + strlen(fnd_lebel->label) + 1;
			NextWord(word);
			

			/* 3 */
			if ((!strncmp(word, ".data", 5) && (current_char - word) == 5 && *current_char != '/')
				|| (!strncmp(word, ".string", 7) && (current_char - word) == 7 && *current_char != '/'))
			{
				continue;
			}
			/* 4 */
			if (!strncmp(word, ".entry", 6) && (current_char - word) == 6 && *current_char != '/') 
			{
				/* 5 */
				/* לא לשכוח לעשות פונקציה שמטפלת בסעיף 5 - - אולי כדאי לראות הרצאה..*/
				entry_flag++;
				continue;
			}
			if (!strncmp(word, ".extern", 7) && (current_char - word) == 7 && *current_char != '/')
			{
				extern_flag++; 
				continue;
			}
			/* 6 */



		}/* end of condition */
	}/* end of while loop */


	if (entry_flag > 0)
	{
		openExtEntFile("ent", shead); /* TODO */
	}
	if (extern_flag > 0)
	{
		openExtEntFile("ext", shead); /* TODO */
	}

	trans()


}/* end of func */



/*----------------Todo function   -------------------------------------------------------------   */
addEntryLebel()
{

}

int lebel_compere(void* l1, void* l2)
{
	Lebel* first_lebel = l1;
	Lebel* second_lebel = l2;
	return strcmp(first_lebel->lebel, second_lebel->lebel);
}

openExtEntFile()
{

}

/*const Command commands[] = {
	{0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0},
	{0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0, 0},
	{0, 1, 0, 1, 1, 0, 1, 0 ,0 ,0 ,0, 0},
	{0, 1, 0, 1, 1, 0, 1, 1 ,0 ,0 ,0, 0},
	{0, 1, 0, 1, 1, 1, 0, 0 ,0 ,0 ,0, 0},
	{0, 1, 0, 1, 1, 1, 0, 1 ,0 ,0 ,0, 0},
	{1, 0, 0, 1, 1, 0, 1, 0 ,0 ,0 ,0, 0},
	{1, 0, 0, 1, 1, 0, 1, 1 ,0 ,0 ,0, 0},
	{1, 0, 0, 1, 1, 1, 0, 0 ,0 ,0 ,0, 0},
	{1, 1, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0, 0},
	{1, 1, 0, 1, 0, 0, 0, 0 ,0 ,0 ,0, 0},
	{1, 1, 1, 0, 0, 0, 0, 0 ,0 ,0 ,0, 0},
	{1, 1, 1, 1, 0, 0, 0, 0 ,0 ,0 ,0, 0},
};------------------------------------------- TODO*/


addToList()
{


}

void update_line_in_symbol_list(){}

void printObjectFile(const char* file_name)
{
	FILE* fpExt, * fpOb, * fpEnt;
	
	fpExt = open_file(full_file_name, ExternFileEnding, "w");
	fpOb = open_file(full_file_name, ObjectFileEnding, "w");
	fpEnt = open_file(full_file_name, EntryFileEnding, "w");

	fprintf(fp,"\t\t\t%X\t%X\n", IC, DC);
	mainList* temp = mhead;
	while (temp) {
		fprintf(fp, "%d\t%04X", temp->data->address, printBCode(temp.data.bcode));
		temp = temp->next;
	} 

	
	
	close_file(file_name, ObjectFileEnding);
}

void close_file(const char* file_name, char* ending)
{

}