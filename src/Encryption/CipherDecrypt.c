/**
 * Title : GAME (GPU Accelerated Maths Engine)
 * Decrypts file using cipher and saves the result in 'CipherDecrypt_out.txt'.
 */

// Header files
#include "../include/FileHelper.h"
#include "../include/DataIO.h"
#include "../include/OpenCLHelper.h"

void main(int argc, char *argv[]) {
	// Code
	// Check for valid arguments
	if(argc != 3) {
		printf("\n Invalid number of arguments. Give command as follows.");
		printf("\n CipherDecrypt.exe 'filename' 'cipher'");
		printf("\n\n");
		exit(EXIT_FAILURE);
	}
	char *file = argv[1];
	char *cipher = argv[2];

	cl_char *data = readFile(file);
	int nData = strlen(data);
	int nCipher = strlen(cipher);

	// Select array of less size
	cl_char *decryptedData = data;
	int nDecryptedData = nData - 1;

	// OpenCL
	InitOpenCL();

	char *kernelName = "CipherDecrypt";
	cl_kernel *clKernel = CreateOpenCLKernelFromFile("Encryption.cl", &kernelName, 1);

	cl_mem clMemory;
	SetOpenCLKernelArgumentWithDatablob(clKernel[0], 0, sizeof(cl_char) * nDecryptedData, NULL, &clMemory);
	SetOpenCLKernelArgumentWithDatablob(clKernel[0], 1, sizeof(cl_char) * nData, data, NULL);
	SetOpenCLKernelArgumentWithDatablob(clKernel[0], 2, sizeof(cl_char) * nCipher, cipher, NULL);
	SetOpenCLKernelArgumentWithDatablob(clKernel[0], 3, sizeof(cl_int) * 1, &nCipher, NULL);

	RunOpenCLKernel(clKernel[0], nDecryptedData, clMemory, sizeof(cl_char) * nDecryptedData, decryptedData);
	UninitOpenCL();

	writeFile("CipherDecrypt_out.txt", decryptedData);

	// Free allocated memory
	free(data);
}