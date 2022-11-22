/**
 * Title : GAME (GPU Accelerated Maths Engine)
 * Subtracts array 2 from array 1 and saves the result in 'Sub_iArray_out.txt'.
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
		printf("\n Sub_iArray.exe 'filename_array1' 'filename_array2'");
		printf("\n\n");
		exit(EXIT_FAILURE);
	}
	char *file1 = argv[1];
	char *file2 = argv[2];

	int nArray1 = 0;
	cl_int *array1 = GetIntFromFile(file1, &nArray1);
	int nArray2 = 0;
	cl_int *array2 = GetIntFromFile(file2, &nArray2);

	// Select array of less size
	cl_int *dataResult = NULL;
	int nDataResult = 0;
	if(nArray1 > nArray2) {
		nDataResult = nArray2;
		dataResult = array2;
	}
	else {
		nDataResult = nArray1;
		dataResult = array1;
	}

	// OpenCL
	InitOpenCL();

	char *kernelName = "Sub_iArray";
	cl_kernel *clKernel = CreateOpenCLKernelFromFile("BasicArithmetic.cl", &kernelName, 1);

	cl_mem clMemory;
	SetOpenCLKernelArgumentWithDatablob(clKernel[0], 0, sizeof(cl_int) * nDataResult, NULL, &clMemory);
	SetOpenCLKernelArgumentWithDatablob(clKernel[0], 1, sizeof(cl_int) * nArray1, array1, NULL);
	SetOpenCLKernelArgumentWithDatablob(clKernel[0], 2, sizeof(cl_int) * nArray2, array2, NULL);

	RunOpenCLKernel(clKernel[0], nDataResult, clMemory, sizeof(cl_int) * nDataResult, dataResult);
	UninitOpenCL();

	StoreIntInFile("Sub_iArray_out.txt", nDataResult, dataResult);

	// Free allocated memory
	free(array1);
	free(array2);
}
