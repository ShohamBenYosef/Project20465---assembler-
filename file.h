#include <stdio.h>
#include "error.h"
#include "list.h"

#define MainFileEnding ".as"
#define ObjectFileEnding ".ob"
#define ExternFileEnding ".ext"
#define EntryFileEnding ".ent"

#define MAX_LINE_LENGTH 81

/*name of the main file! */
char* full_file_name;

/*
* open a file
* save pointer to the file (full_file_name).
*  - modolary
*/
FILE* open_file(const char* file_name, char* ending, char* mod);

/**
*
*/
char* runOnLine();

/**
* Collect the next word.
*/
char* read_word(const char* line, const int line_num, FILE* fp);

/*
* closing  file with a given ending . (full_file_name)
*/
void close_file(const char* file_name, char* ending);