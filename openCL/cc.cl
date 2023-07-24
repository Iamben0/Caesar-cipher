// Encryption kernel
__kernel void encrypt(__global const char *plaintext, __global char *encryptedText, int n) {
    size_t id = get_global_id(0);

    // Read the input plaintext characters using char16 vector type
    char16 c = vload16(0, plaintext + id * 16);

    // Encrypt the characters using the shift cipher method
    for (int i = 0; i < 16; i++) {
        char charToEncrypt = c[i];

        if (charToEncrypt >= 'a' && charToEncrypt <= 'z') {
            // Shift lowercase letters
            charToEncrypt = ((charToEncrypt - 'a' + n) % 26 + 26) % 26 + 'a';
        } else if (charToEncrypt >= 'A' && charToEncrypt <= 'Z') {
            // Shift uppercase letters
            charToEncrypt = ((charToEncrypt - 'A' + n) % 26 + 26) % 26 + 'A';
        }

        c[i] = charToEncrypt;
    }

    // Write the encrypted characters to the output ciphertext
    vstore16(c, 0, encryptedText + id * 16);
}


// Decryption kernel
__kernel void decrypt(__global const char* encryptedText, __global char* decryptedText, int n) {
    size_t id = get_global_id(0);

    // Read the input ciphertext characters using char16 vector type
    char16 c = vload16(0, encryptedText + id * 16);

    // Decrypt the characters using the reverse shift
    for (int i = 0; i < 16; i++) {
        char charToDecrypt = c[i];

        if (charToDecrypt >= 'a' && charToDecrypt <= 'z') {
            // Shift lowercase letters
            charToDecrypt = ((charToDecrypt - 'a' + 26 - n) % 26 + 26) % 26 + 'a';
        } else if (charToDecrypt >= 'A' && charToDecrypt <= 'Z') {
            // Shift uppercase letters
            charToDecrypt = ((charToDecrypt - 'A' + 26 - n) % 26 + 26) % 26 + 'A';
        }

        c[i] = charToDecrypt;
    }

    // Write the decrypted character to the output decrypted text
    vstore16(c, 0, decryptedText + id * 16);
}

