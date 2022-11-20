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
 * @brief Initialize OpenCL.
 * It selects OpenCL platform and device.
 * Then creates OpenCL context and command queue.
 * 
 * @return Returns 'true' on success. Else 'false'.
 */
bool InitOpenCL();

/**
 * @brief Creates OpenCL kernel(s) from file 'filename'.
 * 
 * @param filename	The name of file from where the kernel(s) is to be read.
 * @param kernelName	The name of kernel(s) to be extracted from file 'filename'.
 * @param kernelCount	Number of kernel(s) specified in 'kernelName'.
 * 
 * @return Returns 'kernelCount' number of kernel(s) specified in 'kernelName'. Returns NULL on failure.
 */
cl_kernel *CreateOpenCLKernelFromFile(char *filename, const char *kernelName[], cl_uint kernelCount);

/**
 * @brief Set OpenCL kernel argument and fill array data in it.
 * 
 * @param kenrel	Specify the kernel to which the argument is to be set.
 * @param argumentIndex	Specify the number of argument to be given to kernel function. Index starts from 0.
 * @param dataSize	Specify the amount of memory required by 'dataBlob'. Amount of memory is in bytes.
 * @param dataBlob	Specify the base address of data. Can be base address of any data type. Give NULL if the argmentIndex is used to store result.
 * @param clMem_write	Returns the cl_mem object if 'dataBlob' is NULL.
 * 
 * @return Returns 'true' on success. Else 'false'.
 */
bool SetOpenCLKernelArgumentWithDatablob(cl_kernel kernel, int argumentIndex, size_t dataSize, void *dataBlob, cl_mem *clMem_write);

/**
 * @brief Runs OpenCL kernel specified in 'kernel' and fills the output in 'dataPtr'.
 * 
 * @param kernel	Specify which kernel to run.
 * @param nArrElems	Specify the number of elements present in input array.
 * @param clMem_write	Specify the cl_mem object returned by SetOpenCLKernelArgumentWithDataBlob().
 * @param dataSize	Specify the amount of memory to store resultant data. This must be same as specified in SetOpenCLKernelArgumentWithDataBlob() when 'dataBlob' was NULL.
 * @param dataPtr	Specify the base address of memory allocated on CPU side. This contains the resultant data after the OpenCL kernel has ran successfully.
 * 
 * @return Returns 'true' on success. Else 'false'.	
 */
bool RunOpenCLKernel(cl_kernel kernel, int nArrElems, cl_mem clMem_write, size_t dataSize, void *dataPtr);

/**
 * @brief Uninitialize OpenCL.
 * Deallocates memory acquired during execution of program.
 * 
 * @return void
 */
void UninitOpenCL();
