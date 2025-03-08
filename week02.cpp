// STL - Standard Template Library for C++
#include <iostream>
#include <string>
#include <math.h>




// Variables
std::string keyword = "MARK", title = "HCMUNS";
char table[6][6] = { {'8', 'p', '3', 'd', '1', 'n'},
	{'l', 't', '4', 'o', 'a', 'h'},
	{'7', 'k', 'b','c', '5', 'z'},
	{'j', 'u', '6', 'w', 'g' ,'m'},
	{'x', 's', 'v', 'i', 'r', '2'},
	{'9', 'e', 'y', '0', 'f', 'q'} };




// Function Declarations
// Declare the function encryptXXXXXX(plaintexts)
std::string encryptXXXXXX(std::string plaintexts);
// Declare the function decryptXXXXXX(ciphertexts)
std::string decryptXXXXXX(std::string ciphertexts);




// Main function
void main() {
	std::string plaintexts = "attack at 10 pm";
	std::string ciphertexts = encryptXXXXXX(plaintexts);
	std::cout << "Result: " << ciphertexts << std::endl;
	std::string decryptedtexts = decryptXXXXXX(ciphertexts);
	std::cout << "Result: " << decryptedtexts << std::endl;
}




// Function Definitions
std::string encryptXXXXXX(std::string plaintexts) {
	std::string cipher = "";

	// replace
	// loop with plaintexts
	for (int i = 0; i < plaintexts.length(); i++) {

		// iterate through all elements in the array
		for (int j = 0; j < sizeof(table) / sizeof(table[0]); j++) {
			for (int k = 0; k < sizeof(table[0]) / sizeof(table[0][0]); k++) {

				// replace, save as cipher
				if (table[j][k] == plaintexts[i]) {
					cipher += title[j];
					cipher += title[k];
				}
			}
		}
	}

	// swap
	// swap with Bubble Sort (small n)
	std::string key = keyword;
	for (int i = 0; i < key.length(); i++) {
		for (int j = 0; j < key.length() - 1; j++) {

			// sorting condition of the Bubble Sort algorithm
			if (key[j] > key[j + 1]) {

				// swap elements
				for (int k = 0; k < cipher.length() / key.length(); k++) 
				{
					std::swap(cipher[k * key.length() + j], cipher[k * key.length() + j + 1]);
				}

				// swap keywords
				std::swap(key[j], key[j + 1]);
			}
		}
	}

	// rearrange
	// rearrange with column 1, 2, 3,...
	std::string result = "";
	for (int i = 0; i < key.length(); i++) {
		for (int j = 0; j < title.length(); j++) 
		{
			result += cipher[(j * key.length() + i)];	// rearrange
		}
	}

	// return 
	return result;
}


std::string decryptXXXXXX(std::string ciphertexts) {
	std::string cipher = "";

	// decrypt the final ciphertext (columnar string) back into the intermediate ciphertext (row string)
	// pos is the row position pointer, while idx is the column character pointer within the same row
	int pos = 0, idx = 0;
	while (idx < 6) {
		// condition for decrypting to a new row
		if (pos * title.length() + idx > ciphertexts.length()) {
			pos = 0;
			idx++;
			continue;
		}

		cipher += ciphertexts[pos * title.length() + idx];	// convert
		pos++;
	}

	// remove NULL characters before processing
	cipher.erase(std::remove(cipher.begin(), cipher.end(), '\0'), cipher.end());

	// sort the keyword string in ascending order
	// with Bubble Sort become decryptionKey 
	std::string decryptionKey = keyword;
	for (int i = 0; i < decryptionKey.length(); i++) {
		for (int j = 0; j < decryptionKey.length() - 1; j++)
		{
			if (decryptionKey[j] > decryptionKey[j + 1]) {
				std::swap(decryptionKey[j], decryptionKey[j + 1]);
			}
		}
	}

	// reverse decryption of transposition cipher
	// with Selection Sort (reference)
	for (int i = 0; i < decryptionKey.length() - 1; i++) {
		
		int idx = i;
		// condition to jump to a new loop iteration if the compared values are the same
		if (keyword[i] == decryptionKey[idx])
			continue;

		// locate the position that needs to be transposed to reverse the decryption
		for (int j = i + 1; j < decryptionKey.length(); j++) {
			if (keyword[i] == decryptionKey[j]) {
				idx = j;
				break;
			}
		}

		// swap positions to make the decryptionKey match the keyword
		std::swap(decryptionKey[i], decryptionKey[idx]);
		for (int k = 0; k < cipher.length() / decryptionKey.length(); k++) 
		{
			std::swap(cipher[k * decryptionKey.length() + i], cipher[k * decryptionKey.length() + idx]);
		}
	}

	// reverse decrypt the ciphertexts to obtain the original plaintext
	std::string result = "";
	int i = 0;
	while (i < cipher.length()) {

		// determine the position of the substitution code on the substitution matrix
		int rowIdx = 0, colIdx = 0;
		char rowChar = cipher[i], colChar = cipher[i + 1];

		// search for the position
		for (int j = 0; j < title.length(); j++) 
		{
			if (rowChar == title[j])
				rowIdx = j;
			if (colChar == title[j])
				colIdx = j;
		}

		// insert to result
		result += table[rowIdx][colIdx];
		i = i + 2;
	}

	// return 
	return result;
}

