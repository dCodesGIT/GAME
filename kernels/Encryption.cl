/**
 * OpenCL Kernel File for Data encryption and decryption
 * Encryption and decryption using Cipher
 */

// ****************************************************************************
// Cipher
__kernel void CipherEncrypt(__global char *encrypted, __global char *data, __global char *cipher, __global int *nCipher) {
	// Variable declaration
	int i = get_global_id(0);
	int cipherLen = nCipher[0];

	// Code
	encrypted[i] = data[i] + cipher[i % cipherLen] + (i / cipherLen);

	return;
}

__kernel void CipherDecrypt(__global char *decrypted, __global char *data, __global char *cipher, __global int *nCipher) {
	// Variable declaration
	int i = get_global_id(0);
	int cipherLen = nCipher[0];

	// Code
	decrypted[i] = data[i] - cipher[i % cipherLen] - (i / cipherLen);

	return;
}
