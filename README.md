# GAME
GPU Accelerated Maths Engine

## Description
GAME is capable of performing mathematical calculations on huge amount of data.
It has console based UI but can be used for statistics and mathematics as it can
read from file and print output into file as well as on the terminal. GAME uses 
[OpenCL](https://www.khronos.org/opencl/)(Open Computing Library), an open, royality-free standard for implemeting 
mathematical and statistical functions.

### *More about OpenCL*
*OpenCL™ (Open Computing Language) is an open, royalty-free standard for cross-
platform, parallel programming of diverse accelerators found in supercomputers,
cloud servers, personal computers, mobile devices and embedded platforms.
OpenCL greatly improves the speed and responsiveness of a wide spectrum of 
applications in numerous market categories including professional creative 
tools, scientific and medical software, vision processing, and neural network 
training and inferencing.*

## Installation
* Clone the repository.
<!-- * Install dependency libraries / SDKs
	1. OpenCL
		* Windows : Click [here](https://github.com/GPUOpen-LibrariesAndSDKs/OCL-SDK/releases/download/1.0/OCL_SDK_Light_AMD.exe) to download OpenCL SDK. Run the 
			executable and install.
		* Linux : Open the terminal and run the command
			```bash
			$ sudo apt install ocl-icd-opencl-dev
			``` -->
* Now run `build.bat` (*for Windows*), `build.sh` (*for Linux*) to build the 
project. You will find all the executables in `output` folder.

## Limitations
* No GUI.
* OpenCL based only since we want our project to be open source and cross platform.

## Authors
1. [Darshan Vikam](https://github.com/dCodesGIT)
2. [Yash Pungaliya](https://github.com/IRONKID444)

### Contact Us
For any queries or pull requests
1. Darshan Vikam : darshan.vikam@gmail.com
2. Yash Pungaliya : ypungaliya@gmail.com
