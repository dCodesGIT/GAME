/**
 * Source file for OpenCLHelper.cpp
 * 
 * It includes wrapper functions for OpenCL.
 */

// Header files
#include "../include/OpenCLHelper.h"

// Variable declaration
static cl_platform_id *clPlatformID = NULL;
static cl_device_id *clDeviceID = NULL;

// Function definition
/**
 * Initialize OpenCL for program
 */
bool InitOpenCL() {
	// Function declarations
	cl_int GetOpenCLPlatforms(cl_uint *);
	cl_int GetOpenCLDevices(cl_platform_id, cl_uint *);

	// Variable declaration
	cl_int clResult;
	cl_uint clPlatforms;
	cl_uint clDevices;

	// Code
	clResult = GetOpenCLPlatforms(&clPlatforms);
	if(clResult != CL_SUCCESS)
		return false;

	for(int i = 0; i < clPlatforms; i++) {
		clResult = GetOpenCLDevices(clPlatformID[i], &clDevices);
		if(clResult != CL_SUCCESS)
			return false;
	}

	return true;
}

/**
 * Get all supported OpenCL Platform(s) and gives
 * number of supported platforms in 'clPlatformCount'.
 * Returns CL_SUCCESS on sucess.
 */
cl_int GetOpenCLPlatforms(cl_uint *PlatformCount) {
	// Variable declaration
	cl_int clResult;
	size_t byteCount;
	cl_char *byteStream = NULL;

	// Code
	// Get count of supported OpenCL platforms
	clResult = clGetPlatformIDs(1, NULL, PlatformCount);
	if(clResult != CL_SUCCESS || PlatformCount == 0) {
		printf("No OpenCL platform found !!!\n");
		return clResult;
	}
	clPlatformID = (cl_platform_id *)malloc(sizeof(cl_platform_id) * (*PlatformCount));

	// Get actual ids of supported OpenCL platforms
	clResult = clGetPlatformIDs(*PlatformCount, clPlatformID, NULL);
	if(clResult != CL_SUCCESS) {
		printf("Unable to find OpenCL platform !!!\n");
		return clResult;
	}
	printf("Found %d OpenCL supported platform(s).\n", (int)(*PlatformCount));

	// Print information of all supported OpenCL platforms
	for(int i = 0; i < (*PlatformCount); i++) {
		printf("Platform Number : %d\n", i);
		// Platform Name
		clGetPlatformInfo(clPlatformID[i], CL_PLATFORM_NAME, 0, NULL, &byteCount);
		byteStream = (cl_char *) alloca(sizeof(cl_char) * byteCount);
		clGetPlatformInfo(clPlatformID[i], CL_PLATFORM_NAME, byteCount, byteStream, NULL);
		printf("\tPlatform Name : %s\n", byteStream);

		// Platform Vendor
		clGetPlatformInfo(clPlatformID[i], CL_PLATFORM_VENDOR, 0, NULL, &byteCount);
		byteStream = (cl_char *) alloca(sizeof(cl_char) * byteCount);
		clGetPlatformInfo(clPlatformID[i], CL_PLATFORM_VENDOR, byteCount, byteStream, NULL);
		printf("\tPlatform Vendor : %s\n", byteStream);

		// Platform supported openCL version
		clGetPlatformInfo(clPlatformID[i], CL_PLATFORM_VERSION, 0, NULL, &byteCount);
		byteStream = (cl_char *) alloca(sizeof(cl_char) * byteCount);
		clGetPlatformInfo(clPlatformID[i], CL_PLATFORM_VERSION, byteCount, byteStream, NULL);
		printf("\tOpenCL Version : %s\n", byteStream);
	}
	return CL_SUCCESS;
}

/**
 * Get supported OpenCL Device(s) and gives
 * number of supported devices in 'clDeviceCount'.
 * Returns CL_SUCCESS on sucess.
*/
cl_int GetOpenCLDevices(cl_platform_id PlatformID, cl_uint *DeviceCount) {
	// Variable declarations
	cl_int clResult;
	size_t byteCount;
	cl_char *byteStream = NULL;

	// Code
	// Get count of OpenCL supported devices on platform PlatformID
	clResult = clGetDeviceIDs(PlatformID, CL_DEVICE_TYPE_GPU, 0, NULL, DeviceCount);
	if(clResult != CL_SUCCESS || (*DeviceCount) == 0) {
		printf("No supported devices on platform !!!\n");
		UninitOpenCL();
		return false;
	}
	clDeviceID = (cl_device_id *)malloc(sizeof(cl_device_id) * (*DeviceCount));

	// Get actual ids of OpenCL supported devices on platform PlatformID
	clResult = clGetDeviceIDs(PlatformID, CL_DEVICE_TYPE_GPU, *DeviceCount, clDeviceID, NULL);
	if(clResult != CL_SUCCESS) {
		printf("No supported devices on platform !!!\n");
		UninitOpenCL();
		return false;
	}
	printf("\tFound %d OpenCL supporting device(s).\n", (int)(*DeviceCount));

	// Print information of all supported OpenCL Devices
	for(int i = 0; i < (*DeviceCount); i++) {
		printf("\tDevice Number : %d\n", i);
		// Device Name
		clGetDeviceInfo(clDeviceID[i], CL_DEVICE_NAME, 0, NULL, &byteCount);
		byteStream = (cl_char *)alloca(sizeof(cl_char) * byteCount);
		clGetDeviceInfo(clDeviceID[i], CL_DEVICE_NAME, byteCount, byteStream, NULL);
		printf("\t\tDevice Name : %s\n", byteStream);

		// Device Vendor
		clGetDeviceInfo(clDeviceID[i], CL_DEVICE_VENDOR, 0, NULL, &byteCount);
		byteStream = (cl_char *)alloca(sizeof(cl_char) * byteCount);
		clGetDeviceInfo(clDeviceID[i], CL_DEVICE_VENDOR, byteCount, byteStream, NULL);
		printf("\t\tDevice Vendor : %s\n", byteStream);

		// Device Version
		clGetDeviceInfo(clDeviceID[i], CL_DEVICE_VERSION, 0, NULL, &byteCount);
		byteStream = (cl_char *)alloca(sizeof(cl_char) * byteCount);
		clGetDeviceInfo(clDeviceID[i], CL_DEVICE_VERSION, byteCount, byteStream, NULL);
		printf("\t\tDevice Version : %s\n", byteStream);

		// Driver Version
		clGetDeviceInfo(clDeviceID[i], CL_DRIVER_VERSION, 0, NULL, &byteCount);
		byteStream = (cl_char *)alloca(sizeof(cl_char) * byteCount);
		clGetDeviceInfo(clDeviceID[i], CL_DRIVER_VERSION, byteCount, byteStream, NULL);
		printf("\t\tDriver Version : %s\n", byteStream);

		// Max Computation units
		cl_uint maxComputeUnits = 0;
		clGetDeviceInfo(clDeviceID[i], CL_DEVICE_MAX_COMPUTE_UNITS, 0, NULL, &byteCount);
		clGetDeviceInfo(clDeviceID[i], CL_DEVICE_MAX_COMPUTE_UNITS, byteCount, &maxComputeUnits, NULL);
		printf("\t\tMaximum compute units : %d\n", maxComputeUnits);
	}

	return CL_SUCCESS;
}

/**
 * Uninitialize OpenCL
 */
void UninitOpenCL() {
	// Code
	if(clDeviceID) {
		free(clDeviceID);
		clDeviceID = NULL;
	}
	if(clPlatformID) {
		free(clPlatformID);
		clPlatformID = NULL;
	}
}
