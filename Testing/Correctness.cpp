#include "../src/Integer.cpp"
#include "../src/Natural.cpp"
#include "../src/Rational.cpp"
#include "../src/LinearAlgebra/Matrix.cpp"
#include "../src/LinearAlgebra/Vector.cpp"
#include "LFSR.cpp"
#include <chrono>
#include <vector>
#include <iostream>

Integer integer_from_bitstream(std::vector<int> bits) {
    Integer result;
    for (int i = 0; i < bits.size(); i++) {
        result = 2 * result + (bits[i]);
    }
    if (bits.size() > 0 && bits[0] == 1) {
        result.sign = false; // Set sign to negative if the first bit is 1
    } else {
        result.sign = true; // Set sign to positive if the first bit is 0
    }
    return result;
}

Natural natural_from_bitstream(const std::vector<int>& bits) {
    Natural result;
    for (int i = 0; i < bits.size(); i++) {
        result = Natural(2) * result + Natural(bits[i]);
    }
    return result;
}

long long ll_from_bitstream(const std::vector<int>& bits) {
    long long result = 0;
    for (int i = 0; i < bits.size(); i++) {
        result = 2 * result + (bits[i]);
    }
    if (bits.size() > 0 && bits[0] == 1) {
        result = -result; // Set sign to negative if the first bit is 1
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

Rational fibonacci(int n){
    if (n < 0) {
        throw std::invalid_argument("Fibonacci number cannot be negative.");
    }
    if (n == 0) return Rational(0);
    if (n == 1) return Rational(1);
    
    return fibonacci(n-1) + fibonacci(n-2);
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
        std::cout << "8. Test vector addition\n";
        std::cout << "9. Test vector multiplication\n";
        std::cout << "10. Test vector projection\n";
        std::cout << "11. Test matrix addition\n";
        std::cout << "12. Test matrix multiplication\n";
        std::cout << "13. Test matrix transpose\n";
        std::cout << "14. Test matrix reduced row echelon form\n";
        std::cout << "15. Test matrix determinant\n";
        std::cout << "16. Test matrix inverse\n";
        std::cout << "0. Exit\n";

        std::cout << "Enter your choice (1-14, or 0 to exit): ";
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
            case 8: {
                std::cout << "Enter size of vector:\n";
                int vector_size;
                std::cin >> vector_size;

                std::cout << "Enter number of bits:\n";
                int number_of_bits;
                std::cin >> number_of_bits;
                if (number_of_bits <= 0) {
                    std::cout << "Please enter a positive number of bits." << std::endl;
                    continue; // Skip to the next iteration if input is invalid
                }
                Vector v1(vector_size), v2(vector_size);

                for (int i = 0; i < vector_size; i++) {
                    std::vector<int> bits = lfsr.generate(number_of_bits);
                    v1.replace(integer_from_bitstream(bits), i);
                }
                for (int i = 0; i < vector_size; i++) {
                    std::vector<int> bits = lfsr.generate(number_of_bits);
                    v2.replace(integer_from_bitstream(bits), i);
                }

                std::cout << "Vector created: " << v1 << std::endl;
                std::cout << "Vector created: " << v2 << std::endl;

                auto start = std::chrono::high_resolution_clock::now();
                Vector result = v1 + v2;
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                std::cout << vector_size << " bit Vector addition took " << duration << " microseconds." << std::endl;
                std::cout << vector_size << " bit Vector addition result: " << result << std::endl;
            }

            case 9: {
                std::cout << "Enter size of vector:\n";
                int vector_size;
                std::cin >> vector_size;

                std::cout << "Enter number of bits:\n";
                int number_of_bits;
                std::cin >> number_of_bits;
                if (number_of_bits <= 0) {
                    std::cout << "Please enter a positive number of bits." << std::endl;
                    continue; // Skip to the next iteration if input is invalid
                }
                Vector v1(vector_size), v2(vector_size);

                for (int i = 0; i < vector_size; i++) {
                    std::vector<int> bits = lfsr.generate(number_of_bits);
                    v1.replace(integer_from_bitstream(bits), i);
                }
                for (int i = 0; i < vector_size; i++) {
                    std::vector<int> bits = lfsr.generate(number_of_bits);
                    v2.replace(integer_from_bitstream(bits), i);
                }

                std::cout << "Vector created: " << v1 << std::endl;
                std::cout << "Vector created: " << v2 << std::endl;

                auto start = std::chrono::high_resolution_clock::now();
                Rational result = v1 * v2;
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                std::cout << vector_size << " bit Vector multiplication took " << duration << " microseconds." << std::endl;
                std::cout << vector_size << " bit Vector multiplication result: " << result << std::endl;
            }

            case 10: {
                std::cout << "Enter size of vector:\n";
                int vector_size;
                std::cin >> vector_size;

                std::cout << "Enter number of bits:\n";
                int number_of_bits;
                std::cin >> number_of_bits;
                if (number_of_bits <= 0) {
                    std::cout << "Please enter a positive number of bits." << std::endl;
                    continue; // Skip to the next iteration if input is invalid
                }
                Vector v1(vector_size), v2(vector_size);

                for (int i = 0; i < vector_size; i++) {
                    std::vector<int> bits = lfsr.generate(number_of_bits);
                    v1.replace(integer_from_bitstream(bits), i);
                }
                for (int i = 0; i < vector_size; i++) {
                    std::vector<int> bits = lfsr.generate(number_of_bits);
                    v2.replace(integer_from_bitstream(bits), i);
                }

                std::cout << "Vector created: " << v1 << std::endl;
                std::cout << "Vector created: " << v2 << std::endl;

                auto start = std::chrono::high_resolution_clock::now();
                Vector result = v1.projectionIn(v2);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                std::cout << vector_size << " bit Vector projection took " << duration << " microseconds." << std::endl;
                std::cout << vector_size << " bit Vector projection v1 in v2 result: " << result << std::endl;
            }

            case 11: {
                std::cout << "Enter number of rows:\n";
                int rows;
                std::cin >> rows;
                std::cout << "Enter number of columns:\n";
                int columns;
                std::cin >> columns;
                std::cout << "Enter number of bits:\n";
                int number_of_bits;
                std::cin >> number_of_bits;
                if (number_of_bits <= 0) {
                    std::cout << "Please enter a positive number of bits." << std::endl;
                    continue; // Skip to the next iteration if input is invalid
                }
                Matrix m1(rows, columns), m2(rows, columns);
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < columns; j++) {
                        std::vector<int> bits = lfsr.generate(number_of_bits);
                        m1[i][j] = integer_from_bitstream(bits);
                    }
                }

                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < columns; j++) {
                        std::vector<int> bits = lfsr.generate(number_of_bits);
                        m2[i][j] = integer_from_bitstream(bits);
                    }
                }

                std::cout << "Matrix created: \n" << m1 << std::endl;
                std::cout << "Matrix created: \n" << m2 << std::endl;
                auto start = std::chrono::high_resolution_clock::now();
                Matrix result = m1 + m2;
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                std::cout << rows << "x" << columns << " " <<number_of_bits << " bit Matrix addition took "<< duration << " microseconds." << std::endl;
                std::cout << rows << "x" << columns << " " <<number_of_bits << " bit Matrix addition result: \n" << result << std::endl;
            }
            case 12: {
                /*
                std::cout << "Enter number of rows for first matrix:\n";
                int rows1;
                std::cin >> rows1;
                std::cout << "Enter number of columns for first matrix:\n";
                int columns1;
                std::cin >> columns1;
                std::cout << "Enter number of rows for second matrix:\n";
                int rows2;
                std::cin >> rows2;
                std::cout << "Enter number of columns for second matrix:\n";
                int columns2;
                std::cin >> columns2;
                if (columns1 != rows2) {
                    std::cout << "The number of columns in the first matrix must match the number of rows in the second matrix." << std::endl;
                    continue; // Skip to the next iteration if input is invalid
                }
                std::cout << "Enter number of bits:\n";
                int number_of_bits;
                std::cin >> number_of_bits;
                if (number_of_bits <= 0) {
                    std::cout << "Please enter a positive number of bits." << std::endl;
                    continue; // Skip to the next iteration if input is invalid
                }
                */
               int rows1, rows2, columns1, columns2, number_of_bits;
                rows1 = rows2 = columns1 = columns2 = 100; // For testing purposes, we can set fixed sizes
                number_of_bits = 1; // For testing purposes, we can set a fixed number of bits
                Matrix m1(rows1, columns1), m2(rows2, columns2);
                
                //Create vector matrix to test multiplication time comparison

                std::vector<std::vector<Integer>> ll_m1(rows1, std::vector<Integer>(columns1));
                std::vector<std::vector<Integer>> ll_m2(rows2, std::vector<Integer>(columns2));

                for (int i = 0; i < rows1; i++) {
                    for (int j = 0; j < columns1; j++) {
                        std::vector<int> bits = lfsr.generate(number_of_bits);
                        m1[i][j] = integer_from_bitstream(bits);
                        ll_m1[i][j] = ll_from_bitstream(bits);

                    }
                }

                for (int i = 0; i < rows2; i++) {
                    for (int j = 0; j < columns2; j++) {
                        std::vector<int> bits = lfsr.generate(number_of_bits);
                        m2[i][j] = integer_from_bitstream(bits);
                        ll_m2[i][j] = ll_from_bitstream(bits);
                    }
                }

                //std::cout << "Matrix created: \n" << m1 << std::endl;
                //std::cout << "Matrix created: \n" << m2 << std::endl;

                auto start = std::chrono::high_resolution_clock::now();
                Matrix result = m1 * m2;
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                std::cout << rows1 << "x" << columns1 << " and " <<rows2 << "x" << columns2 << " " << number_of_bits << " bit Matrix multiplication took " << duration << " microseconds." << std::endl;
                //std::cout << rows1 << "x" << columns1 << " and " <<rows2 << "x" << columns2 << " " << number_of_bits << " bit Matrix multiplication result:\n " << result << std::endl;

                /*                 start = std::chrono::high_resolution_clock::now();
                std::vector<std::vector<Integer>> ll_result(rows1, std::vector<Integer>(columns2));
                for (int i = 0; i < rows1; i++) {
                    for (int j = 0; j < columns2; j++) {
                        ll_result[i][j] = Integer(0);
                        for (int k = 0; k < columns1; k++) {
                            ll_result[i][j] += ll_m1[i][k] * ll_m2[k][j];
                        }
                    }
                }
                end = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                std::cout << rows1 << "x" << columns1 << " and " <<rows2 << "x" << columns2 << " " << number_of_bits << " bit Matrix multiplication took " << duration << " microseconds." << std::endl;
                std::cout << rows1 << "x" << columns1 << " and " <<rows2 << "x" << columns2 << " " << number_of_bits << " bit (LL) Matrix multiplication result:\n ";
                */
                rows1 = rows2 = columns1 = columns2 = 3; // For testing purposes, we can set fixed sizes
                number_of_bits = 5; // For testing purposes, we can set a fixed number of bits
                

                for (int i = 0; i < rows1; i++) {
                    for (int j = 0; j < columns1; j++) {
                        std::vector<int> bits = lfsr.generate(number_of_bits);
                        m1[i][j] = integer_from_bitstream(bits);
                        ll_m1[i][j] = ll_from_bitstream(bits);

                    }
                }

                for (int i = 0; i < rows2; i++) {
                    for (int j = 0; j < columns2; j++) {
                        std::vector<int> bits = lfsr.generate(number_of_bits);
                        m2[i][j] = integer_from_bitstream(bits);
                        ll_m2[i][j] = ll_from_bitstream(bits);
                    }
                }

                //std::cout << "Matrix created: \n" << m1 << std::endl;
                //std::cout << "Matrix created: \n" << m2 << std::endl;

                 start = std::chrono::high_resolution_clock::now();
                 result = m1 * m2;
                 end = std::chrono::high_resolution_clock::now();
                 duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                std::cout << rows1 << "x" << columns1 << " and " <<rows2 << "x" << columns2 << " " << number_of_bits << " bit Matrix multiplication took " << duration << " microseconds." << std::endl;
            }

            case 13: {
                std::cout << "Enter number of rows:\n";
                int rows;
                std::cin >> rows;
                std::cout << "Enter number of columns:\n";
                int columns;
                std::cin >> columns;
                std::cout << "Enter number of bits:\n";
                int number_of_bits;
                std::cin >> number_of_bits;
                if (number_of_bits <= 0) {
                    std::cout << "Please enter a positive number of bits." << std::endl;
                    continue; // Skip to the next iteration if input is invalid
                }
                Matrix m(rows, columns);
                
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < columns; j++) {
                        std::vector<int> bits = lfsr.generate(number_of_bits);
                        m[i][j] = integer_from_bitstream(bits);
                    }
                }

                std::cout << "Matrix created: \n" << m << std::endl;

                auto start = std::chrono::high_resolution_clock::now();
                Matrix result = Matrix::transpose(m);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                std::cout << rows << "x" << columns << " " << number_of_bits << " bit Matrix transpose took " << duration << " microseconds." << std::endl;
                std::cout << rows << "x" << columns << " " << number_of_bits << " bit Matrix transpose result:\n" << result << std::endl;
            }

            case 14: {
                std::cout << "Enter number of rows:\n";
                int rows;
                std::cin >> rows;
                std::cout << "Enter number of columns:\n";
                int columns;
                std::cin >> columns;
                std::cout << "Enter number of bits:\n";
                int number_of_bits;
                std::cin >> number_of_bits;
                if (number_of_bits <= 0) {
                    std::cout << "Please enter a positive number of bits." << std::endl;
                    continue; // Skip to the next iteration if input is invalid
                }
                Matrix m(rows, columns);
                
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < columns; j++) {
                        std::vector<int> bits = lfsr.generate(number_of_bits);
                        m[i][j] = integer_from_bitstream(bits);
                    }
                }

                std::cout << "Matrix created: \n" << m << std::endl;

                auto start = std::chrono::high_resolution_clock::now();
                Matrix result = Matrix::scalonadeForm(m);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                std::cout << rows << "x" << columns << " " << number_of_bits << " bit Matrix scalonade form took " << duration << " microseconds." << std::endl;
                std::cout << rows << "x" << columns << " " << number_of_bits << " bit Matrix scalonade form result:\n" << result << std::endl;
            }

            case 15: {
                /*
                std::cout << "Enter number of rows:\n";
                int rows;
                std::cin >> rows;
                std::cout << "Enter number of columns:\n";
                int columns;
                std::cin >> columns;
                std::cout << "Enter number of bits:\n";
                int number_of_bits;
                std::cin >> number_of_bits;
                if (number_of_bits <= 0) {
                    std::cout << "Please enter a positive number of bits." << std::endl;
                    continue; // Skip to the next iteration if input is invalid
                }
                */
               int rows, columns, number_of_bits;
                rows = columns = 100; // For testing purposes, we can set fixed sizes
                number_of_bits = 16; // For testing purposes, we can set a fixed number of bits
                Matrix m(rows, columns);
                
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < columns; j++) {
                        std::vector<int> bits = lfsr.generate(number_of_bits);
                        m[i][j] = integer_from_bitstream(bits);
                    }
                }

                std::cout << "Matrix created: \n" << m << std::endl;

                auto start = std::chrono::high_resolution_clock::now();
                Rational result = Matrix::det(m);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                std::cout << rows << "x" << columns << " " << number_of_bits << " bit Matrix determinant took " << duration << " microseconds." << std::endl;
                std::cout << rows << "x" << columns << " " << number_of_bits << " bit Matrix determinant result: " << result << std::endl;
            }

            case 16: {
                std::cout << "Enter number of rows:\n";
                int rows;
                std::cin >> rows;
                std::cout << "Enter number of columns:\n";
                int columns;
                std::cin >> columns;
                std::cout << "Enter number of bits:\n";
                int number_of_bits;
                std::cin >> number_of_bits;
                if (number_of_bits <= 0) {
                    std::cout << "Please enter a positive number of bits." << std::endl;
                    continue; // Skip to the next iteration if input is invalid
                }
                Matrix m(rows, columns);
                
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < columns; j++) {
                        std::vector<int> bits = lfsr.generate(number_of_bits);
                        m[i][j] = integer_from_bitstream(bits);
                    }
                }

                std::cout << "Matrix created: \n" << m << std::endl;

                auto start = std::chrono::high_resolution_clock::now();
                Matrix result = Matrix::inverse(m);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                std::cout << rows << "x" << columns << " " << number_of_bits << " bit Matrix inverse took " << duration << " microseconds." << std::endl;
                std::cout << rows << "x" << columns << " " << number_of_bits << " bit Matrix inverse result:\n" << result << std::endl;
            }

            case 17:{
                auto start = std::chrono::high_resolution_clock::now();
                Rational r1 = Matrix::fibonnacci(100000);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                std::cout << "Fibonacci number took " << duration << " microseconds." << std::endl;
                std::cout << "Fibonacci(50): " << r1 << std::endl;
            
            //     start = std::chrono::high_resolution_clock::now();
            //     Rational r2 = fibonacci(30);
            //     end = std::chrono::high_resolution_clock::now();
            //     duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            //     std::cout << "Fibonacci number (recursive) took " << duration << " microseconds." << std::endl;
            // 
            }

            case 18: {
                Natural n(100);
                std::cout << "Factorial of " << n << " is: " << Natural::factorial(n) << std::endl;
            }
        }
    }
        else {
            lfsr.warmup(1);
        } 
    }
}