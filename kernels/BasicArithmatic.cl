// OpenCL Kernel File for Basic Arithmatic operations
// Basic Arithmatic operations include Addition, Subtraction, Multiplication and Division

// Addition of two array of integers
__kernel void Add_iArray(__global int *arraySum, __global int *array1, __global int *array2) {
	// Variable declaration
	int i = get_global_id(0);

	// Code
	arraySum[i] = array1[i] + array2[i];
	printf("%d + %d = %d\n", array1[i], array2[i], arraySum[i]);
	return;
}
