/**
 * Title : GAME (GPU Accelerated Maths Engine)
 * Divides a number from an array and saves the result in 'Div_iNumber_out.txt'.
 */

// Header files
#include "../include/FileHelper.h"
#include "../include/DataIO.h"
#include "../include/OpenCLHelper.h"

void main(int argc, char *argv[]) {
	// Code
	// Check for valid arguments
	if(argc != 3) {
		printf("\n Invalid number of arguments. Give command as follows.");
		printf("\n Div_iArray.exe 'filename_array1' 'integer'");
		printf("\n\n");
		exit(EXIT_FAILURE);
	}
	char *file1 = argv[1];
	char *numStr = argv[2];

	int nArray1 = 0;
	cl_int *array1 = GetIntFromFile(file1, &nArray1);
	cl_int number = atoi(numStr);

	// Select array of less size
	cl_int *dataResult = array1;
	int nDataResult = nArray1;

	// OpenCL
	InitOpenCL();

	char *kernelName = "Div_iNumber";
	cl_kernel *clKernel = CreateOpenCLKernelFromFile("BasicArithmetic.cl", &kernelName, 1);

	cl_mem clMemory;
	SetOpenCLKernelArgumentWithDatablob(clKernel[0], 0, sizeof(cl_int) * nDataResult, NULL, &clMemory);
	SetOpenCLKernelArgumentWithDatablob(clKernel[0], 1, sizeof(cl_int) * nArray1, array1, NULL);
	SetOpenCLKernelArgumentWithDatablob(clKernel[0], 2, sizeof(cl_int) * 1, &number, NULL);

	RunOpenCLKernel(clKernel[0], nDataResult, clMemory, sizeof(cl_int) * nDataResult, dataResult);
	UninitOpenCL();

	StoreIntInFile("Div_iNumber_out.txt", nDataResult, dataResult);

	// Free allocated memory
	free(array1);
}
