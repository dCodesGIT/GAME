/**
 * Title : GAME (GPU Accelerated Maths Engine)
 * Encrypts file using cipher and saves the result in 'CipherEncrypt_out.txt'.
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
		printf("\n CipherEncrypt.exe 'filename' 'cipher'");
		printf("\n\n");
		exit(EXIT_FAILURE);
	}
	char *file = argv[1];
	char *cipher = argv[2];

	cl_char *data = readFile(file);
	int nData = strlen(data);
	int nCipher = strlen(cipher);

	// Select array of less size
	cl_char *encryptedData = data;
	int nEncryptedData = nData - 1;

	// OpenCL
	InitOpenCL();

	char *kernelName = "CipherEncrypt";
	cl_kernel *clKernel = CreateOpenCLKernelFromFile("Encryption.cl", &kernelName, 1);

	cl_mem clMemory;
	SetOpenCLKernelArgumentWithDatablob(clKernel[0], 0, sizeof(cl_char) * nEncryptedData, NULL, &clMemory);
	SetOpenCLKernelArgumentWithDatablob(clKernel[0], 1, sizeof(cl_char) * nData, data, NULL);
	SetOpenCLKernelArgumentWithDatablob(clKernel[0], 2, sizeof(cl_char) * nCipher, cipher, NULL);
	SetOpenCLKernelArgumentWithDatablob(clKernel[0], 3, sizeof(cl_int) * 1, &nCipher, NULL);
printf("\n%d\n%s", nData, data);
	RunOpenCLKernel(clKernel[0], nEncryptedData, clMemory, sizeof(cl_char) * nEncryptedData, encryptedData);
	UninitOpenCL();
printf("%s", encryptedData);

	writeFile("CipherEncrypt_out.txt", encryptedData);

	// Free allocated memory
	free(data);
}
