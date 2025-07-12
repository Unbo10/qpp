#include "../src/Integer.cpp"
#include "../src/Natural.cpp"
#include "../src/Rational.cpp"
#include "LFSR.cpp"
#include <chrono>
#include <vector>
#include <iostream>

Integer integer_from_bitstream(std::vector<int> bits) {
    Integer result;
    for (int i = 0; i < bits.size(); i++) {
        result = result * 2 + bits[i];
    }
    if (bits.size() > 0 && bits[0] == 1) {
        result.setSign(false); // Set sign to negative if the first bit is 1
    } else {
        result.setSign(true); // Set sign to positive if the first bit is 0
    }
    return result;
}

Natural natural_from_bitstream(const std::vector<int>& bits) {
    Natural result;
    for (int i = 0; i < bits.size(); i++) {
        result = result * 2 + bits[i];
    }
    return result;
}

long long ll_from_bitstream(const std::vector<int>& bits) {
    long long result = 0;
    for (int i = 0; i < bits.size(); i++) {
        result = result * 2 + bits[i];
    }
    return result;
}

Rational rational_from_bitstream(const std::vector<int>& bits) {
    if (bits.size() < 2) {
        throw std::invalid_argument("Bitstream must have at least 2 bits for rational number.");
    }
    Integer numerator = integer_from_bitstream(std::vector<int>(bits.begin(), bits.begin() + bits.size() / 2));
    Natural denominator = natural_from_bitstream(std::vector<int>(bits.begin() + bits.size() / 2, bits.end()));
    std::cout << "Numerator: " << numerator << ", Denominator: " << denominator << std::endl;
    return Rational(numerator, denominator);
}


int main(){
    LeftShiftRegister lfsr;
    for (int i = 0; i < 16; i++) {
        std::cout << lfsr.LFSR[i] << " ";
    }
    std::cout << std::endl;
    while (true) {
    if (std::cin){
        std::cout << "Menu:\n";
        std::cout << "1. Test natural addition\n";
        std::cout << "2. Test natural multiplication\n";
        std::cout << "3. Test integer addition\n";
        std::cout << "4. Test integer multiplication\n";
        std::cout << "5. Test integer division\n";
        std::cout << "6. Test rational addition\n";
        std::cout << "7. Test rational multiplication\n";

        std::cout << "Enter your choice (1-7, or 0 to exit): ";
        int choice;
        std::cin >> choice;
        if (choice == 0) {
            break; // Exit the loop if user enters 0
        }
        switch (choice) {
            case 1: {
                    std::cout << "Enter number of bits:\n";
                    int number_of_bits;
                    std::cin >> number_of_bits;
                    if (number_of_bits <= 0) {
                        std::cout << "Please enter a positive number of bits." << std::endl;
                        continue; // Skip to the next iteration if input is invalid
                    }
                    std::vector<int> bits = lfsr.generate(number_of_bits);
                    Natural n1 = natural_from_bitstream(bits);
                    long long ll_n1 = ll_from_bitstream(bits);
                    std::cout << "Generated bits: ";
                    for (int bit : bits) {
                        std::cout << bit;
                    }
                    std::cout << std::endl;
                    std::cout << "Natural number: " << n1 << std::endl;

                    lfsr.warmup(1000); 

                    bits = lfsr.generate(number_of_bits);
                    Natural n2 = natural_from_bitstream(bits);
                    long long ll_n2 = ll_from_bitstream(bits);
                    std::cout << "Generated bits: ";
                    for (int bit : bits) {
                        std::cout << bit;
                    }
                    std::cout << std::endl;
                    std::cout << "Natural number: " << n2 << std::endl;

                    auto start = std::chrono::high_resolution_clock::now();
                    Natural result = n1 + n2;   
                    auto end = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                    std::cout << number_of_bits << " bit Addition took " << duration << " microseconds." << std::endl;
                    
                    start = std::chrono::high_resolution_clock::now();
                    long long ll_result = ll_n1 + ll_n2;
                    end = std::chrono::high_resolution_clock::now();
                    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                    std::cout << number_of_bits << " bit (LL) Addition took " << duration << " microseconds." << std::endl;

                    std::cout << number_of_bits << " bit Natural Addition result: " << result << std::endl;
                    std::cout << number_of_bits << " bit Natural Addition result (long long): " << ll_n1 + ll_n2 << std::endl;
                    std::cout << "Same? "  << (result == Natural(ll_result)) << std::endl;
                    break;
            }
            case 2: {
                std::cout << "Enter number of bits:\n";
                    int number_of_bits;
                    std::cin >> number_of_bits;
                    if (number_of_bits <= 0) {
                        std::cout << "Please enter a positive number of bits." << std::endl;
                        continue; // Skip to the next iteration if input is invalid
                    }
                    std::vector<int> bits = lfsr.generate(number_of_bits);
                    Natural n1 = natural_from_bitstream(bits);
                    long long ll_n1 = ll_from_bitstream(bits);
                    std::cout << "Generated bits: ";
                    for (int bit : bits) {
                        std::cout << bit;
                    }
                    std::cout << std::endl;
                    std::cout << "Natural number: " << n1 << std::endl;

                    lfsr.warmup(1000); 

                    bits = lfsr.generate(number_of_bits);
                    Natural n2 = natural_from_bitstream(bits);
                    long long ll_n2 = ll_from_bitstream(bits);
                    std::cout << "Generated bits: ";
                    for (int bit : bits) {
                        std::cout << bit;
                    }
                    std::cout << std::endl;
                    std::cout << "Natural number: " << n2 << std::endl;

                    auto start = std::chrono::high_resolution_clock::now();
                    Natural result = n1 * n2;   
                    auto end = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                    std::cout << number_of_bits << " bit Multiplication took " << duration << " microseconds." << std::endl;
                    
                    start = std::chrono::high_resolution_clock::now();
                    long long ll_result = ll_n1 * ll_n2;
                    end = std::chrono::high_resolution_clock::now();
                    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                    std::cout << number_of_bits << " bit (LL) Multiplication took " << duration << " microseconds." << std::endl;

                    std::cout << number_of_bits << " bit Natural multiplication result: " << result << std::endl;
                    std::cout << number_of_bits << " bit Natural multiplication result (long long): " << ll_n1 * ll_n2 << std::endl;
                    std::cout << "Same? "  << (result == Natural(ll_n1 * ll_n2)) << std::endl;
                    break;
            }
            case 3: {
                std::cout << "Enter number of bits:\n";
                    int number_of_bits;
                    std::cin >> number_of_bits;
                    if (number_of_bits <= 0) {
                        std::cout << "Please enter a positive number of bits." << std::endl;
                        continue; // Skip to the next iteration if input is invalid
                    }
                    std::vector<int> bits = lfsr.generate(number_of_bits);
                    Integer n1 = integer_from_bitstream(bits);
                    long long ll_n1 = ll_from_bitstream(bits);
                    std::cout << "Generated bits: ";
                    for (int bit : bits) {
                        std::cout << bit;
                    }
                    std::cout << std::endl;
                    std::cout << "Integer number: " << n1 << std::endl;

                    lfsr.warmup(1000); 

                    bits = lfsr.generate(number_of_bits);
                    Integer n2 = integer_from_bitstream(bits);
                    long long ll_n2 = ll_from_bitstream(bits);
                    std::cout << "Generated bits: ";
                    for (int bit : bits) {
                        std::cout << bit;
                    }
                    std::cout << std::endl;
                    std::cout << "Integer number: " << n2 << std::endl;

                    auto start = std::chrono::high_resolution_clock::now();
                    Integer result = n1 + n2;   
                    auto end = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                    std::cout << number_of_bits << " bit Addition took " << duration << " microseconds." << std::endl;
                    
                    start = std::chrono::high_resolution_clock::now();
                    long long ll_result = ll_n1 + ll_n2;
                    end = std::chrono::high_resolution_clock::now();
                    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                    std::cout << number_of_bits << " bit (LL) Addition took " << duration << " microseconds." << std::endl;

                    std::cout << number_of_bits << " bit Integer Addition result: " << result << std::endl;
                    std::cout << number_of_bits << " bit Integer Addition result (long long): " << ll_n1 + ll_n2 << std::endl;
                    std::cout << "Same? "  << (result == Natural(ll_result)) << std::endl;
                    break;
            }
            case 4: {
                std::cout << "Enter number of bits:\n";
                int number_of_bits;
                std::cin >> number_of_bits;
                if (number_of_bits <= 0) {
                    std::cout << "Please enter a positive number of bits." << std::endl;
                    continue; // Skip to the next iteration if input is invalid
                }
                std::vector<int> bits = lfsr.generate(number_of_bits);
                Integer n1 = integer_from_bitstream(bits);
                long long ll_n1 = ll_from_bitstream(bits);
                std::cout << "Generated bits: ";
                for (int bit : bits) {
                    std::cout << bit;
                }
                std::cout << std::endl;
                std::cout << "Integer number: " << n1 << std::endl;

                lfsr.warmup(1000);

                bits = lfsr.generate(number_of_bits);
                Integer n2 = integer_from_bitstream(bits);
                long long ll_n2 = ll_from_bitstream(bits);
                std::cout << "Generated bits: ";
                for (int bit : bits) {
                    std::cout << bit;
                }
                std::cout << std::endl;
                std::cout << "Integer number: " << n2 << std::endl;

                auto start = std::chrono::high_resolution_clock::now();
                Integer result = n1 * n2;
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                std::cout << number_of_bits << " bit Multiplication took " << duration << " microseconds." << std::endl;

                start = std::chrono::high_resolution_clock::now();
                long long ll_result = ll_n1 * ll_n2;
                end = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                std::cout << number_of_bits << " bit (LL) Multiplication took " << duration << " microseconds." << std::endl;

                std::cout << number_of_bits << " bit Integer multiplication result: " << result << std::endl;
                std::cout << number_of_bits << " bit Integer multiplication result (long long): " << ll_n1 * ll_n2 << std::endl;
                std::cout << "Same? "  << (result == Natural(ll_n1 * ll_n2)) << std::endl;
            }
            case 5: {
                std::cout << "Enter number of bits:\n";
                int number_of_bits;
                std::cin >> number_of_bits;
                if (number_of_bits <= 0) {
                    std::cout << "Please enter a positive number of bits." << std::endl;
                    continue; // Skip to the next iteration if input is invalid
                }
                std::vector<int> bits = lfsr.generate(number_of_bits);
                Integer n1 = integer_from_bitstream(bits);
                long long ll_n1 = ll_from_bitstream(bits);
                std::cout << "Generated bits: ";
                for (int bit : bits) {
                    std::cout << bit;
                }
                std::cout << std::endl;
                std::cout << "Integer number: " << n1 << std::endl;

                lfsr.warmup(1000);

                bits = lfsr.generate(number_of_bits);
                Integer n2 = integer_from_bitstream(bits);
                long long ll_n2 = ll_from_bitstream(bits);
                std::cout << "Generated bits: ";
                for (int bit : bits) {
                    std::cout << bit;
                }
                std::cout << std::endl;
                std::cout << "Integer number: " << n2 << std::endl;

                auto start = std::chrono::high_resolution_clock::now();
                Integer result = n1 / n2;
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                std::cout << number_of_bits << " bit Division took " << duration << " microseconds." << std::endl;

                start = std::chrono::high_resolution_clock::now();
                long long ll_result = ll_n1 / ll_n2;
                end = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                std::cout << number_of_bits << " bit (LL) Division took " << duration << " microseconds." << std::endl;

                std::cout << number_of_bits << " bit Integer division result: " << result << std::endl;
                std::cout << number_of_bits << " bit Integer division result (long long): " << ll_result << std::endl;
                std::cout << "Same? "  << (result == Natural(ll_result)) << std::endl;
            }
            case 6: {
                std::cout << "Enter number of bits:\n";
                int number_of_bits;
                std::cin >> number_of_bits;
                number_of_bits *= 2;
                if (number_of_bits <= 0) {
                    std::cout << "Please enter a positive number of bits." << std::endl;
                    continue; // Skip to the next iteration if input is invalid
                }
                std::vector<int> bits = lfsr.generate(number_of_bits);
                Rational n1 = rational_from_bitstream(bits);
                std::cout << "Generated bits: ";
                for (int bit : bits) {
                    std::cout << bit;
                }
                std::cout << std::endl;
                std::cout << "Rational number: " << n1 << std::endl;

                lfsr.warmup(1000);

                bits = lfsr.generate(number_of_bits);
                Rational n2 = rational_from_bitstream(bits);
                std::cout << "Generated bits: ";
                for (int bit : bits) {
                    std::cout << bit;
                }
                std::cout << std::endl;
                std::cout << "Rational number: " << n2 << std::endl;

                auto start = std::chrono::high_resolution_clock::now();
                Rational result = n1 + n2;
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                std::cout << number_of_bits/2 << " bit addition took " << duration << " microseconds." << std::endl;

                std::cout << number_of_bits/2 << " bit Rational addition result: " << result << std::endl;
            }
            case 7: {
                std::cout << "Enter number of bits:\n";
                int number_of_bits;
                std::cin >> number_of_bits;
                number_of_bits *= 2;
                if (number_of_bits <= 0) {
                    std::cout << "Please enter a positive number of bits." << std::endl;
                    continue; // Skip to the next iteration if input is invalid
                }
                std::vector<int> bits = lfsr.generate(number_of_bits);
                Rational n1 = rational_from_bitstream(bits);
                std::cout << "Generated bits: ";
                for (int bit : bits) {
                    std::cout << bit;
                }
                std::cout << std::endl;
                std::cout << "Rational number: " << n1 << std::endl;

                lfsr.warmup(1000);

                bits = lfsr.generate(number_of_bits);
                Rational n2 = rational_from_bitstream(bits);
                std::cout << "Generated bits: ";
                for (int bit : bits) {
                    std::cout << bit;
                }
                std::cout << std::endl;
                std::cout << "Rational number: " << n2 << std::endl;

                auto start = std::chrono::high_resolution_clock::now();
                Rational result = n1 * n2;
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                std::cout << number_of_bits/2 << " bit Rational multiplication took " << duration << " microseconds." << std::endl;
                std::cout << number_of_bits/2 << " bit Rational addition result: " << result << std::endl;
            }
        }
    }
    else {
        lfsr.warmup(1);
    }
    }
}