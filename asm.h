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
	
/* build new main list node */
#define NewMainNode(_node) _node = (Line*)malloc(sizeof(Line));\
	if (!_node) fatal_error(ErrorMemoryAlloc);\
	_node->label =NULL;\
	_node->address = 0;\
	_node->is_instruction = 0;\
	_node->are = '0';\
	_node->bcode = 0;\
	_node->next = NULL;
	/*_node->machine_code = 0;\*/


/**/

char* tempWord[MAX_LINE_LENGTH];
int DC, IC, L;
extern fp;



/**
* Hold the 12 bits.  ------- bits field ---------
*/
typedef struct {
	
	unsigned int source : 2;
	unsigned int target : 3;
	unsigned int func : 4;
	unsigned int opcode : 4;

	unsigned int allBits : 12;

} MachineCode;



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
* 
*/
Line extract_data(char* word, int const line_num);
/**
*
*/
Line* extract_string(char* word, int const line_num, char* line);
/**
*
*/
void extract_lebel(char* word, char* curr_char, int const line_num, char* line, Attributes type);
/**
*
*/
char* getLineLebel(char* line, int line_num);
/**
*
*/
int check_valid_lebel(char* lebel, int line_num);
/**
*
*/
int parse();
/**
*
*/
int parse2(FILE* fp);
/**
*
*/
int lebel_compere(void* l1, void* l2);



