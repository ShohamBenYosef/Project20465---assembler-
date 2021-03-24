/**
* translate.h
*/
#ifndef TRANSLATE_H_
#define TRANSLATE_H_

#include <stdio.h>
#include "file.h"
#include "error.h"
#include "utils.h"

enum { entryFile, externFile, objectFile };

/***
* The second part of the algorithm.
* run on the symbol list and fill the empty machine code fields.
*/
int parse2(FILE* fp);
/**
* Print to ENT file (only if theres a entry line on the main file)
*/
void printEnt(FILE* name_file);
/**
* Print to EXT file (only if theres a extern line on the main file)
*/
void printExt(FILE* name_file);
/**
* Print to OBJECT file - run on the main list(Line) and print the machine code in hexadecimal.
*/
void printObjectFile(FILE* file_name);
/**
* 
*/
int addTargetToSource(const Line* node);

#endif