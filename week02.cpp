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
//std::string decryptXXXXXX(std::string ciphertexts);




// Main function
void main() {
	std::string plaintexts = "attack at 10 pm";
	std::string ciphertexts = encryptXXXXXX(plaintexts);
	std::cout << "Result: " << ciphertexts << std::endl;
	//std::string decryptedtexts = decryptXXXXXX(ciphertexts);
	//std::cout << "Result: " << decryptedtexts << std::endl;
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
	for (int i = 0; i < keyword.length(); i++) {
		for (int j = 0; j < keyword.length() - 1; j++) {

			// sorting condition of the Bubble Sort algorithm
			if (keyword[j] > keyword[j + 1]) {

				// swap elements
				for (int k = 0; k < cipher.length() / keyword.length(); k++) {
					std::swap(cipher[k * keyword.length() + j], cipher[k * keyword.length() + j + 1]);
				}

				// swap keywords
				std::swap(keyword[j], keyword[j + 1]);
			}
		}
	}

	// rearrange
	// rearrange with column 1, 2, 3,...
	std::string result = "";
	for (int i = 0; i < keyword.length(); i++) {
		for (int j = 0; j < title.length(); j++) {
			result += cipher[(j * keyword.length() + i)];	// rearrange
		}
	}

	// return 
	return result;
}



