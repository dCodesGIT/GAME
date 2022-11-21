/**
 * Title : GAME (GPU Accelerated Maths Engine)
 * Adds arrays (array 1 and 2) and saves the result in 'Add_fArray_out.txt'.
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
		printf("\n Add_fArray.exe 'filename_array1' 'filename_array2'");
		printf("\n\n");
		exit(EXIT_FAILURE);
	}
	char *file1 = argv[1];
	char *file2 = argv[2];

	int nArray1 = 0;
	cl_float *array1 = GetFloatFromFile(file1, &nArray1);
	int nArray2 = 0;
	cl_float *array2 = GetFloatFromFile(file2, &nArray2);

	// Select array of less size
	cl_float *dataResult = NULL;
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

	char *kernelName = "Add_fArray";
	cl_kernel *clKernel = CreateOpenCLKernelFromFile("BasicArithmetic.cl", &kernelName, 1);

	cl_mem clMemory;
	SetOpenCLKernelArgumentWithDatablob(clKernel[0], 0, sizeof(cl_float) * nDataResult, NULL, &clMemory);
	SetOpenCLKernelArgumentWithDatablob(clKernel[0], 1, sizeof(cl_float) * nArray1, array1, NULL);
	SetOpenCLKernelArgumentWithDatablob(clKernel[0], 2, sizeof(cl_float) * nArray2, array2, NULL);

	RunOpenCLKernel(clKernel[0], nDataResult, clMemory, sizeof(cl_float) * nDataResult, dataResult);
	UninitOpenCL();

	StoreFloatInFile("Add_fArray_out.txt", nDataResult, dataResult);

	// Free allocated memory
	free(array1);
	free(array2);
}
