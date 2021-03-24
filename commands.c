#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "file.h"
#include "error.h"
#include "utils.h"
#include "commands.h"
#include "list.h"

const CommandsType commandTypes[numOfcommands] = {
	{"mov", 0, 0, 2, {1, 1, 0, 1}, {0, 1, 0, 1} },
	{"cmp", 1, 0, 2, {1, 1, 0, 1}, {1, 1, 0, 1}},
	{"add", 2, 1, 2, {1, 1, 0, 1}, {0, 1, 0, 1}},
	{"sub", 2, 2 ,2, {1, 1, 0, 1}, {0, 1, 0, 1}},
	{"lea", 4, 0 ,2, {0, 1, 0, 0}, {0, 1, 0, 1}},
	{"clr", 5, 1, 1, {0, 0, 0, 0}, {0, 1, 0, 1}},
	{"not", 5, 2, 1, {0, 0, 0, 0}, {0, 1, 0, 1}},
	{"inc", 5, 3, 1, {0, 0, 0, 0}, {0, 1, 0, 1}},
	{"dec", 5, 4, 1, {0, 0, 0, 0}, {0, 1, 0, 1}},
	{"jmp", 9, 1, 1, {0, 0, 0, 0}, {0, 1, 1, 0}},
	{"bne", 9, 2, 1, {0, 0, 0, 0}, {0, 1, 1, 0}},
	{"jsr", 9, 3, 1, {0, 0, 0, 0}, {0, 1, 1, 0}},
	{"red", 12, 0, 1,{ 0, 0, 0, 0}, {0, 1, 0, 1}},
	{"prn", 13, 0, 1,{ 0, 0, 0, 0}, {1, 1, 0, 1}},
	{"rts", 14, 0, 0,{ 0, 0, 0, 0}, {0, 0, 0, 0}},
	{ "stop", 15, 0, 0,{ 0, 0, 0, 0}, {0, 0, 0, 0 }}
};


/*
int pushCommandToTable(command newCommand, Line newLine, int address)
{

	newLine.bcode.separateBits.func = commandsTypes[newCommand.numOfCommand].funct;
	newLine.bcode.separateBits.opcode = newCommand.numOfCommand;
	newLine.bcode.separateBits.source = newCommand.firstOperand.type;
	newLine.bcode.separateBits.target = newCommand.secondOperand.type;
	switch (commandsTypes[newCommand.numOfCommand].numOfOperand)
	{
		case 0:
			break;
		case 1:
		{
			pushOperandToTable(newCommand.FirstOperand);
			break;
		}
		case 2:
		{
			pushOperandToTable(newCommand.FirstOperand);
			address++
				pushOperandToTable(newCommand.secondOperand, line);
			address++
		}
		return addres;
	}
}
void pushOperandToTable(operand opr)
{
	Line* newLine;
	newLineNode(newLine, address,  instruction, ARE)
}*/
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


operand parseOperand(char* line, int line_num)
{

	{

		operand opr;
		int operandLength = strlen(line);
		int i = 0;
		int j;

		opr.type = 0;
		opr.operandValue.immediateNum = 0;

		/* Immediate case */
		if (line[i] == '#')
		{
			i++;
			
			if (line[i] == '+' || line[i] == '-' || isdigit(line[i]))
			{
				j = i + 1;
				for (; j < operandLength; j++)
				{
					if (!isdigit(line[j]))
					{
						error_log("there isn't a legal operand", line_num);
						return opr;
					}
				}
				opr.type = immediateOperand;
				opr.operandValue.immediateNum = atoi(&line[i]);
				return opr;
			}

			error_log("there isn't a legal operand", line_num);
			return;
		}

		/* if its start like relative operand */
		if (line[i] == '&')
		{
			if (!isalpha(line[i + 1]))
			{
				error_log("there isn't a legal operand", line_num);
				return opr;
			}

			j = i + 2;
			for (; j < strlen(line); j++)
			{
				if (!isalpha(line[j]) && !isdigit(line[j]))
				{
					error_log("there isn't a legal operand", line_num);
					return opr;
				}
			}

			opr.type = RealativeOperand;
			opr.operandValue.Symbol = (char*)malloc(sizeof(char) * strlen(&line[i + 1]) + 1);
			strcpy(opr.operandValue.Symbol, &line[i + 1]);
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
			error_log("there isn't a legal operand", line_num);
			return opr;
		}

		j = i + 1;
		for (; j < strlen(line); j++)
		{
			if (!isalpha(line[j]) && !isdigit(line[j]))
			{
				error_log("there isn't a legal operand", line_num);
				return opr;
			}
		}

		opr.type = SymbolOperand;
		opr.operandValue.Symbol = (char*)malloc(sizeof(char) * strlen(&line[i]) + 1);
		strcpy(opr.operandValue.Symbol, &line[i]);
		return opr;
	}
}


operand getFirstOperand(char* line, const int line_num)
{
	char* operandStr;
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
		error_log("there is no opreand after command", line_num);


	/* length of the  operand */
	while (line[i] != ' ' && line[i] != '\t' && line[i] != ',' && line[i] != '\0')
	{
		operandLength++;
		i++;
	}

	if (line[i] == '\0')
		error_log("Required operand not found", line_num);




	operandStr = (char*)malloc(sizeof(char) * (operandLength + 1));

	strncpy(operandStr, &line[i - operandLength], operandLength);
	operandStr[operandLength] = '\0';

	opr = parseOperand(operandStr, line_num);

	free(operandStr);

	return opr;

}


operand getSecondOperand(char* line, int line_num)
{
	operand opr;
	int i;

	opr.type = 0;
	opr.operandValue.immediateNum = 0;

	/* go to the start of the second operand */
	i = 0;
	while (line[i] != ',' && line[i] != '\0') i++;


	if (line[i] == '\0')
	{
		error_log("there is need to be second opernd", line_num);
		return opr;
	}

	return parseOperand(&line[i + 1], line_num);
}

int checkOperands(const command* newCommand)
{
	if (commandTypes[newCommand->numOfCommand].numOfOpreand == 2)
	{
		if (!commandTypes[newCommand->numOfCommand].destAddressTypes[newCommand->SecondOperand.type])

		{
			return 0;
		}
	}
	if (commandTypes[newCommand->numOfCommand].numOfOpreand >= 1)
	{
		if (!commandTypes[newCommand->numOfCommand].srcAddressTypes[newCommand->FirstOperand.type])
		{
			return 0;
		}
	}
	return 1;
}


command parseCommand(char* line, const int line_num)
{
	char nameOfCommand[5];
	command newCommand;

	/* Ged id in command types */
	nameOfCommand[0] = line[0];
	nameOfCommand[1] = line[1];
	nameOfCommand[2] = line[2];

	if (line[3] != ' ' || line[3] != '\t') {
		nameOfCommand[3] = line[3];
		nameOfCommand[4] = NULL;
	}
	else
	{
		nameOfCommand[3] = NULL;
	}

	newCommand.numOfCommand = typeOfCommand(nameOfCommand);


	/* if there isnt match */
	if (newCommand.numOfCommand == -1)
	{
		error_log("there isnt a legal command on line", line_num);
		return newCommand;
	}

	/* push the pointer to the start of operands */
	line = strstr(line, nameOfCommand) + strlen(nameOfCommand);

	/* parse the operands, operands type start with 0 if there arent exist */

	newCommand.FirstOperand.type = -1;
	newCommand.SecondOperand.type = -1;

	switch (commandTypes[newCommand.numOfCommand].numOfOpreand)
	{
	case 0:
		break;
	case 1:
		newCommand.SecondOperand = parseOperand(line, line_num);
		break;
	case 2:
		newCommand.FirstOperand = getFirstOperand(line, line_num);
		newCommand.SecondOperand = getSecondOperand(line, line_num);
		break;
	}
}