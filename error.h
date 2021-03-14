/*/**
* error.h
*/

/* list of common errors:  */
#define ErrorMaxLengthLine "there is to many characters in this line."
#define ErrorMissingArgument "Missing argument."
#define ErrorCantRead "Could not open file %s for reading."
#define ErrorMemoryAlloc "Memory allocation failed."


int errors_count;
/**
* Prints an error message and the program exits
*/
void fatal_error(const char* message);
/**
* Prints an error message and adds 1 to the error counter
*/
void error_log(char* msg, int line);