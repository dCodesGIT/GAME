/**
 * Source File for DataIO.h
 * 
 * Contains functions to read and write data from file
 * Data can be of integer, float or string type
 */

// Header Files
#include "../include/DataIO.h"

// Function definition
cl_int *GetIntFromFile(char *filename, int *elementCount) {
	// Variable declaration
	FILE *fp = NULL;
	cl_int *data = NULL;

	// Code
	// Open file for reading
	fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("\n Unable to open file '%s'", filename);
		exit(EXIT_FAILURE);
	}

	// Read int data from file
	while(1) {
		int num;
		fscanf(fp, "%d\n", &num);
		data = (cl_int *)realloc(data, sizeof(cl_int) * ((*elementCount) + 1));
		data[(*elementCount)++] = num;
		if(feof(fp))
			break;
	}

	// Close file once done reading
	fclose(fp);
	fp = NULL;

	printf("\n File '%s' read successfully...", filename);

	return data;
}

bool StoreIntInFile(char *filename, int elementCount, cl_int *data) {
	// Variable declaration
	FILE *fp = NULL;

	// Code
	// Open File
	fp = fopen(filename, "w");
	if(fp == NULL)
		exit(EXIT_FAILURE);

	// Write in file
	for(int i = 0; i < elementCount; i++)
		fprintf(fp, "%d\n", data[i]);

	// Close file
	fclose(fp);
	fp = NULL;

	printf("\n Data saved in file '%s' successfully...", filename);

	return true;
}

cl_float *GetFloatFromFile(char *filename, int *elementCount) {
	// Variable declaration
	FILE *fp = NULL;
	cl_float *data = NULL;

	// Code
	// Open file for reading
	fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("Unable to open file '%s'", filename);
		exit(EXIT_FAILURE);
	}

	// Read int data from file
	while(1) {
		float num;
		fscanf(fp, "%f\n", &num);
		data = (cl_float *)realloc(data, sizeof(cl_float) * ((*elementCount) + 1));
		data[(*elementCount)++] = num;
		if(feof(fp))
			break;
	}

	// Close file once done reading
	fclose(fp);
	fp = NULL;

	printf("\n File '%s' read successfully...", filename);

	return data;
}

bool StoreFloatInFile(char *filename, int elementCount, cl_float *data) {
	// Variable declaration
	FILE *fp = NULL;

	// Code
	// Open File
	fp = fopen(filename, "w");
	if(fp == NULL)
		exit(EXIT_FAILURE);

	// Write in file
	for(int i = 0; i < elementCount; i++)
		fprintf(fp, "%f\n", data[i]);

	// Close file
	fclose(fp);
	fp = NULL;

	printf("\n Data saved in file '%s' successfully...", filename);

	return true;
}
