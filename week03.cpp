#include <iostream>

// DES Tables - Each table is used for permutation in DES algorithm
const unsigned char PC1_Table[56] = {
    57, 49, 41, 33, 25, 17,  9, 1,  // Original PC1 table from DES standard
    58, 50, 42, 34, 26, 18, 10, 2,
    59, 51, 43, 35, 27, 19, 11, 3,
    60, 52, 44, 36, 63, 55, 47, 39,
    31, 23, 15,  7, 62, 54, 46, 38,
    30, 22, 14,  6, 61, 53, 45, 37,
    29, 21, 13,  5, 28, 20, 12, 4
};

const unsigned char PC1s_Table[56] = {
    50, 43, 36, 29, 22, 15, 8, 1,   // Modified PC1 table: PC1[i] - (PC1[i]/8)
    51, 44, 37, 30, 23, 16, 9, 2,
    52, 45, 38, 31, 24, 17, 10, 3,
    53, 46, 39, 32, 56, 49, 42, 35,
    28, 21, 14, 7, 55, 48, 41, 34,
    27, 20, 13, 6, 54, 47, 40, 33,
    26, 19, 12, 5, 25, 18, 11, 4
};

const unsigned char PC2_Table[48] = {
    14, 17, 11, 24,  1,  5,  3, 28, // PC2 permutation table for generating subkeys
    15,  6, 21, 10, 23, 19, 12,  4,
    26,  8, 16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56,
    34, 53, 46, 42, 50, 36, 29, 32
};

const unsigned char Shift_Table[16] = {
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1  // Number of left shifts for each round
};

// Function Declarations
unsigned char** CreateSubKey(unsigned char* Key);
void ReplaceBit(unsigned char* str, unsigned int idx, bool val);
bool ExtractBit(unsigned char* str, unsigned int idx);

// Main DES Algorithm Implementation
void main() {
    unsigned char Key[] = "abcdefgh";  // 64-bit initial key (8 bytes)
    unsigned char** Keys = CreateSubKey(Key);
    
    // Print all 16 subkeys in hexadecimal format
    for (size_t k = 0; k < 16; k++) {
        printf_s("SubKey%d:\t", k);
        for (size_t i = 0; i < 6; i++) {
            printf_s("%02x ", (unsigned short)Keys[k][i]);
        }
        printf_s("\n");
    }
}

// Function to create 16 subkeys from the initial key
unsigned char** CreateSubKey(unsigned char* Key) {
    // Allocate memory for 16 subkeys (48 bits each = 6 bytes)
    unsigned char** Keys = new unsigned char*[16];
    for (size_t k = 0; k < 16; k++) {
        Keys[k] = new unsigned char[6] {0}; // Initialize with zeros
    }

    // Allocate memory for temporary variables
    unsigned char* PC1 = new unsigned char[7] {0}; // 56 bits = 7 bytes
    unsigned char* PC2 = new unsigned char[6] {0}; // 48 bits = 6 bytes
    unsigned char* C = new unsigned char[4] {0};   // 28 bits = 4 bytes (left half)
    unsigned char* D = new unsigned char[4] {0};   // 28 bits = 4 bytes (right half)

    // Step 1: Initial Permutation using PC1s_Table
    for (size_t i = 0; i < 56; i++) {
        ReplaceBit(PC1, i, ExtractBit(Key, PC1s_Table[i] - 1));
    }

    // Step 2: Split into C0 and D0 (28 bits each)
    for (size_t i = 0; i < 28; i++) {
        ReplaceBit(C, i, ExtractBit(PC1, i));         // Left half
        ReplaceBit(D, i, ExtractBit(PC1, i + 28));    // Right half
    }

    // Step 3: Generate 16 subkeys through 16 rounds
    for (size_t round = 0; round < 16; round++) {
        // Perform left circular shift according to Shift_Table
        for (size_t shift = 0; shift < Shift_Table[round]; shift++) {
            // Save first bits before shifting
            bool tempC = ExtractBit(C, 0);
            bool tempD = ExtractBit(D, 0);
            
            // Shift all bits one position to the left
            for (size_t i = 0; i < 27; i++) {
                ReplaceBit(C, i, ExtractBit(C, i + 1));
                ReplaceBit(D, i, ExtractBit(D, i + 1));
            }
            
            // Move saved bits to the end (circular shift)
            ReplaceBit(C, 27, tempC);
            ReplaceBit(D, 27, tempD);
        }

        // Combine C and D into 56-bit CD
        unsigned char* CD = new unsigned char[7] {0};
        for (size_t i = 0; i < 28; i++) {
            ReplaceBit(CD, i, ExtractBit(C, i));         // Copy C bits
            ReplaceBit(CD, i + 28, ExtractBit(D, i));    // Copy D bits
        }

        // Generate subkey through PC2 permutation (56 bits -> 48 bits)
        for (size_t i = 0; i < 48; i++) {
            ReplaceBit(Keys[round], i, ExtractBit(CD, PC2_Table[i] - 1));
        }

        delete[] CD;  // Free temporary CD buffer
    }

    // Free all temporary buffers
    delete[] PC1;
    delete[] PC2;
    delete[] C;
    delete[] D;

    return Keys;
}

// Function to set a specific bit in a byte array
// str: byte array
// idx: bit position in the entire array
// val: bit value (0 or 1)
void ReplaceBit(unsigned char* str, unsigned int idx, bool val) {
    if (val) {
        str[idx / 8] |= (1 << (7 - (idx % 8)));  // Set bit using left shift
    } else {
        str[idx / 8] &= ~(1 << (7 - (idx % 8))); // Clear bit using left shift
    }
}

// Function to extract a specific bit from a byte array
// str: byte array
// idx: bit position in the entire array
// returns: bit value (true = 1, false = 0)
bool ExtractBit(unsigned char* str, unsigned int idx) {
    return (str[idx / 8] & (1 << (7 - (idx % 8)))) != 0; // Extract bit using left shift
}

