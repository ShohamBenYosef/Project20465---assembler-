#include <stdio.h>
#include "file.h"
#include "error.h"


#define NUM_OF_CMD 16
#define MAX_DATA_NUM 4096
#define NUM_OF_REG 7


#define IsBlank(c) ((c) == ' ' || (c) == '\t')
#define NextWord(x) while (IsBlank(*(x))) (x)++ 


#define NewLebelNode(_label) _label = (Label*)malloc(sizeof(Label));\
	if (!_label) error_fatal(ErrorMemoryAlloc);\
	_label->label = NULL;\
	_label->line = 0;


#define NewMainNode(_node) _node = (LineData*)malloc(sizeof(LineData));\
	if (!_node) fatal_error(ErrorMemoryAlloc);\
	_node->address = 0;\
	_node->machine_code = 0;\
	_node->label = NULL;\
	_node->are = 0;


/**/
char* curr_lebel;
char* current_char;
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
} MachineCode;



/**
* 
*/
mainList extract_data(mainList* mhead, char* word, int const line_num, char* line);
/**
*
*/
mainList extract_string(mainList* mhead, char* word, int const line_num, char* line);