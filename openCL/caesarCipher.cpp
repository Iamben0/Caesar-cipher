#define CL_USE_DEPRECATED_OPENCL_2_0_APIS // using OpenCL 1.2, some functions deprecated in OpenCL 2.0
#define __CL_ENABLE_EXCEPTIONS			  // enable OpenCL exemptions

// C++ standard library and STL headers
#include <iostream>
#include <vector>
#include <fstream>

// OpenCL header, depending on OS
#ifdef __APPLE__
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

#include "common.h"

int main(void)
{
	cl::Platform platform;						 // device's platform
	cl::Device device;							 // device used
	cl::Context context;						 // context for the device
	cl::Program program;						 // OpenCL program object
	cl::Kernel encryptedKernel, decryptedKernel; // kernel objects
	cl::CommandQueue queue;						 // commandqueue for a context and device
	cl::Buffer plaintextBuffer, encryptedBuffer, decryptedBuffer;

	std::string plaintext;
	std::string nextLine;
	std::ifstream inputFile("plaintext.txt"); // Open the input file

	int n; // value for use prompt

	if (inputFile.is_open())
	{
		// Read each line from the file and append it to the plaintext string
		while (std::getline(inputFile, nextLine))
		{
			plaintext += nextLine + "\n"; // Append the line to the plaintext string
		}
		inputFile.close();

		std::cout << "Enter the shift value (n) for encryption: ";
		std::cin >> n;
		std::cin.ignore();
	}
	else
	{
		std::cout << "Failed to open the input file.\n";
	}

	int plaintextSize = plaintext.size(); // size of the text

	std::vector<cl_uchar> encryptedText(plaintextSize); // to store the encryptedText
	std::vector<cl_uchar> decryptedText(plaintextSize); // to store the decryptedText

	try
	{
		// select an OpenCL device
		if (!select_one_device(&platform, &device))
		{
			// if no device selected
			quit_program("Device not selected.");
		}

		// create a context from device
		context = cl::Context(device);

		// build the program
		if (!build_program(&program, &context, "cc.cl"))
		{
			// if OpenCL program build error
			quit_program("OpenCL program build error.");
		}

		// create the encryption and decryption kernels
		encryptedKernel = cl::Kernel(program, "encrypt");
		decryptedKernel = cl::Kernel(program, "decrypt");

		// create command queue
		queue = cl::CommandQueue(context, device);

		// create OpenCL buffers
		plaintextBuffer = cl::Buffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, plaintextSize * sizeof(cl_char), &plaintext[0]);
		encryptedBuffer = cl::Buffer(context, CL_MEM_WRITE_ONLY, plaintextSize * sizeof(cl_char));
		decryptedBuffer = cl::Buffer(context, CL_MEM_WRITE_ONLY, plaintextSize * sizeof(cl_char));

		// set kernel arguments
		encryptedKernel.setArg(0, plaintextBuffer);
		encryptedKernel.setArg(1, encryptedBuffer);
		encryptedKernel.setArg(2, n);

		decryptedKernel.setArg(0, encryptedBuffer);
		decryptedKernel.setArg(1, decryptedBuffer);
		decryptedKernel.setArg(2, n);

		// enqueue kernel for execution
		cl::NDRange offset(0);
		cl::NDRange globalSize(plaintextSize); // work‐units per kernel

		queue.enqueueNDRangeKernel(encryptedKernel, offset, globalSize);
		std::cout << "Encrpytion kernel enqueued." << std::endl;
		std::cout << "--------------------" << std::endl;

		queue.enqueueNDRangeKernel(decryptedKernel, offset, globalSize);
		std::cout << "Decryption kernel enqueued." << std::endl;
		std::cout << "--------------------" << std::endl;

		// enqueue command to read from device to host memory
		queue.enqueueReadBuffer(encryptedBuffer, CL_TRUE, 0, plaintextSize * sizeof(cl_uchar), &encryptedText[0]);
		queue.enqueueReadBuffer(decryptedBuffer, CL_TRUE, 0, plaintextSize * sizeof(cl_uchar), &decryptedText[0]);

		// open the encrypted file and write the ciphertext to the file
		std::ofstream encryptedFile("ciphertext.txt");
		for (cl_char ch : encryptedText)
		{
			encryptedFile << ch;
		}

		// open the decrypted file for and write the decrypted text to the file
		std::ofstream decryptedFile("decrypted.txt");
		for (cl_char ch : decryptedText)
		{
			decryptedFile << ch;
		}

		encryptedFile.close();
		decryptedFile.close();

		std::cout << "Encryption and decryption completed successfully." << std::endl;
	}
	// catch any OpenCL function errors
	catch (cl::Error e)
	{
		// call function to handle errors
		handle_error(e);
	}
#ifdef _WIN32
	// wait for a keypress on Windows OS before exiting
	std::cout << "\npress a key to quit...";
	std::cin.ignore();
#endif

	return 0;
}
