/**
 * Source Code for FileHelper.h
 * 
 * It contains all the helper functions such as read and write into file.
 */

// Header files
#include "../include/FileHelper.h"

// Function definitions
char *readFile(char *filename) {
	// Variable declarations
	FILE *fp = NULL;
	unsigned int fileSize = 0;
	char *stream = NULL;

	// Code
	// Open file 'filename' in read mode
	fp = fopen(filename, "rb");
	if(fp == NULL) {
		printf("Unable to open file '%s'.", filename);
		return NULL;
	}

	// Get file size
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	// Allocate 'fileSize' bytes of memory
	stream = (char *)malloc(sizeof(char) * (fileSize + 1));
	if(stream == NULL) {
		printf("Unable to allocate memory for stream of %d characters.", fileSize);
		fclose(fp);
		return NULL;
	}

	// Read file and store in 'stream'
	fread(stream, sizeof(char), fileSize, fp);
	stream[fileSize] = '\0';

	// Close file once reading done from file
	fclose(fp);
	fp = NULL;

	// Return read file
	return stream;
}

bool writeFile(char *filename, char *stream) {
	// Variable declaration
	FILE *fp = NULL;

	// Code
	// Open file 'filename' in write mode
	fp = fopen(filename, "w");
	if(fp == NULL) {
		printf("Unable to open file '%s'.", filename);
		return false;
	}

	// Write in file 'filename'
	fprintf(fp, "%s", stream);

	// Close file once writing done in file
	fclose(fp);
	fp = NULL;

	// Return true if file read successfully
	return true;
}
