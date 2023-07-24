// C++ standard library and STL headers
#include <iostream>
#include <fstream>
#include <string>

// Prototype
std::string encryptText(const std::string &, int);
std::string decryptText(const std::string &, int);

int main()
{
	std::string plaintext;
	std::string nextLine;
	std::ifstream inputFile("plaintext.txt"); // Open the input file

	if (inputFile.is_open())
	{
		// Read each line from the file and append it to the plaintext string
		while (std::getline(inputFile, nextLine))
		{
			plaintext += nextLine + "\n"; // Append the line to the plaintext string
		}
		inputFile.close();

		int n;
		std::cout << "Enter the shift value (n) for encryption: ";
		std::cin >> n;

		// Encrypt the plaintext
		std::string ciphertext = encryptText(plaintext, n);

		// Open the encrypted file and write the ciphertext to the file
		std::ofstream encryptedFile("ciphertext.txt");
		encryptedFile << ciphertext;

		// Decrpyt the ciphertext
		std::string decryptedText = decryptText(ciphertext, n);

		// Open the decrypted file for and write the decrypted text to the file
		std::ofstream decryptedFile("decrypted.txt");
		decryptedFile << decryptedText;

		encryptedFile.close();
		decryptedFile.close();

		std::cout << "Encryption and decryption completed successfully." << std::endl;
	}
	else
	{
		std::cout << "Failed to open the input file.\n";
	}

	return 0;
}

// Function to encrypt text using Caesar’s cipher
std::string encryptText(const std::string &plaintext, int n)
{
	std::string ciphertext = plaintext;

	for (char &ch : ciphertext)
	{
		// Ensures that only alphabetic characters are encrypted, while leaving other characters unchanged
		if (isalpha(ch))
		{
			char base = islower(ch) ? 'a' : 'A'; // Align with the ASCII value and ensuring consistent when encrypting
			ch = ((ch - base + n) % 26 + 26) % 26 + base;
		}
	}

	return ciphertext;
}

// Function to decrypt text using Caesar’s cipher
std::string decryptText(const std::string &ciphertext, int n)
{
	return encryptText(ciphertext, 26 - n); // Decryption is just encryption with the reverse n
}