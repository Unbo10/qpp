#include "../src/Integer.cpp"
#include "../src/Natural.cpp"
#include "LFSR.cpp"
#include <chrono>
#include <vector>
#include <iostream>

Integer int_from_bitstream(std::vector<int> bits) {
    Integer result;
    for (int i = 0; i < bits.size(); i++) {
        result = result * 2 + bits[i];
    }
    return result;
}

int main(){
    LeftShiftRegister lfsr;
    for (int i = 0; i < 16; i++) {
        std::cout << lfsr.LFSR[i] << " "; // Print initial LFSR state
    }
    std::cout << std::endl;
    std::vector<int> randomBits = lfsr.generate(10); // Generate 100 random bits
    std::cout << "Generated bits: ";
    for (int bit : randomBits) {
        std::cout << bit << " "; // Print generated bits
    }
    Integer integerFromBits = int_from_bitstream(randomBits);
    std::cout << "Generated Integer from LFSR bits: " << integerFromBits << std::endl;
}