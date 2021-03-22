#include "utils.h"
#include "asm.h"
#include "file.h"
#include "error.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h> /*for alphanomeric*/
#include <string.h> /* for stncmp and etc */
#include "commands.h"


int DCF, ICF;
int IC, DC;
extern file;

const char* command_names[] = { "mov", "cmp", "add", "sub","lea", "clr","not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop" };

extern main_list_head, lebel_list_head;

/* DATA*/
void extract_data(char* line, int const line_num)
{
    printf("in EXTRACT DATA*****  \n");
    char* word;	/* Current word read */
    char current_number_string[80]; /*****/
    int current_number_string_index;
    int comma_expected;
    int digit_expected;
    Line* node;
    int i, size, is_neg = 0;

    current_number_string_index = 0;

    size = 0;
    word = read_word(line, line_num, file);
    printf(" after read word, word=%s \n", word);

    comma_expected = 0;
    digit_expected = 1;

    /* loop over data and extract all numbers */
    while (*word != '\0')
    {
        printf("in big lopp data---- \n");
        for (i = 0; i < strlen(word); ++i)
        {
            printf("   \n");
            printf("  in for loop \n");
            /* Expect number sign only at beginning of number */
            if (word[i] == '+' || word[i] == '-')
            {
                if (word[i] == '-') is_neg = 1;
                if (current_number_string_index == 0)
                {
                    printf(" in while for if 1  \n");
                    current_number_string[current_number_string_index] = word[i];
                    current_number_string_index++;
                }
                else
                {
                    printf("  in ehile for else 1 \n");
                    size = 0;
                    error_log("Error, Invalid char in data ", line_num);
                    return;
                }

            }
            /* Expect number only after comma if not first number */
            else if (isdigit(word[i]))
            {
                printf("  in else if \n");
                if (digit_expected)
                {

                    printf(" digit expected  \n");
                    current_number_string[current_number_string_index] = word[i];
                    current_number_string_index++;
                    comma_expected = 1;
                }
                else
                {
                    printf("  digit not expected \n");
                    size = 0;
                    error_log("Error, Invalid data format", line_num);
                    return;
                }
            }
            /* Expect comma between numbers */
            else if (word[i] == ',')
            {
                printf("  else if 2 \n");
                if (comma_expected)
                {
                    printf("  comma \n");
                    comma_expected = 0;
                    digit_expected = 1;

                    if (current_number_string_index > 0)
                    {
                        printf("  comma and num \n");
                        current_number_string[current_number_string_index] = '\0';
                        size++;
                        printf(" build node  \n");
                        newLineNode(node, line_num, 1, 'A');
                        node->lebel = NULL;
                        node->bcode.allBits = atoi(current_number_string);


                        current_number_string_index = 0;
                    }
                    printf("   there is not else \n");
                }
                else
                {
                    printf("  other else \n");
                    size = 0;
                    error_log("Error, Invalid data format", line_num);
                    return;
                }
            } /*
            /* Expect spaces between numbers and commas */
            else if (word[i] == ' ' || word[i] == '\t')
            {
                if (comma_expected && digit_expected)
                {
                    digit_expected = 0;
                }

                else if (!comma_expected && digit_expected)
                {
                    digit_expected = 0;
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
        if (current_number_string_index > 0)
        {
            current_number_string[current_number_string_index] = '\0';
            size++;

            newLineNode(node, line_num, 1, 'A');
            node->lebel = NULL;
            node->bcode.allBits = atoi(current_number_string);

            current_number_string_index = 0;
        }
        printf("  \n");
        printf("end of while?  \n");
        line = line + strlen(word);
        comma_expected = 1;
        word = read_word(line, line_num, file);
    }

    return;
}

/*************************************************************/
/* STRING */
int extract_string(char* word, int line_num, char* line)
{
    printf(" EXTRACT STRING \n");
    Line* node;
    char* pLine;
    int i, size, index;
    int malloc_size;
    char* temp_str;


    pLine = strstr(line, ".string");
    i = strlen(".string");
    size = 1;
    printf("%s \n", pLine);

    /* find first quotes */
    while ((pLine[i] == ' ' || pLine[i] == '\t') && pLine[i] != '\0')
    {
        i++;
    }

    /* String must begin with quotes*/
    if (pLine[i] != '"')
    {
        error_log("Error,  String dont start with \" ", line_num);
        size = 0;
        return strlen(pLine);
    }

    i++;
    malloc_size = 80;
    temp_str = (char*)malloc(sizeof(char) * malloc_size);
    if (!temp_str)
        fatal_error(ErrorMemoryAlloc);
    printf("  after memory aloc\n");

    /* Add chars between quotes */
    while (pLine[i] != '"' && pLine[i] != '\0')
    {
        printf(" in main while \n");
        if (pLine[i] < 32 || pLine[i] > 126)
        {
            printf(" no alpha no digit \n");
            error_log("Errors in data", line_num);
            free(temp_str);
            return strlen(pLine);
        }

        printf(" alpha or digit \n");
        temp_str[size - 1] = pLine[i];
        size++;
        i++;
    }

    temp_str[size - 1] = '\0';

    /* Second quotes not found */
    if (pLine[i] == '\0')
    {
        printf("pline == null  \n");
        error_log("Eror, Data string must end with quotes", line_num);
        size = 0;
        free(temp_str);
        return strlen(pLine);
    }
    printf(" ----1---- \n");
    i++;
    /* Expect to find only whitespaces after quotes */
    while (pLine[i] != '\0')
    {
        printf(" another while \n");
        if (pLine[i] != ' ' && pLine[i] != '\t')
        {
            error_log("Error, Invalid data after string", line_num);
            size = 0;
            free(temp_str);
            return strlen(pLine);
        }
        i++;
    }
    do {
        index++;
    } while (pLine[index] != '\"');

    printf(" ----- 2   *----- \n");
    while (index <= strlen(pLine))
    {
        if (pLine[index] != ' ' && pLine[index] != '\t' && pLine[index] != '\"')
        {
            printf("  build nodes  ----\n");
            Line* node1;
            newLineNode(node1, index, 1, 'A');
            node->bcode.allBits = pLine[index];
            addToMainList(main_list_head, node);

            printf("%d \n", pLine[index]);
            printf("%d \n", node->bcode.allBits);
        }
        index++;
    }
    printf(" return \n");
    return strlen(pLine);
}

/* Ext and Ent */
void extract_lebel(char* word, char* curr_char, int const line_num, char* line, Attributes type)
{
    printf("  \n");/********************************/
    printf(" IN EXTRACT_LEBEL!!!!!! \n");
    printf(" -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*---*-*-*-*-*-*-*-**--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-**-*-* \n");
    if (type == entryType)
        printf("entry  \n");
    else
        printf(" extern \n");
        /*******************************/
    Lebel* lebel;
    word = curr_char;

    /* set pointer to the start of the next word */
    NextWord(word);
    printf("  after nexWord\n");
    if (!isalpha(*word))
    {
        printf(" !isalpha \n");
        error_log("Error, illigal char in Lebel ", line_num);
        return;
    }

    /* Set pointer to the end of line and the move to*/
    curr_char = line + strlen(line) - 1;
    printf("char to end  \n");
    /* Move back to the end of the lebel */
    while (!IsBlank(*curr_char)) curr_char--;
    printf("  move back 1\n");
    while (isalnum(*curr_char)) curr_char--;
    printf(" move back 2 \n"); 
    if (curr_char < word)
    {
        printf("  some error\n");
        error_log("Error, there is no lebel ", line_num);
        return;
    }

    /* build the node of lebel */
    printf(" build lebel node \n");
    NewLebelNode(lebel);
    lebel->lebel = (char*)malloc(MAX_LINE_LENGTH + 1);
    if (!lebel->lebel)
        fatal_error(ErrorMemoryAlloc);
    printf(" after memeory alloc \n");
    strcpy(lebel->lebel, word);
    if (getLineLebel(lebel->lebel, line_num))
    {
        printf(" in if \n");
        /*Attributes*/
        if (type == externType)
        {
            printf("extern  \n");
            lebel->type = externType;
            lebel->line = 0;
            addToSymbolList(lebel_list_head, lebel);
        }
        else if (type == entryType)
        {
            printf("  entry\n");
            lebel->type = entryType;
            lebel->line = line_num;
            addToSymbolList(lebel_list_head, lebel);
        }
    }
    printf("END OF EXTRACT LEBEL  - - - back to parse.  \n");
    return;
}

/* Check if the line start with 'LEBEL:' */
char* getLineLebel(char* line, int line_num)
{
    printf("\n in getlinelebel  \n");
    int length = 0;
    char* lebel;
    const char* temp = line++;

    lebel = (char*)malloc(MAX_LINE_LENGTH + 1);
    if (!lebel)
        fatal_error(ErrorMemoryAlloc);
    printf("after memory allocation   \n");
    /* check capital letters. */
    if (!isalpha(*temp))
    {
        printf("***** NULL   ******  \n");
        free(lebel);

        return NULL;
    }

    while (isalnum(*temp) && length < MAX_LINE_LENGTH)
    {
        temp++;
        length++;
    }
    printf("after while  \n");
    if (line[length] == ':') {
        strncpy(lebel, line, length);
        lebel[length] = '\0';
        return lebel;
    }
    printf(" end of getline lebel - returrn to parse: \n");

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
/**
* יש מצב שלא נצטרך
*/
/*int check_valid_lebel(char* lebel, int line_num)
{
printf("in valid  \n");
    int index;
    char* word = lebel;
    while (!IsBlank(word))
    {
        printf(" in while loop check if its alphaand : \n");
        if (!isalpha(word) || !isalnum(word))
        {
            error_log("Error, illigal char in lebel ", line_num);
            return 0;
        }
        word++;
    }
    if (word != ':')
    {
        error_log("Error, illigal char in lebel ", line_num);
        return 0;
    }
    printf("go back to \n");
    free(lebel);
    return 1;
}*/

int parse(FILE* file)
{
    /* 1 */
    IC = 99, DC = 0;

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

    char* temp_arr[10];
    command cmd;
    int there_is_lebel = 0, index = 0;

    printf(" IN ASM.C - starting purse: \n");
    printf("GO to runOnLine - FILE.C");
    /* Check if there is a line */
    while (line = runOnLine(file)) /* 2*/
    {
        printf("  in the while loop\n");
        line_num++;

        /* Need to check if it works */
        if (strlen(line) > MAX_LINE_LENGTH)
            error_log("Error, line is too ", line_num);
        printf(" its in the right size\n");
        if (*line == ';')
        {
            printf(" empty line - continue-------------------- \n");
            continue;
        }
        printf("not line of ;\n");
        if (BlankLine(line))
        {
            printf("is blank line\n");
            continue;
        }
        printf("IN THE IF CONDITION - CHECK THE LINE:\n create new node  \n");
        /* Get the lebel of the line */
        NewLebelNode(lebel);
        printf("lebel: %s\n", lebel->lebel);
        printf(" send it to getLineLebel \n");
        lebel->lebel = getLineLebel(line, line_num);
        printf("back from getLineLebel - go to validate  \n");
        if (lebel->lebel != NULL) /* if its lebel */
        {
            printf("  lebel->lebel != NULL  so lebel: %s\n", lebel->lebel);
            /*there_is_lebel = check_valid_lebel(lebel->lebel, line_num);*/
        }
        /* ending of the first word */
        printf(" we back in parse:  \n");

        word = line;
        printf(" print word - %s\n", word);
        NextWord(word);

        /* Empty line. */
        if (*word == '\0' || *word == '\n' || (IsBlank(*word) && strlen(line) == 1))
        {
            printf(" chaeck if *word == 0 ----    continue  \n");
            free(lebel);
            continue;
        }
        /* If the first word is lebel so jmp to the beginning of the next word. */
        if (lebel->lebel) {
            printf(" if lebel->lebel and then  set word to the end \n");
            word = line + strlen(lebel->lebel) + 1;
            NextWord(word++);
            printf(" print word%s \n", word);
        }

        /* */
        if (*word == '\0' && lebel->lebel)
        {
            error_log("Error, only lebel in line ", line_num);
            free(lebel);
            continue;
        }

        curr_char = word + 1;
        while (!IsBlank(*curr_char) && *curr_char != '\0')
            curr_char++;
        printf("curr char - %s \n", --curr_char); /*dont forget to keep -- */

        /*5*/
        printf("check what is this line:  5\n");
        printf("  \n");
        /*word++;*/
        strncpy(temp_arr, word, 5);
        printf(" print word - %s \n", temp_arr);

        /* If its not data or string add it to symbol line*/
        if ((!strncmp(word, ".data", 5)) || (!strncmp(word, ".string", 7)) && (lebel->lebel))
        {
            printf(" build symbol node \n");
            DC++;
            lebel->line = DC;
            lebel->type = dataType;
            /* Add the label to the labels list. */
            printf(" go to adToSymbolList-----> \n");
            addToSymbolList(lebel_list_head, &lebel); /* check if its alredy in the list    T0D0 or change "CreateAndaddtolist" */
        }

        /* 7 */
        printf("\n********\n ");

        printf(" print word%s \n", word);
        word++;
        printf("  \n");
        printf(" temp arr:%s\n", temp_arr);

        /* Data line. */
        if (!strncmp(word, ".data", 5)) {
            continue;/************************/
            printf("word = %s\n", word);
            word += 6;
            printf("word = %s\n", word);
            printf(" its data ! \n");
            continue;
            extract_data(word, line_num);

            continue;
        }

        printf(" no data \n");
        /* String line. */
        if (!strncmp(word, ".string", 7))
        {
            continue;/******************************/
            printf(" its string  -------------------------------- \n");
            extract_string(word, line_num, line);
            continue;
        }


        printf("no string");
        /*8*/
        /*9*/
        /* Entry label declaration line. */
        if (!strncmp(word, ".entry", 6))
        {
            printf("entry");
            extract_lebel(word, curr_char, line_num, line, entryType);
            return;/**********************/
            continue;
        }
        /*******************/
        printf("no entry");
        /*10*/
        /* External label declaration line. */
        if (!strncmp(word, ".extern", 7)) 
        {
            printf("extern");
            extract_lebel(word, curr_char, line_num, line, externType);
            return;
            continue;
        }
        printf("extern");
        /* add to main list */

        printf("no enty no extern  \n");
        continue;/********************/
        return;/************************/


        IC++;
        newLineNode(&node, IC, 0, 'A');
        strcpy(node->lebel, lebel->lebel);


        /*add to symbol table */
        /* need to add func to check if the lebel is alredy exist in the list*/
        /* 11 */
        if (lebel->lebel) {
            lebel->type = codeType;
            lebel->line = DC + 1;
            addToSymbolList(lebel_list_head, lebel); /* check if its alredy in the list    T0D0 or change "CreateAndaddtolist" */
        }

        /* check if too much */
        if (strlen(line) > MAX_LINE_LENGTH) {
            error_log("Error, Line length is over 81 characters.\n", line_num);
            continue;
        }
        /****************************************************************/

        NextWord(curr_char);
        /*NewCommandLine(cmd);*/
        cmd = parseCommand(word, line_num);

        /* 13*/
        /* נתח את מבנה האופרנדים של ההוראה, וחשב מהו מס המילים הכולל שתופסת ההוראה בקוד מכונה ונקראה לו אל גדול    L*/
        /*14*/
        /* בניית קוד בינארי של המילה הראשונה, ןשל כל מילת-מידע נוספת המקודדת  אופרנד במיעון מיידי*/

    /* end of if  */
        /****************************************************************
        *******************************************************************/

    }/* end of while*/

    if (errors_count > 0)
        return 0;

    /* 18 */
/*
    ICF = IC;
    DCF = DC;
*/
/* 19 */
/*update_line_in_symbol_list(); to do*/

    return 1;
    /* 17 */
}