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
bool SetOpenCLKernelArgumentWithDatablob(cl_kernel kernel, int argumentIndex, size_t dataSize, void *dataBlob, cl_mem *clMemory_write);

/**
 * Run OpenCL kernel 'kernel'
 */
bool RunOpenCLKernel(cl_kernel kernel, int nArrayElements, cl_mem clMemory_write, size_t dataSize, void *dataPtr);

/**
 * Uninitialize OpenCL
 */
void UninitOpenCL();
