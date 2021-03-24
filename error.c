/**
* error.c
*/
#include "utils.h"
#include "error.h"
#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include "parse.h"

/* Fatal error - report and exit.*/
void fatal_error(const char* message) {
	fprintf(stderr, "Fatal error: %s\n", message);
	exit(EXIT_FAILURE);
}
/* Error log - report, rise counter and continue.*/
void error_log(char* msg, int line) {

	printf(stderr, "%s; The error is on line %d\n", msg, line);
	parser_data.errors++;
}