#include <stdio.h>
#include "file.h"
#include "error.h"


#define MAX_DATA_NUM 4096


#define IsBlank(c) ((c) == ' ' || (c) == '\t')
#define NextWord(x) while (IsBlank(*(x))) (x)++ 


#define NewLabel(_label) _label = (Label*)malloc(sizeof(Label));\
	if (!_label) error_fatal(ErrorMemoryAlloc);\
	_label->label = NULL;


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