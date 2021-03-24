/**
* error.c
*/
#include "utils.h"
#include "error.h"
#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include "asm.h"


void fatal_error(const char* message) {
	fprintf(stderr, "Fatal error: %s\n", message);
	exit(EXIT_FAILURE);
}

void error_log(char* msg, int line) {

	printf(stderr, "%s; The error is on line %d\n", msg, line);
	parser_data.errors++;
}