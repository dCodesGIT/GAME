/**
 * OpenCL Kernel File for Basic Arithmatic operations
 * Basic Arithmatic operations include Addition, Subtraction, Multiplication and Division
 */

// ****************************************************************************
// Addition
// Two arrays of integers
__kernel void Add_iArray(__global int *arraySum, __global int *array1, __global int *array2) {
	// Variable declaration
	int i = get_global_id(0);

	// Code
	arraySum[i] = array1[i] + array2[i];
	return;
}

// An integer to an array of integer
__kernel void Add_iNumber(__global int *arraySum, __global int *array1, __global int *number) {
	// Variable declaration
	int i = get_global_id(0);

	// Code
	arraySum[i] = array1[i] + number[0];
	return;
}

// Two arrays of floats
__kernel void Add_fArray(__global float *arraySum, __global float *array1, __global float *array2) {
	// Variable declaration
	int i = get_global_id(0);

	// Code
	arraySum[i] = array1[i] + array2[i];
	return;
}

// A float to an array of float
__kernel void Add_fNumber(__global float *arraySum, __global float *array1, __global float *number) {
	// Variable declaration
	int i = get_global_id(0);

	// Code
	arraySum[i] = array1[i] + number[0];
	return;
}

// ****************************************************************************
// Subtraction
// Array 2 of integer from array 1 of integer
__kernel void Sub_iArray(__global int *arrayDiff, __global int *array1, __global int *array2) {
	// Variable declaration
	int i = get_global_id(0);

	// Code
	arrayDiff[i] = array1[i] - array2[i];
	return;
}

// An integer from an array of integer
__kernel void Sub_iNumber(__global int *arrayDiff, __global int *array1, __global int *number) {
	// Variable declaration
	int i = get_global_id(0);

	// Code
	arrayDiff[i] = array1[i] - number[0];
	return;
}

// Array 2 of float from array 1 of float
__kernel void Sub_fArray(__global float *arrayDiff, __global float *array1, __global float *array2) {
	// Variable declaration
	int i = get_global_id(0);

	// Code
	arrayDiff[i] = array1[i] - array2[i];
	return;
}

// A float from an array of float
__kernel void Sub_fNumber(__global float *arrayDiff, __global float *array1, __global float *number) {
	// Variable declaration
	int i = get_global_id(0);

	// Code
	arrayDiff[i] = array1[i] - number[0];
	return;
}

// ****************************************************************************
// Multiplication
// Two arrays of integers
__kernel void Mul_iArray(__global int *arrayProd, __global int *array1, __global int *array2) {
	// Variable declaration
	int i = get_global_id(0);

	// Code
	arrayProd[i] = array1[i] * array2[i];
	return;
}

// An integer to an array of integer
__kernel void Mul_iNumber(__global int *arrayProd, __global int *array1, __global int *number) {
	// Variable declaration
	int i = get_global_id(0);

	// Code
	arrayProd[i] = array1[i] * number[0];
	return;
}

// Two arrays of floats
__kernel void Mul_fArray(__global float *arrayProd, __global float *array1, __global float *array2) {
	// Variable declaration
	int i = get_global_id(0);

	// Code
	arrayProd[i] = array1[i] * array2[i];
	return;
}

// A float to an array of float
__kernel void Mul_fNumber(__global float *arrayProd, __global float *array1, __global float *number) {
	// Variable declaration
	int i = get_global_id(0);

	// Code
	arrayProd[i] = array1[i] * number[0];
	return;
}

// ****************************************************************************
// Division
// Array 2 of integer from array 1 of integer
__kernel void Div_iArray(__global int *arrayQuotient, __global int *array1, __global int *array2) {
	// Variable declaration
	int i = get_global_id(0);

	// Code
	arrayQuotient[i] = array1[i] / array2[i];
	return;
}

// An integer from an array of integer
__kernel void Div_iNumber(__global int *arrayQuotient, __global int *array1, __global int *number) {
	// Variable declaration
	int i = get_global_id(0);

	// Code
	arrayQuotient[i] = array1[i] / number[0];
	return;
}

// Array 2 of float from array 1 of float
__kernel void Div_fArray(__global float *arrayQuotient, __global float *array1, __global float *array2) {
	// Variable declaration
	int i = get_global_id(0);

	// Code
	arrayQuotient[i] = array1[i] / array2[i];
	return;
}

// A float from an array of float
__kernel void Div_fNumber(__global float *arrayQuotient, __global float *array1, __global float *number) {
	// Variable declaration
	int i = get_global_id(0);

	// Code
	arrayQuotient[i] = array1[i] / number[0];
	return;
}
