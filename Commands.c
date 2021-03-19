/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby,
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "main.h"
#define numOfcommands 15

command parseCommand(char* line, );

void getFirstOperand(char* currentChar);

void parseOperand(char*currentChar,int operandLength);

int typeOfCommand(char* word);

void parseOperand(char* currentChar,int operandLength);

void operand getSecondOperand(char* line);

void pushCommandToTable(command lineCommand, line newLine, int addres)

int checkOperands(const command* newCommand);


const commands commandTypes[numOfcommands] = {
    {"mov", 0, 0, 2, 1, 1, 0, 1, 0, 1, 0, 1},
    {"cmp", 1, 0, 2, 1, 1, 0, 1, 1, 1, 0, 1},
    {"add", 2, 1, 2, 1, 1, 0, 1, 0, 1, 0, 1},
    {"sub", 2, 2 ,2, 1, 1, 0, 1, 0, 1, 0, 1},
    {"lea", 4, 0 ,2, 0, 1, 0, 0, 0, 1, 0, 1},
    {"clr", 5, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1},
    {"not", 5, 2, 1, 0, 0, 0, 0, 0, 1, 0, 1},
    {"inc", 5, 3, 1, 0, 0, 0, 0, 0, 1, 0, 1},
    {"dec", 5, 4, 1, 0, 0, 0, 0, 0, 1, 0, 1},
    {"jmp", 9, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0},
    {"bne", 9, 2, 1, 0, 0, 0, 0, 0, 1, 1, 0},
    {"jsr", 9, 3, 1, 0, 0, 0, 0, 0, 1, 1, 0},
    {"red", 12, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
    {"prn", 13, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1},
    {"rts", 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {"stop", 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};














void parseCommand(char* line )
{
	char* nameOfCommand;
	command newCommand;
	int operandsToParse= commandTypes[newCommand.numOfCommand].operand_num;

	if (is_symbol)
	{
		nameOfCommand = getWord(line, 1, file_reader_context);
	}
	else
	{
		nameOfCommand = getWord(line, 0, file_reader_context);
	}

	/* Ged id in command types */
	newCommand.numOfCommand = typeOfCommand(nameOfCommand);

	/* if there isnt match */
	if (newCommand.numOfCommand == -1)
	{
		log_error("there isnt a legal command on line");
		return newCommand;
	}

	/* push the pointer to the start of operands */
	line = strstr(line, nameOfCommand) + strlen(nameOfCommand);

	/* parse the operands, operands type start with 0 if there arent exist */

	newCommand.firstOperand.type =NULL;
	newCommand.secondOperand = NULL;
	switch (commandTypes[newCommand.numOfCommand].operand_num && operandsToParse)
	{
	case 0:
		operandsToParse = NULL;
	case 1:
		newCommand.secondOperand = parseOperand(line);
		operandsToParse = NULL;
	case 2:
		newCommand.firstOperand = getFirstOperand(line);
		newCommand.secondOperand = getSecondOperand(line);
		operandsToParse = NULL;
	}
}

const commands commandTypes[numOfcommands] = {
	{"mov", 0, 0, 2, 1, 1, 0, 1, 0, 1, 0, 1},
	{"cmp", 1, 0, 2, 1, 1, 0, 1, 1, 1, 0, 1},
	{"add", 2, 1, 2, 1, 1, 0, 1, 0, 1, 0, 1},
	{"sub", 2, 2 ,2, 1, 1, 0, 1, 0, 1, 0, 1},
	{"lea", 4, 0 ,2, 0, 1, 0, 0, 0, 1, 0, 1},
	{"clr", 5, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1},
	{"not", 5, 2, 1, 0, 0, 0, 0, 0, 1, 0, 1},
	{"inc", 5, 3, 1, 0, 0, 0, 0, 0, 1, 0, 1},
	{"dec", 5, 4, 1, 0, 0, 0, 0, 0, 1, 0, 1},
	{"jmp", 9, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0},
	{"bne", 9, 2, 1, 0, 0, 0, 0, 0, 1, 1, 0},
	{"jsr", 9, 3, 1, 0, 0, 0, 0, 0, 1, 1, 0},
	{"red", 12, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
	{"prn", 13, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1},
	{"rts", 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{"stop", 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

void pushCommandToTable(command lineCommand, line newLine, int addres)
{
	newLine.bcode.separateBits.func = commandsTypes[lineCommmand.numOfCommand].funct;
	newLine.bcode.separateBits.opcode = lineCommmand.numOfCommand;
	newLine.bcode.separateBits.source = lineCommmand.firstOperand.type;
	newLine.bcode.separateBits.target = lineCommmand.secondOperand.type;
}

int typeOfCommand(char* word)
{

	int i;
	/* Search if match to a command in the commands types */
	for (i = 0; i < numOfcommands; ++i)
	{
		if (strcmp(word, commandTypes[i].name) == 0)
			return i;
	}
	/*if there isnt a match*/
	return -1;
}

void parseOperand(char* line, int operandLength)
{

	{

		operand opr;
		int i = 0;
		int j;
		
		opr.type = 0;
		opr.operandValue.immediateNum = 0;

		printf("%c \n", line[i]);
		/* Immediate case */
		if (line[i] == '#')
		{
			printf("yes its statrs with #\n");
			i++;
			printf("check if have sign\n");
			if (line[i] == '+' || line[i] == '-' || isdigit(line[i]))
			{
				j = i + 1;
				for (; j < operandLength; j++)
				{
					printf("check if number\n");
					if (!isdigit(line[j]))
					{
						
						log_error("there isn't a legal operand");
						return opr; 
					}
				}
				opr.type = immediateOperand;
				opr.operandValue.immediateNum = atoi(&line[i]);
				printf("this is an imidate operande");
				return;
			}
			
			log_error("there isn't a legal operand");
			return;
		}

		/* if its start like relative operand */
		if (line[i] == '&')
		{
			if (!isalpha(line[i + 1]))
			{
				log_error("there isn't a legal operand");
				return opr;
			}

			j = i + 2;
			for (; j < strlen(line); j++)
			{
				if (!isalpha(line[j]) && !isdigit(line[j]))
				{
					log_error("there isn't a legal operand");
					return opr;
				}
			}

			opr.type = RealativeOperand;
			opr.operandValue.SymbolOperand = (char*)malloc(sizeof(char) * strlen(&line[i + 1]) + 1);
			strcpy(opr.operandValue.SymbolOperand, &line[i + 1]);
			return opr;
		}

		/* if its start like relative register operand */
		if (line[i] == 'r' && strlen(&line[i]) == 2 && isdigit(line[i + 1]))
		{
			const int registerNum = atoi(&line[i + 1]);
			if (registerNum >= 0 && registerNum <= 7)
			{
				opr.type = RegisterOperand;
				opr.operandValue.numOfRegister = registerNum;
				return opr;
			}

		}

		/*if its can be a symbol */
		if (!isalpha(line[i]))
		{
			log_error("there isn't a legal operand");
			return opr;
		}

		j = i + 1;
		for (; j < strlen(line); j++)
		{
			if (!isalpha(line[j]) && !isdigit(line[j]))
			{
				log_error("there isn't a legal operand");
				return opr;
			}
		}

		opr.type = SymbolOperand;
		opr.operandValue.SymbolOperand = (char*)malloc(sizeof(char) * strlen(&line[i]) + 1);
		strcpy(opr.operandValue.SymbolOperand, &line[i]);
		return opr;*/
	}
}


void getFirstOperand(char* line)
{
	operand opr;
	int operandLength = 0;
	int i;


	opr.type = 0;
	opr.operandValue.immediateNum = 0;
	i = 0;
	/* Skip white spaces and tabs  til  its find the start of the operand*/
	while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
	{
		line++;
	}

	if (line[i] == '\0')
	{
		error("there is no opreand after command");
		

	}

	/* length of the  operand */

	while (line[i] != ' ' && line[i] != '\t' && line[i] != ',' && line[i] != '\0')
	{
		operandLength++;
		i++;
	}

	if (line[i] == '\0')
	{
		log_error("Required operand not found");
		
	}




	printf("sending to parse\n");
	operandStr = (char*)malloc(sizeof(char) * (operandLength + 1));

	strncpy(operandStr, &line[i - operandLength], operandLength);
	operandStr[operandLength] = '\0';

	opr = parseOperand(operandStr);

	free(operandStr);

	return opr;

}

operand get_second_operand(char* line)
{
	operand opr;
	int i;

	opr.type = 0;
	opr.operand_content.immediateNum = 0;

	/* go to the start of the second operand */
	i = 0;
	while (line[i] != ',' && line[i] != '\0')
	{
		i++;
	}

	if (line[i] == '\0')
	{
		log_error("there is need to be second opernd");
		return opr;
	}

	return parseOperand(&line[i + 1]);
}

int checkOperands(const command* newCommand)
{
	if (commandTypes[newCommand->commandNum].numOfOperand == 2)
	{
		if (!(commandTypes[newCommand->numOfCommand].allowed_org_types
			& (1 << newCommand->operand1.type)))
		{
			return 0;
		}
	}

	if (commandTypes[newCommand->newCommandruction_type_id].numOfoperand > 0)
	{
		if (!(commandTypes[newCommand->newCommandruction_type_id].allowed_dest_types
			& (1 << newCommand->operand2.type)))
		{
			return 0;
		}
	}

	return 1;
}





/*void pushCommandLine(Line newLine, command lineCommmand);
void checkOperandForTable(command lineCommmand);
void pushOperandLine( operand lineOperand);
int main()
{
   Line newLine;
   command lineCommmand;
   pushCommandLine(newLine, lineCommmand);
     return 0;
}

checkOperandForTable(command lineCommmand)
{
    switch(commandsTypes[lineCommmand.numOfCommand].numOfOpreand)
    {
        case 0:
            break;
        case 1:
              pushOperandLine(lineCommmand.firstOperand); 
              break;
        case 2:
            {
                pushOperandLine(lineCommmand.firstOperand); 
                pushOperandLine(lineCommmand.secondOperand); 
                break;
    }       }
}

void pushCommandLine(Line newLine, command lineCommmand)
{
    lineCommmand.numOfCommand=3;
  
   lineCommmand.firstOperand.type=1;
   lineCommmand.secondOperand.type=2;
   newLine.bcode.separateBits.func=commandsTypes[lineCommmand.numOfCommand].funct;
   newLine.bcode.separateBits.opcode=lineCommmand.numOfCommand;
   newLine.bcode.separateBits.source=lineCommmand.firstOperand.type;
   newLine.bcode.separateBits.target=lineCommmand.secondOperand.type;
   
   checkOperandForTable(lineCommmand);
  printf("%d\n",newLine.bcode.separateBits.opcode);
  printf("%d\n",newLine.bcode.separateBits.func);
  printf("%d\n",newLine.bcode.separateBits.source);
  printf("%d\n",newLine.bcode.separateBits.target);
  
}
void pushOperandLine( operand lineOperand)
{
    lineOperand.operandValue.numOfRegister=7;
    Line operandLine;
    switch(lineOperand.type)
    {
        case ImmediateOperand:
            operandLine.bcode.allBits=lineOperand.operandValue.immediateNum;
            break;
        case DirectOperand:
        /*need to do*/
            break;
        case RelativeOperand:
         /*need to do*/
       /*     break;
        case RegisterOperand:
            operandLine.bcode.allBits=lineOperand.operandValue.numOfRegister;
            printf("%d",operandLine.bcode.allBits);
    } 
}*/
