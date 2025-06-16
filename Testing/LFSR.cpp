#include <iostream>
#include "LFSR.h"

void LeftShiftRegister::warmup(int n) {
    for(int i = 0; i < n; i++) {
        int new_bit = 0;
        // Calculate the new bit based on feedback coefficients
        for(int j = 0; j < 4; j++) {
            new_bit ^= LFSR[feedback_coefficients[j] - 1]; // XOR operation
        }
        // Shift the LFSR and insert the new bit at the front
        for(int k = length - 1; k > 0; k--) {
            LFSR[k] = LFSR[k - 1];
        }
        LFSR[0] = new_bit; // Insert new bit at the front
    }
}
std::vector<int> LeftShiftRegister::generate(int n) {
    std::vector<int> bits;
    for(int i = 0; i < n; i++) {
        int new_bit = 0;
        // Calculate the new bit based on feedback coefficients
        for(int j = 0; j < 4; j++) {
            new_bit ^= LFSR[feedback_coefficients[j] - 1]; // XOR operation
        }
        bits.push_back(new_bit);
        // Shift the LFSR and insert the new bit at the front
        for(int k = length - 1; k > 0; k--) {
            LFSR[k] = LFSR[k - 1];
        }
        LFSR[0] = new_bit; // Insert new bit at the front
    }
    warmup(100); // Warm up the LFSR
    return bits;
}
LeftShiftRegister::LeftShiftRegister() {
    bool isZero = true;
    srand(time(0));
    // for loop to check that we get different values on every iteration
    for (int i = 0; i < 16; i++) {
        LFSR[i] = rand() % 2 == 1? 1: 0; // Randomly initialize LFSR bits to 0 or 1
    }
    // Ensure the LFSR is not all zeros
    LFSR[0] = 1;
}



// int main() {
//     LeftShiftRegister lfsr;
//     std::cout << "Initial LFSR state: ";
//     for (int i = 0; i < 16; i++) {
//         std::cout << lfsr.LFSR[i] << " ";
//     }
//     std::cout << std::endl;

//     lfsr.warmup(1000); // Warm up the LFSR
//     std::vector<int> randomBits = lfsr.generate(100); // Generate 10 random bits

//     std::cout << "Generated bits: ";
//     for (int bit : randomBits) {
//         std::cout << bit << " ";
//     }
//     std::cout << std::endl;
//     return 0;
// }


