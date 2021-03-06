/*/**
*
*/

#define ErrorMaxLengthLine "there is to many characters in this line."
#define ErrorMissingArgument "Missing argument."
#define ErrorCantRead "Could not open file %s for reading."
#define ErrorMemoryAlloc "Memory allocation failed."

/**
*
*/
void fatal_error(const char* message);
void error_log(char* msg, int line);