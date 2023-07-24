# Caesar Cipher Encryption and Decryption

## Description

This project demonstrates a Caesar cipher implementation in both C++ and OpenCL. The Caesar cipher is a simple encryption technique that shifts each letter in the plaintext by a fixed number of positions down the alphabet. The program allows the user to enter a value for the shift amount (n) and performs both encryption and decryption on the contents of the "plaintext.txt" file. The resulting encrypted and decrypted text will be saved in separate text files.

## Requirements

### C++ Implementation

- Compiler: gcc (Rev6, Built by MSYS2 project) 12.2.0 or compatible
- Input File: `plaintext.txt`

### OpenCL Implementation

- OpenCL version: 1.2
- Input File: `plaintext.txt`

## How to Run

### C++ Implementation

1. Ensure you have gcc (Rev6, Built by MSYS2 project) 12.2.0 or a compatible version installed on your system.
2. Compile the C++ code using the following command:
   `g++ caesarCipher.cpp -o caesarCipher`
3. Run the executable: `./caesar_cipher`
4. Enter a value for the shift amount (n) when prompted.
5. The program will read the contents of `plaintext.txt`, perform encryption and decryption, and save the results in separate text files.

### OpenCL Implementation

1. Ensure you have OpenCL version 1.2 or compatible installed on your system.
2. Compile the OpenCL code using the appropriate tool (Visual Studio 2022 for me) or platform for your setup.
3. Run the OpenCL executable (Look up the openCL folder for more information).
