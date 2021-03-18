/**
* translate.h
*/
#ifndef TRANSLATE_H_
#define TRANSLATE_H_

#include <stdio.h>
#include "file.h"
#include "error.h"
#include "utils.h"

enum { objectFile, externFile, entryFile };



/***
*
*/
int parse2(FILE* fp);
/**
*
*/
void printEnt(FILE* name_file);
/**
*
*/
void printExt(FILE* name_file);
/**
*
*/
void printObjectFile(FILE* file_name);
/**
*
*/
int addTargetToSource(const Line* node);

#endif