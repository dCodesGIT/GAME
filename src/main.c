/**
 * Title : GAME (GPU Accelerated Maths Engine)
 * Start date : 20th October 2022
 */

// Header files
#include "../include/FileHelper.h"
#include "../include/DataIO.h"
#include "../include/OpenCLHelper.h"

// Macro declarations
#define ADD_IARRAY	0
#define ADD_INUMBER	1

// Enum declarations
enum KERNELS {
	Add_iArray = 0,
	Add_iNumber,
	nKernels
};

int main() {
	// Variable declaration
	cl_kernel *kernel = NULL;
	char *kernelName[] = {
		"Add_iArray",
		"Add_iNumber",
	};
	cl_mem clMem;

	// Code
	InitOpenCL();

	kernel = CreateOpenCLKernelFromFile("BasicArithmetic.cl", kernelName, nKernels);
	if(kernel == NULL)
		return -1;

#ifdef ADD_IARRAY
	cl_int iArr1[] = { 1, 2, 3, 4, 5 };
	cl_int iArr2[] = { 10, 20, 30, 40, 50 };
	cl_int iArrResult[5];
	SetOpenCLKernelArgumentWithDatablob(kernel[Add_iArray], 0, sizeof(iArrResult), NULL, &clMem);
	SetOpenCLKernelArgumentWithDatablob(kernel[Add_iArray], 1, sizeof(iArr1), iArr1, NULL);
	SetOpenCLKernelArgumentWithDatablob(kernel[Add_iArray], 2, sizeof(iArr2), iArr2, NULL);
	RunOpenCLKernel(kernel[Add_iArray], 5, clMem, sizeof(iArrResult), iArrResult);
#endif

#ifdef ADD_INUMBER
	cl_int iArr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	cl_int number = 10;
	SetOpenCLKernelArgumentWithDatablob(kernel[Add_iNumber], 0, sizeof(cl_int) * number, NULL, &clMem);
	SetOpenCLKernelArgumentWithDatablob(kernel[Add_iNumber], 1, sizeof(cl_int) * number, iArr, NULL);
	SetOpenCLKernelArgumentWithDatablob(kernel[Add_iNumber], 2, sizeof(number), &number, NULL);
	RunOpenCLKernel(kernel[Add_iNumber], 10, clMem, sizeof(cl_int) * number, iArr);
#endif

	UninitOpenCL();

	StoreIntInFile("outData.txt", number, iArr);

	return 0;
}
