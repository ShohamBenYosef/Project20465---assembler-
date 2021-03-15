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
void getFirstOperand(char* currentChar);
void parseOperand(char*currentChar,int operandLength);

int typeOfCommand(char* word);
void parseOperand(char* currentChar,int operandLength);
void getFirstOperand(char* currentChar);

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


int typeOfCommand(char* word)
{
    
    int i;
    /* Search if match to a command in the commands types */
    for (i = 0; i < numOfcommands; ++i)
    {
        if (strcmp(word, commandTypes[i].name) == 0)
            return i;
    }
    /*if the isnt a match*/
    return -1;
}
void parseOperand(char* currentChar,int operandLength)
{
    
{
    
	operand opr;
	int i=0;
	int j;
	int imadiateNumber;
	opr.type = 0;
	opr.operand_content.immediate_val = 0;
	
    printf("%c \n",currentChar[i]);
	/* Immediate case */
	if (currentChar[i] == '#')
	{
	     printf("yes its statrs with #\n");
		i++; 
		printf("check if hve sign\n");
		if (currentChar[i] == '+' || currentChar[i] == '-' || isdigit(currentChar[i]))
		{
			j = i + 1;
			for(; j < operandLength; j++)
			{
			    printf("check if number\n");
				if(!isdigit(currentChar[j]))
				{
				    /* need what to do
					log_error("Invalid operand");
					return opr; */
				}
			}
			opr.type = IMMEDIATE_OPR;
			/*opr.operand_content.immediate_val = atoi(&currentChar[i]);*/
			printf("this is an imidate operande");
			return;
		}
		/*
		log_error("Invalid operand");
		return;*/
	}

	/* Relative case */
/*	if (line[i] == '&')
	{
		if(!is_letter(line[i + 1]))
		{
			log_error("Invalid operand");
			return opr;
		}
		
		j = i + 2;
		for(; j < strlen(line); j++)
		{
			if(!is_letter(line[j]) && !is_digit(line[j]))
			{
				log_error("Invalid operand");
				return opr;
			}
		}
		
		opr.type = RELATIVE_OPR;
		opr.operand_content.operand_symbol = (char*)malloc(sizeof(char) * strlen(&line[i + 1]) + 1);
		strcpy(opr.operand_content.operand_symbol, &line[i + 1]);
		return opr;
	}

	/* Register case */
/*	if(line[i] == 'r' && strlen(&line[i]) == 2 && is_digit(line[i+1]))
	{
		const int reg_num = atoi(&line[i + 1]);
		if (reg_num >= 0 && reg_num <= 7)
		{
			opr.type = REGISTER_OPR;
			opr.operand_content.register_num = (char)reg_num;
			return opr;
		}
		
	}

	/* Symbol case */
/*	if(!is_letter(line[i]))
	{
		log_error("Invalid operand");
		return opr;
	}
	
	j = i + 1;
	for(; j < strlen(line); j++)
	{
		if(!is_letter(line[j]) && !is_digit(line[j]))
		{
			log_error("Invalid operand");
			return opr;
		}
	}
	
	opr.type = SYMBOL_OPR;
	opr.operand_content.operand_symbol = (char*)malloc(sizeof(char) * strlen(&line[i]) + 1);
	strcpy(opr.operand_content.operand_symbol, &line[i]);
	return opr;*/
}
}


void getFirstOperand(char* currentChar)
{
	operand opr;
	int operandLength=0;
    int i;

	
	opr.type = 0;
	opr.operand_content.immediate_val = 0;
	i = 0;
	/* Skip white spaces and tabs  til till its find the stat of the operand*/
	while((currentChar[i] == ' ' || currentChar[i] == '\t') && currentChar[i] != '\0' )
	{
		 currentChar++;
	}

	if (currentChar[i] == '\0')
	{
		/*error("there is no opreand after command");
		 need what to do*/
	
	}

	/* length of the  operand */
	
	while (currentChar[i] != ' ' && currentChar[i] != '\t' && currentChar[i] != ',' && currentChar[i] != '\0')
	{
		operandLength++;
		i++;
	}

	if (currentChar[i] == '\0')
	{
		/*log_error("Required operand not found");
		need what to do */
	}

	

	
    printf("sending to parse\n");
	parseOperand(currentChar,operandLength);
	
	
	
	
}
/*char* getWord(char* currentChar)
{
    currentWord = (char*)malloc((size_)word_length * sizeof(char));
    while(current_word_index < index)
    {
		while(current_char != '\0' && current_char != ' ' && current_char != '\t')
		{
			current_char_index++;
			current_char = line[current_char_index];
		}

    	while(current_char == ' ' || current_char == '\t')
    	{
			current_char_index++;
			current_char = line[current_char_index];
    	}

    	current_word_index++;
    }

	Copy letters into word 
	word_char = 0;
	while(current_char != '\0' && current_char != ' ' && current_char != '\t')
	{
		if (word_char - 1 == word_length)
		{
			word_length += WORD_INITIAL_LENGTH;
			file_reader_context.current_word = 
				(char*)realloc(file_reader_context.current_word, (word_length + 1) * sizeof(char));
		}

		file_reader_context.current_word[word_char] = current_char;
		current_char_index++;
		word_char++;
		current_char = line[current_char_index];
	}
}*/	
