#ifndef ASM_H_
#define ASM_H_

#include "list.h"
#include <stdio.h>
#include "file.h"
#include "error.h"
#include "utils.h"


/* build new lebel node */
#define NewLebelNode(_lebel) _lebel = (Lebel*)malloc(sizeof(Lebel));\
	if (!_lebel) fatal_error(ErrorMemoryAlloc);\
	_lebel->lebel = (char*)malloc(sizeof(char));\
	if(!lebel) fatal_error(ErrorMemoryAlloc);\
	_lebel->line = 0;\
	_lebel->type = 0;\
	_lebel->next = NULL;





char* tempWord[MAX_LINE_LENGTH];
int DC, IC, L;
extern fp;



typedef struct {
	char* lebel;
	int IC;
	int DC;
	char* command;
	char* arg1;
	char* arg2;
	int is_instruction : 1;
	int is_entry : 1;
}LineData;



/**
* A function that extracts the information after the word .data in a assembly line
*/
Line extract_data(char* word, int const line_num);
/**
* A function that extracts the information after the word .string in a assembly line
*/
Line* extract_string(char* word, int const line_num, char* line);
/**
* A function that extracts the next Lebel.
*/
void extract_lebel(char* word, char* curr_char, int const line_num, char* line, Attributes type);
/**
* A function that extracts the first Lebel is the line.
*/
char* getLineLebel(char* line, int line_num);
/**
*
*/
int check_valid_lebel(char* lebel, int line_num);
/**
* A method that parses Line after Line in the assembly file. (First round in the algorithm)
*/
int parse();




#endif