#include "utils.h"
#include "parse.h"
#include "file.h"
#include "error.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h> /*for alphanomeric*/
#include <string.h> /* for stncmp and etc */
#include "commands.h"

const char* command_names[] = { "mov", "cmp", "add", "sub","lea", "clr","not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop" };



/* DATA*/
void extract_data(char* line, int const line_num)
{
    
    char* word;	/* Current word read */
    char curr_num_string[MAX_LINE_LENGTH]; /*****/
    int string_index;
    
    int is_comma;
    int is_digit;
    
    Line* node;
    int i, size, is_neg = 0;

    string_index = 0;

    size = 0;
    word = read_word(line, line_num, parser_data.file);

   

    is_comma = 0;
    is_digit = 1;

    /* loop over data and extract all numbers */
    while (*word != '\0')
    {
       
        for (i = 0; i < strlen(word); ++i)
        {
            
            /* Expect number sign only at beginning of number */
            if (word[i] == '+' || word[i] == '-')
            {
                if (word[i] == '-') is_neg = 1;
                if (string_index == 0)
                { 
                    curr_num_string[string_index] = word[i];
                    string_index++;
                }
                else
                {
                    size = 0;
                    error_log("Error, Invalid char in data ", line_num);
                    return;
                }

            }
            /* Expect number only after comma if not first number */
            else if (isdigit(word[i]))
            {
                if (is_digit)
                {
                    curr_num_string[string_index] = word[i];
                    string_index++;
                    is_comma = 1;
                }
                else
                {
                    size = 0;
                    error_log("Error, Invalid data format", line_num);
                    return;
                }
            }
            /* Expect comma between numbers */
            else if (word[i] == ',')
            {
                if (is_comma)
                {
                    is_comma = 0;
                    is_digit = 1;

                    if (string_index > 0)
                    {
                        curr_num_string[string_index] = '\0';
                        size++;

                        newLineNode(node, line_num, 1, 'A');
                        node->lebel = NULL;
                        node->bcode.allBits = atoi(curr_num_string);
                        node->address = parser_data.IC++;
                        parser_data.DC++;
                        string_index = 0;
                        addToMainList(parser_data.Mhead, node);
                    }
                }
                else
                {
                    size = 0;
                    error_log("Error, Invalid data format", line_num);
                    return;
                }
            } /*
            /* Expect spaces between numbers and commas */
            else if (word[i] == ' ' || word[i] == '\t')
            {
                if (is_comma && is_digit)
                {
                    is_digit = 0;
                }

                else if (!is_comma && is_digit)
                {
                    is_digit = 0;
                }
            }
            /* Expect only digits, signs and spaces */
            else
            {
                size = 0;
                error_log("Error, Invalid data character ", line_num);
                return;
            }
        } /* end of for */

        /* If found numbers, add them to data store */
        if (string_index > 0)
        {
            curr_num_string[string_index] = '\0';
            size++;
            newLineNode(node, line_num, 1, 'A');
            node->lebel = NULL;
            node->bcode.allBits = atoi(curr_num_string);
            node->address = parser_data.IC++;
            parser_data.DC++;
            string_index = 0;
            addToMainList(parser_data.Mhead, node);
            
        }
       
        line = line + strlen(word);
        is_comma = 1;
        word = read_word(line, line_num, parser_data.file);
        if (!word)
            return;
    }

    return;
}

/*************************************************************/
/* STRING */
int extract_string(char* word, int line_num, char* line)
{
    Line* node;
    char* line_pointer;
    int i, size, index;
    int malloc_size;
    char* temp_str;


    line_pointer = strstr(line, ".string");
    i = strlen(".string");
    size = 1;
    

    /* find first quotes */
    while ((line_pointer[i] == ' ' || line_pointer[i] == '\t') && line_pointer[i] != '\0')
    {
        i++;
    }

    /* Check if string begin with \" */
    if (line_pointer[i] != '"')
    {
        error_log("Error,  String dont start with \" ", line_num);
        size = 0;
        return strlen(line_pointer);
    }

    i++;

    malloc_size = 80;
    temp_str = (char*)malloc(sizeof(char) * malloc_size);
    if (!temp_str)
        fatal_error(ErrorMemoryAlloc);
    

    while (line_pointer[i] != '"' && line_pointer[i] != '\0')
    {
        if (line_pointer[i] < 32 || line_pointer[i] > 126)
        {
            error_log("Errors in data", line_num);
            free(temp_str);
            return strlen(line_pointer);
        }

        temp_str[size - 1] = line_pointer[i];
        size++;
        i++;
    }

    temp_str[size - 1] = '\0';

    /*  If string dont end with \" */
    if (line_pointer[i] == '\0')
    {
        error_log("Eror, Data string must end with quotes", line_num);
        size = 0;
        free(temp_str);
        return strlen(line_pointer);
    }
    
    i++;

    /* If is not alphanumeric*/
    while (line_pointer[i] != '\0')
    {
        if (line_pointer[i] != ' ' && line_pointer[i] != '\t')
        {
            error_log("Error, Invalid data after string", line_num);
            size = 0;
            free(temp_str);
            return strlen(line_pointer);
        }
        i++;
    }
    do {
        index++;
    } while (line_pointer[index] != '\"');

    while (index <= strlen(line_pointer))
    {
        if (line_pointer[index] != ' ' && line_pointer[index] != '\t' && line_pointer[index] != '\"')
        {
            Line* node1;
            newLineNode(node1, index, 1, 'A');
            node->bcode.allBits = line_pointer[index];
            node->address = parser_data.IC++;
            parser_data.DC++;

            addToMainList(parser_data.Mhead, node);
        }
        index++;
    }

    return strlen(line_pointer);
}

/* Ext and Ent */
void extract_lebel(char* word, char* curr_char, int const line_num, char* line, Attributes type)
{
    Lebel* lebel;
    word = curr_char;

    /* set pointer to the start of the next word */
    NextWord(word);
    
    if (!isalpha(*word))
    {
        error_log("Error, illigal char in Lebel ", line_num);
        return;
    }

    /* Set pointer to the end of line and the move to*/
    curr_char = line + strlen(line) - 1;
    
    /* Move back to the end of the lebel */
    while (!IsBlank(*curr_char)) curr_char--;
    
    while (isalnum(*curr_char)) curr_char--;
    
    if (curr_char < word)
    {
        error_log("Error, there is no lebel ", line_num);
        return;
    }

    /* build the node of lebel */
    NewLebelNode(lebel);
    lebel->lebel = (char*)malloc(MAX_LINE_LENGTH + 1);
    if (!lebel->lebel)
        fatal_error(ErrorMemoryAlloc);
    
    strcpy(lebel->lebel, word);
    if (getLineLebel(lebel->lebel, line_num))
    {
        /*Attributes*/
        if (type == externType)
        {
            lebel->type = externType;
            lebel->line = 0;
            addToSymbolList(parser_data.Shead, lebel);
        }
        else if (type == entryType)
        {
            lebel->type = entryType;
            lebel->line = line_num;
            addToSymbolList(parser_data.Shead, lebel);
        }
    }
    return;
}

/* Check if the line start with 'LEBEL:' */
char* getLineLebel(char* line, int line_num)
{
    int length = 0;
    char* lebel;
    const char* temp = line;
    
    lebel = (char*)malloc(MAX_LINE_LENGTH + 1);
    if (!lebel)
        fatal_error(ErrorMemoryAlloc);
    
    /* check capital letters. */
    if (!isalpha(temp))
    {
        free(lebel);
        return NULL;
    }

    while (isalnum(*temp) && length < MAX_LINE_LENGTH)
    {
        temp++;
        length++;
    }

    if (line[length] == ':') {
        strncpy(&lebel, *line, length);
        lebel[length] = '\0';
        return lebel;
    }

    free(lebel);
    return NULL;
}

/* Get the lebel - Use after extern and entry */
int BlankLine(char* line)
{
    while ((*line == ' ' || *line == '\t') && *line != '\0')
        line = &line[1];

    if (*line != '\0')
        return 0;

    return 1;
}

int check_valid_lebel(char* lebel, int line_num)
{
    char* word = lebel;

    while (*word != '\0')
    {
        if (isalnum(word))
            word++;
    }
    if (*word == ':')
        return 1;
    return 0;
}

int parse(FILE* file)
{
    /* 1 */
    /* Struct to hold all the data*/
    parser_data.IC = 99, parser_data.DC = 0;

    parser_data.Shead = NewLebelNode();
    parser_data.Mhead = newLineNode(parser_data.Mhead, 0, 0, 'A');

    /* Nodes for Main list and Symbol list.  */
    Lebel* lebel = NULL;
    Line* node = NULL;

    /*Hold the string line*/
    char* line;

    /* Lines count */
    int line_num = 0;

    /* Pointer that help us to 'run' on the line*/
    char* word;

    char* curr_char;

    command cmd;
    int there_is_lebel, index = 0;


    /* Check if there is a line */
    while (line = runOnLine(file)) /* 2*/
    {

        line_num++;
        there_is_lebel = 0;

        /* Need to check if it works */
        if (strlen(line) > MAX_LINE_LENGTH)
            error_log("Error, line is too ", line_num);

        /* If its comment line */
        if (*line == ';')
            continue;
        
        /* If its blank line */
        if (BlankLine(line))
            continue;
        
        /* Get the lebel of the line */
        lebel = NewLebelNode();

        lebel->lebel = read_word(line, line_num, file);

        if (lebel->lebel != NULL) /* if its lebel */
            there_is_lebel = check_valid_lebel(read_word(line, line_num, file), line_num);

        /* ending of the first word */


        /* If the first word is lebel so jmp to the beginning of the next word. */
        if (lebel->lebel && there_is_lebel)
        {
            word = line + strlen(lebel->lebel);
            while (*word == ' ' || *word == '\t') word++;
        }
        else
            word = line;

        
        if (*word == '\0' && lebel->lebel)
        {
            error_log("Error, only lebel in line or only empty", line_num);
            free(lebel);
            continue;
        }
       
        curr_char = word;

        while (*curr_char != ' ' && *curr_char != '\t' && *curr_char != '\0') curr_char++;
        
        while (*curr_char == ' ' && *curr_char == '\t') curr_char++;

        /* If its not data or string add it to symbol line*/
        if ((!strncmp(word, ".data", 5)) || (!strncmp(word, ".string", 7)) && (lebel->lebel))
        {

            parser_data.DC++;
            lebel->line = parser_data.DC;
            lebel->type = dataType;

            /* Add the label to the labels list. */
            addToSymbolList(parser_data.Shead, lebel); /* check if its alredy in the list    T0D0 or change "CreateAndaddtolist" */
        }

        /* Data line. */
        if (!strncmp(word, ".data", 5)) {
            word += 6;
            extract_data(word, line_num);
            continue;
        }

        /* String line. */
        if (!strncmp(word, ".string", 7)) {
            word += 8;
            extract_string(word, line_num, line);
            continue;
        }

        /* Entry label declaration line. */
        if (!strncmp(word, ".entry", 6)) {
            word += 7;
            extract_lebel(word, curr_char, line_num, line, entryType);
            continue;
        }

        /*10*/
        /* External label declaration line. */
        if (!strncmp(word, ".extern", 7)) {
            word += 8;
            extract_lebel(word, curr_char, line_num, line, externType);
            continue;
        }
        
        newLineNode(node, parser_data.IC++, 0, 'A');
        strcpy(node->lebel, lebel->lebel);
        addToMainList(parser_data.Mhead, node);

        /* 11 */
        if (lebel->lebel) {
            lebel->type = codeType;
            lebel->line = parser_data.DC + 1;
            addToSymbolList(parser_data.Shead, lebel); 
        }

        /* check if too much */
        if (strlen(line) > MAX_LINE_LENGTH) {
            error_log("Error, Line length is over 81 characters.\n", line_num);
            continue;
        }
        
        NextWord(curr_char);
        /*NewCommandLine(cmd);*/
        parser_data.cmd = parseCommand(word, line_num);


    }/* End of while*/

    if (parser_data.errors > 0)
        return 0;

    return 1;
    
}

void freeParserData(ParserData parser_data)
{
    parser_data.DC = 0;
    parser_data.IC = 99;
    parser_data.file = NULL;
    parser_data.errors = 0;
    freeLebelList(parser_data.Shead);
    freeLineList(parser_data.Mhead);
    free(parser_data.file_name_base);

}