#ifndef COMMANDS_H_
#define COMMANDS_H_

#include "utils.h"
#define numOfcommands 15
#define lengthOfCommands 3
#define NewCommandLine(cmd) cmd = (Command*)malloc(sizeof(Command));\
	if (!cmd) fatal_error(ErrorMemoryAlloc);\
	cmd->first_operand = NULL;\
	cmd->second_operand = NULL;\
	cmd->numOfCommand = 0;\
	cmd->address = 0;

typedef enum
{
	immediateOperand,
	SymbolOperand,
	RealativeOperand,
	RegisterOperand
} operandType;

typedef union
	{
		int immediateNum; /* Number for immediate addres */
		char* Symbol; /* If there is a symbol in the operand */
		char numOfRegister; /* Number of register in operand - for register type */
} operandValue; /* What inside the operand */



typedef struct
{
    	operandType type; /* Type of operand */
    	union
    	{
    		int immediateNum; /* Number for immediate addres */
    		char* Symbol; /* If there is a symbol in the operand */
    		int numOfRegister; /* Number of register in operand - for register type */
    } operandValue; /* What inside the operand */
} operand;

/*
 Struct of a command  with all the deatils
 */
typedef struct
{
	int numOfCommand; /* number of the command from the commandsTypes */
	operand FirstOperand; /* origin operand */
	operand SecondOperand; /* destination operand */
	int address; /* the address of command */
} command;





typedef struct
{
	char* name; /* Command name*/
	int opcode; /* Command opcode */
	int funct; /* Command function code */
	int numOfOpreand; /* Number of operands expected with command */
	unsigned int srcImidiateadAdress : 1;
	unsigned int srcDirectAddress : 1;
	unsigned int srcRelativeAddress : 1;
	unsigned int srcDirectRegAdress : 1;
	unsigned int destImidiateAddress : 1;
	unsigned int destDirectAddress : 1;
	unsigned int destRelativeAddress : 1;
	unsigned int destDirectRegAdress : 1;

} CommandsType;






command parseCommand(char* line,const int line_num);

operand getFirstOperand(char* currentChar,const int line_num);

int typeOfCommand(char* word,const int line_num);

operand parseOperand(char* currentChar,const int line_num);

operand getSecondOperand(char* line,const int line_num);

/*void pushCommandToTable(command lineCommand, Line newLine, int addres);*/

int checkOperands(const command* newCommand,const int line_num);

#endif
