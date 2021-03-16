#include <stdio.h>
#include "file.h"
#include "error.h"


#define NUM_OF_COMMANDS 16
#define MAX_DATA_NUM 4096
#define NUM_OF_REG 7


#define IsBlank(c) ((c) == ' ' || (c) == '\t')
#define NextWord(x) while (IsBlank(*(x))) (x)++ 


/* build new lebel node */
#define NewLebelNode(_node) _label = (Label*)malloc(sizeof(Label));\
	if (!_label) error_fatal(ErrorMemoryAlloc);\
	_label->label = (char*)malloc(sizeof(chaar);\
	if(!lebel) fatal_error(ErrorMemoryAlloc);\
	_label->line = 0;\
	_lebel->type = 0:\
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




