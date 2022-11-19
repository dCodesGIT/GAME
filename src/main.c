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
	cl_kernel *kernel = NULL;
	char *kernelName = "Add";

	// Code
	InitOpenCL();

	kernel = CreateKernelFromFile("BasicArithmatic.cl", &kernelName, 1);
	if(kernel == NULL)
		return -1;
	
	int arr1[] = { 1, 2, 3, 4, 5 };
	int arr2[] = { 1, 2, 3, 4, 5 };
	int arrResult[5];
	KernelArgument krnlArgs[] = {
		{ sizeof(arr1), arr1 },
		{ sizeof(arr2), arr2 },
		{ sizeof(arrResult), arrResult },
	};
	SetOpenCLKernelArguments(kernel[0], krnlArgs, sizeof(krnlArgs));

	UninitOpenCL();

	return 0;
}
