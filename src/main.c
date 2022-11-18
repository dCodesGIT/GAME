/**
 * 
 * Title : GAME (GPU Accelerated Maths Engine)
 * 
 * Start date : 20th October 2022
 * 
 */

// Header files
#include "../include/FileHelper.h"
#include "../include/OpenCLHelper.h"

int main() {
	// Variable declaration
	char *str = NULL;
	
	// Code
	str = readFile("../../src/main.c");
	if(str == NULL)
		return -1;

	writeFile("try.c", str);
	free(str);

	return 0;
}
