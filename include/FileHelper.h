/**
 * Header file for FileHelper.cpp
 * 
 * It contains all the helper functions such as read and write into file.
 */

// Header Files
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function declarations
/**
 * @brief Reads contents from file 'filename'.
 * 
 * @param filename Name of file which is to be read.
 * 
 * @return Returns a stream of characters from file.
 */
char *readFile(char *filename);

/**
 * @brief Writes a stream of characters to file 'filename'.
 * 
 * @param filename	Name of file in which stream of bytes is to be written.
 * @param stream	Stream of bytes(characters) to be written in file 'filename'.
 * 
 * @return Returns true if 'stream' is written successfully to file 'filename'.
 */
bool writeFile(char *filename, char *stream);
