#include <stdio.h>
#include "file.h"
#include "error.h"

char* current_char;
int DC, IC, L;
extern fp;

#define MAX_LINE_LENGTH 81
#define MAX_DATA_NUM 4096

#define IsBlank(c) ((c) == ' ' || (c) == '\t')
#define NextWord(x) while (IsBlank(*(x))) (x)++ 


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