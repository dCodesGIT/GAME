/**
 * OpenCL Kernel File for Basic Arithmatic operations
 * Basic Arithmatic operations include Addition, Subtraction, Multiplication and Division
 */

// Addition of two array of integers
__kernel void Add_iArray(__global int *arraySum, __global int *array1, __global int *array2) {
	// Variable declaration
	int i = get_global_id(0);

	// Code
	arraySum[i] = array1[i] + array2[i];
	return;
}

// Addition of an integer to an array
__kernel void Add_iNumber(__global int *arraySum, __global int *array1, __global int *number) {
	// Variable declaration
	int i = get_global_id(0);

	// Code
	arraySum[i] = array1[i] + number[0];
	return;
}