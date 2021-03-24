#ifndef ASM_H_
#define ASM_H_

#include "list.h"
#include <stdio.h>
#include "file.h"
#include "error.h"
#include "utils.h"
#include <math.h>
#include "commands.h"





char* tempWord[MAX_LINE_LENGTH];
int DC, IC, L;
extern file;

/* we dont need it */
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


typedef struct {
	Lebel* Shead;
	Line* Mhead;
	unsigned int errors;
	command cmd;
	char* file_name_base;
	FILE* file;
	/* Command and data counters. */
	unsigned int IC;
	unsigned int DC;
} ParserData;


ParserData parser_data;
/**
* A function that extracts the information after the word .data in a assembly line
*/
/*void extract_data(char* word, int const line_num);*/
/**
* A function that extracts the information after the word .string in a assembly line
*/
int extract_string(char* word, int const line_num, char* line);
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
int parse(FILE* file);
/**
*
*/
int BlankLine(char* line);


#endif