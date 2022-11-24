/**
 * Header File for DataIO.c
 * 
 * Contains functions to read and write data from file.
 * Data can be of integer, float or string type.
 */

// Header files
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "CL/cl.h"

// Global macro definitions
#define DEFAULT_OUT_FILE	"output.txt"

// Function declaration
/**
 * @brief Reads file and stores in array of integers.
 * 
 * @param filename	Name of file from which integer data has to be read.
 * @param elementCount	Returns the number of integers read from file.
 * 
 * @return Returns a pointer to an array of integers read from file.
 */
cl_int *GetIntFromFile(char *filename, int *elementCount);

/**
 * @brief Writes data from array into file.
 * 
 * @param filename	Name fo file in which data is to be written.
 * @param elementCount	Number of elements from array to be written in file.
 * @param data		Pointer to an array of data.
 * 
 * @return Returns true on success. Else false.
 */
bool StoreIntInFile(char *filename, int elementCount, cl_int *data);

/**
 * @brief Reads file and stores in array of float.
 * 
 * @param filename	Name of file from which float data has to be read.
 * @param elementCount	Returns the number of float read from file.
 * 
 * @return Returns a pointer to an array of float read from file.
 */
cl_float *GetFloatFromFile(char *filename, int *elementCount);

/**
 * @brief Writes data from array into file.
 * 
 * @param filename	Name fo file in which data is to be written.
 * @param elementCount	Number of elements from array to be written in file.
 * @param data		Pointer to an array of data.
 * 
 * @return Returns true on success. Else false.
 */
bool StoreFloatInFile(char *filename, int elementCount, cl_float *data);
