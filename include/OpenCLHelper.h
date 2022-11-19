/**
 * Helper file for OpenCLHelper.cpp
 * 
 * It includes wrapper functions for OpenCL.
 */

// Header files
#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <malloc.h>
#include "../CL/cl.h"
#include "FileHelper.h"

// Structure declaration
typedef struct _KernelArgument {
	size_t size;
	void *arg;
} KernelArgument;

// Function declarations
/**
 * Initialize OpenCL for program
 */
bool InitOpenCL();

/**
 * Create OpenCL Kernel from 'filename'
 */
cl_kernel *CreateOpenCLKernelFromFile(char *filename, const char *kernelName[], cl_uint kernelCount);

/**
 * Set OpenCL kernel Arguments
 */
bool SetOpenCLKernelArguments(cl_kernel kernel, KernelArgument *kernelArguments, int nkernelArguments);

/**
 * Run OpenCL kernel 'kernel'
 */
bool RunOpenCLKernel(cl_kernel kernel, cl_mem *memObjects, cl_uint memObjectCount, cl_uint dims, size_t *GlobalWorkSize, size_t *LocalWorkSize);

/**
 * Uninitialize OpenCL
 */
void UninitOpenCL();
