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

#define ELEM_COUNT	5

int main() {
	// Variable declaration
	cl_kernel *kernel = NULL;
	char *kernelName = "Add_iArray";
	cl_mem clMem;

	// Code
	InitOpenCL();

	kernel = CreateOpenCLKernelFromFile("BasicArithmatic.cl", &kernelName, 1);
	if(kernel == NULL)
		return -1;
	
	cl_int iArr1[ELEM_COUNT] = { 11, 12, 13, 14, 15 };
	cl_int iArr2[ELEM_COUNT] = { 10, 20, 30, 40, 50 };
	cl_int iArrResult[ELEM_COUNT];
	SetOpenCLKernelArgumentWithDatablob(kernel[0], 0, sizeof(iArrResult), NULL, &clMem);
	SetOpenCLKernelArgumentWithDatablob(kernel[0], 1, sizeof(iArr1), iArr1, NULL);
	SetOpenCLKernelArgumentWithDatablob(kernel[0], 2, sizeof(iArr2), iArr2, NULL);

	RunOpenCLKernel(kernel[0], ELEM_COUNT, clMem, sizeof(iArrResult), iArrResult);

	UninitOpenCL();

	return 0;
}
