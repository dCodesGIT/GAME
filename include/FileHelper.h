/**
 * Header file for FileHelper.cpp
 * 
 * It contains all the helper functions such as read and write into file.
 */

// Header Files
#include <stdio.h>
#include <stdbool.h>

// Function definitions
/**
 * Reads contents from file 'filename'.
 * Returns stream of characters from file.
 */
char *readFile(char *filename);

/**
 * Writes stream of characters to file 'filename'.
 * Returns true if 'stream' is written successfully to file 'filename'.
 */
bool writeFile(char *filename, char *stream);
