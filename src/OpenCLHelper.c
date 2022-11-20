/**
 * Source file for OpenCLHelper.cpp
 * 
 * It includes wrapper functions for OpenCL.
 */

// Header files
#include "../include/OpenCLHelper.h"

// Variable declaration
static int selectedPlatform = 0;
static int selectedDevice = 0;
static cl_device_id clDeviceID;
static cl_context clContext;
static cl_command_queue clCommandQueue;
static cl_program clProgram;
static cl_kernel *clKernel;
static int n_clKernels = 0;
static cl_mem *clMemory = NULL;
static int n_clMemory = 0;

// Function definition
bool InitOpenCL() {
	// Function declarations
	cl_int GetOpenCLPlatform(cl_platform_id *);
	void printOpenCLPlatformInfo(cl_platform_id);
	cl_int GetOpenCLDevice(cl_platform_id, cl_device_id *);
	void printOpenCLDeviceInfo(cl_device_id);
	cl_int GetOpenCLContext(cl_platform_id, cl_device_id, cl_context *);

	// Variable declaration
	cl_int clResult;
	cl_platform_id clPlatformID;

	// Code
	clResult = GetOpenCLPlatform(&clPlatformID);
	if(clResult != CL_SUCCESS)
		return false;

	clResult = GetOpenCLDevice(clPlatformID, &clDeviceID);
	if(clResult != CL_SUCCESS)
		return false;

	system("cls");
	printf("Selected Platform and device information : \n");
	printOpenCLPlatformInfo(clPlatformID);
	printOpenCLDeviceInfo(clDeviceID);

	// Create OpenCL Context
	cl_context_properties contextProperties[] = {
		CL_CONTEXT_PLATFORM, (cl_context_properties)clPlatformID,
		0 };
	clContext = clCreateContext(contextProperties, 1, &clDeviceID, NULL, NULL, &clResult);
	if(clResult != CL_SUCCESS) {
		printf("\nUnable to create OpenCL context.\n");
		UninitOpenCL();
		return false;
	}
	printf("OpenCL Context created successfully...\n");

	// Create OpenCL Command Queue
	clCommandQueue = clCreateCommandQueueWithProperties(clContext, clDeviceID, 0, &clResult);
	if(clResult != CL_SUCCESS) {
		printf("\nUnable to create Command Queue.\n");
		UninitOpenCL();
		return false;
	}
	printf("OpenCL Command Queue created successfully...\n");

	return true;
}

cl_int GetOpenCLPlatform(cl_platform_id *platformID) {
	// Function declarations
	void printOpenCLPlatformInfo(cl_platform_id);
	cl_int GetOpenCLDevices(cl_platform_id, cl_device_id *);

	// Variable declaration
	cl_int clResult;
	cl_uint PlatformCount;
	cl_platform_id *platformIDs = NULL;

	// Code
	// Get count of supported OpenCL platforms
	clResult = clGetPlatformIDs(1, NULL, &PlatformCount);
	if(clResult != CL_SUCCESS || PlatformCount == 0) {
		printf("No OpenCL platform found !!!\n");
		return clResult;
	}
	platformIDs = (cl_platform_id *)alloca(sizeof(cl_platform_id) * PlatformCount);

	// Get actual ids of supported OpenCL platforms
	clResult = clGetPlatformIDs(PlatformCount, platformIDs, NULL);
	if(clResult != CL_SUCCESS) {
		printf("Unable to find OpenCL platform !!!\n");
		return clResult;
	}
	printf("Found %d OpenCL supported platform(s).\n", (int)PlatformCount);

	// Print information of all supported OpenCL platforms
	for(int i = 0; i < PlatformCount; i++) {
		printf("Platform Number : %d\n", i);
		printOpenCLPlatformInfo(platformIDs[i]);
	}

	if(PlatformCount > 1) {
		printf("Select OpenCL platform (Platform Number) : ");
		scanf("%d", &selectedPlatform);
	}
	*platformID = platformIDs[selectedPlatform];

	return CL_SUCCESS;
}

void printOpenCLPlatformInfo(cl_platform_id platformID) {
	// Variable declaration
	size_t byteCount;
	cl_char *byteStream = NULL;

	// Code
	// Platform Name
	clGetPlatformInfo(platformID, CL_PLATFORM_NAME, 0, NULL, &byteCount);
	byteStream = (cl_char *) alloca(sizeof(cl_char) * byteCount);
	clGetPlatformInfo(platformID, CL_PLATFORM_NAME, byteCount, byteStream, NULL);
	printf("\tPlatform Name : %s\n", byteStream);

	// Platform Vendor
	clGetPlatformInfo(platformID, CL_PLATFORM_VENDOR, 0, NULL, &byteCount);
	byteStream = (cl_char *) alloca(sizeof(cl_char) * byteCount);
	clGetPlatformInfo(platformID, CL_PLATFORM_VENDOR, byteCount, byteStream, NULL);
	printf("\tPlatform Vendor : %s\n", byteStream);

	// Platform supported openCL version
	clGetPlatformInfo(platformID, CL_PLATFORM_VERSION, 0, NULL, &byteCount);
	byteStream = (cl_char *) alloca(sizeof(cl_char) * byteCount);
	clGetPlatformInfo(platformID, CL_PLATFORM_VERSION, byteCount, byteStream, NULL);
	printf("\tOpenCL Version : %s\n", byteStream);
}

cl_int GetOpenCLDevice(cl_platform_id PlatformID, cl_device_id *deviceID) {
	// Function declaration
	void printOpenCLDeviceInfo(cl_device_id);

	// Variable declarations
	cl_int clResult;
	cl_uint deviceCount;
	cl_device_id *deviceIDs = NULL;

	// Code
	// Get count of OpenCL supported devices on platform PlatformID
	clResult = clGetDeviceIDs(PlatformID, CL_DEVICE_TYPE_GPU, 0, NULL, &deviceCount);
	if(clResult != CL_SUCCESS || deviceCount == 0) {
		printf("No supported devices on platform !!!\n");
		UninitOpenCL();
		return false;
	}
	deviceIDs = (cl_device_id *)malloc(sizeof(cl_device_id) * deviceCount);

	// Get actual ids of OpenCL supported devices on platform PlatformID
	clResult = clGetDeviceIDs(PlatformID, CL_DEVICE_TYPE_GPU, deviceCount, deviceIDs, NULL);
	if(clResult != CL_SUCCESS) {
		printf("No supported devices on platform !!!\n");
		UninitOpenCL();
		return false;
	}
	printf("\tFound %d OpenCL supporting device(s).\n", (int)deviceCount);

	// Print information of all supported OpenCL Devices
	for(int i = 0; i < deviceCount; i++) {
		printf("\tDevice Number : %d\n", i);
		printOpenCLDeviceInfo(deviceIDs[i]);
	}

	if(deviceCount > 1) {
		printf("Select OpenCL device for selected platform (Device Number) : ");
		scanf("%d", &selectedDevice);
	}
	*deviceID = deviceIDs[selectedDevice];

	return CL_SUCCESS;
}

void printOpenCLDeviceInfo(cl_device_id device) {
	// Variable declaration
	size_t byteCount;
	cl_char *byteStream = NULL;

	// Code
	// Device Name
	clGetDeviceInfo(device, CL_DEVICE_NAME, 0, NULL, &byteCount);
	byteStream = (cl_char *)alloca(sizeof(cl_char) * byteCount);
	clGetDeviceInfo(device, CL_DEVICE_NAME, byteCount, byteStream, NULL);
	printf("\t\tDevice Name : %s\n", byteStream);

	// Device Vendor
	clGetDeviceInfo(device, CL_DEVICE_VENDOR, 0, NULL, &byteCount);
	byteStream = (cl_char *)alloca(sizeof(cl_char) * byteCount);
	clGetDeviceInfo(device, CL_DEVICE_VENDOR, byteCount, byteStream, NULL);
	printf("\t\tDevice Vendor : %s\n", byteStream);

	// Device Version
	clGetDeviceInfo(device, CL_DEVICE_VERSION, 0, NULL, &byteCount);
	byteStream = (cl_char *)alloca(sizeof(cl_char) * byteCount);
	clGetDeviceInfo(device, CL_DEVICE_VERSION, byteCount, byteStream, NULL);
	printf("\t\tDevice Version : %s\n", byteStream);

	// Driver Version
	clGetDeviceInfo(device, CL_DRIVER_VERSION, 0, NULL, &byteCount);
	byteStream = (cl_char *)alloca(sizeof(cl_char) * byteCount);
	clGetDeviceInfo(device, CL_DRIVER_VERSION, byteCount, byteStream, NULL);
	printf("\t\tDriver Version : %s\n", byteStream);
}

cl_kernel *CreateOpenCLKernelFromFile(char *filename, const char *kernelName[], cl_uint kernelCount) {
	// Variable declaration
	cl_int clResult;
	char kernelDirectory[256];
	char *kernelSourceCode = NULL;
	const char *buildOptions = "";

	// Code
	sprintf(kernelDirectory, "../../kernels/%s", filename);
	// Read contents from file 'filename'
	kernelSourceCode = readFile(kernelDirectory);
	if(kernelSourceCode == NULL) {
		printf("Failed to read file '%s'.\n", filename);
		UninitOpenCL();
		return NULL;
	}

	// Create program
	clProgram = clCreateProgramWithSource(clContext, 1, &kernelSourceCode, NULL, &clResult);
	if(clResult != CL_SUCCESS) {
		printf("Unable to create program. clCreateProgramWithSource() failed !!!\n");
		UninitOpenCL();
		return NULL;
	}

	// Free memory allocated by readFile()
	free(kernelSourceCode);
	kernelSourceCode = NULL;

	// Build Program
	clResult = clBuildProgram(clProgram, 1, &clDeviceID, buildOptions, NULL, NULL);
	if(clResult != CL_SUCCESS) {
		printf("Unable to build program. clBuildProgram() failed !!!\n");
		size_t len;
		char *errorBuf;
		clGetProgramBuildInfo(clProgram, clDeviceID, CL_PROGRAM_BUILD_LOG, 0, NULL, &len);
		errorBuf = (char*)alloca(len);
		clGetProgramBuildInfo(clProgram, clDeviceID, CL_PROGRAM_BUILD_LOG, len, errorBuf, NULL);
		printf("Build error : %s", errorBuf);
		UninitOpenCL();
		return NULL;
	}

	// Create Kernel(s)
	clKernel = (cl_kernel *)malloc(sizeof(cl_kernel) * kernelCount);
	if(clKernel == NULL) {
		printf("Unable to allocate memory for kernel.\n");
		UninitOpenCL();
		return NULL;
	}
	for(int i = 0; i < kernelCount; i++) {
		clKernel[i] = clCreateKernel(clProgram, kernelName[i], &clResult);
		if(clResult != CL_SUCCESS) {
			printf("Unable to create kernel '%s'.\n", kernelName[i]);
			UninitOpenCL();
			return NULL;
		}
		n_clKernels++;
	}

	return clKernel;
}

bool SetOpenCLKernelArgumentWithDatablob(cl_kernel kernel, int argumentIndex, size_t dataSize, void *dataBlob, cl_mem *clMemory_write) {
	// Variable declaration
	cl_int clResult;
	cl_mem_flags flags = CL_MEM_COPY_HOST_PTR;

	// Code
	// Allocate memory for 'cl_mem' data
	n_clMemory++;
	clMemory = (cl_mem *)realloc(clMemory, sizeof(cl_mem) * n_clMemory);
	if(clMemory == NULL) {
		printf("Unable to allocate memory for data.\n");
		UninitOpenCL();
		return false;
	}

	// Create memory blob for 'dataBlob'
	if(dataBlob == NULL)
		flags = CL_MEM_HOST_READ_ONLY;
	clMemory[n_clMemory - 1] = clCreateBuffer(clContext, flags, dataSize, dataBlob, &clResult);
	if(clResult != CL_SUCCESS) {
		printf("Unable to create buffer for argument %d. clCreateBuffer() failed !!!\n", argumentIndex);
		UninitOpenCL();
		return false;
	}
	if(dataBlob == NULL)
		*clMemory_write = clMemory[n_clMemory - 1];

	// Set Kernel Argument
	clResult = clSetKernelArg(kernel, argumentIndex, sizeof(cl_mem), (void *)&clMemory[n_clMemory - 1]);
	if(clResult != CL_SUCCESS) {
		printf("clSetKernelArg() failed for argument no. %d\n", argumentIndex);
		UninitOpenCL();
		return false;
	}

	// Return 'true' on success
	return true;
}

bool RunOpenCLKernel(cl_kernel kernel, int nArrayElements, cl_mem clMemory_write, size_t dataSize, void *dataPtr) {
	// Variable declaration
	cl_int clResult;
	size_t localWorkSize = 1;
	size_t globalWorkSize = nArrayElements;

	// Code
	clResult = clEnqueueNDRangeKernel(clCommandQueue, kernel, 1, NULL, &globalWorkSize, &localWorkSize, 0, NULL, NULL);
	if(clResult != CL_SUCCESS) {
		printf("clEnqueueNDRangeKernel() failed !!!\n");
		UninitOpenCL();
		return false;
	}
	clEnqueueReadBuffer(clCommandQueue, clMemory_write, CL_TRUE, 0, dataSize, dataPtr, 0, NULL, NULL);
	if(clResult != CL_SUCCESS) {
		printf("Unable to read data from GPU back to CPU memory. clEnqueueReadBuffer() failed !!!\n");
		UninitOpenCL();
		return false;
	}
	clFinish(clCommandQueue);

	return true;
}

void UninitOpenCL() {
	// Code
	for(int i = 0; i < n_clMemory; i++) {
		if(clMemory[i])
			clReleaseMemObject(clMemory[i]);
	}
	if(clMemory)
		free(clMemory);
	for(int i = 0; i < n_clKernels; i++) {
		if(clKernel[i])
			clReleaseKernel(clKernel[i]);
	}
	if(clKernel)
		free(clKernel);
	if(clProgram)
		clReleaseProgram(clProgram);
	if(clCommandQueue)
		clReleaseCommandQueue(clCommandQueue);
	if(clContext)
		clReleaseContext(clContext);
	if(clDeviceID)
		clReleaseDevice(clDeviceID);
}
