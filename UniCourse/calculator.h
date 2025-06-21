#include <iostream>
#include <vector>

class Calculator {
    protected:
        int convert_to_integer(std::vector<int>, int);
        std::vector<int> convert_to_vector(int);
        /**
         * @brief Add zeros to the left of the vector (i.e., from position `0`)
         */
        std::vector<int> add_zeros(std::vector<int>, int);
        std::vector<int> trim_zeros(std::vector<int>, int);
        int minimize_greatest_power(std::vector<int>);
        /**
         * @brief Returns a vector's left or right half (assuming the vector's
         * size is a power of 2).
         * 
         * Given a vector of integers whose positions are ordered from left to
         * right as `0`, `1`, ..., `n/2 - 1`, `n/2`, ..., `n - 1`, the *left half*
         * are all the elements from the `0`-th index to the `n/2 - 1` index
         * inclusive. Accordingly, the *right half* are all the elements from
         * the `n/2`-th index to the `n - 1`-th index inclusive.
         * 
         * @param v The vector to split.
         * @param half If it's `r`, then the right half will be returned; if
         * it's `l`, the left half will be returned. Otherwise, it will return
         * a vector of zeros of `v`'s size.
         * @return std::vector<int> If the operation is succesful, then it will
         * return one of the two halves of `v`.
         */
        int real_len(std::vector<int>);
        std::vector<int> split_vector(std::vector<int>, const char);
    public:
        Calculator();
        void print_vector(const std::vector<int>&);
        int mod(int, int);        
        void pretty_print_operation(const std::vector<int>&, 
                                    const std::vector<int>&, 
                                    const std::vector<int>&, 
                                    char);
        std::vector<int> convert_to_b10(int, int);
        std::vector<int> convert_to_b10(std::vector<int>, int, int);
        std::vector<int> add(int, int, int);   
        std::vector<int> add(std::vector<int>, std::vector<int>, int);
        std::vector<int> subtract(int, int, int);
        std::vector<int> subtract(std::vector<int>, std::vector<int>, int);
        /**
         * @brief Multiplies two numbers in a given base.
         * 
         * Takes two non-negative integers, `n` and `m`, and multiplies them 
         * using the "traditional" O(n^2) implemented in the overload of
         * this method.
         * 
         * @param n The greater integer.
         * @param m The second integer.
         * @param b The base in which the two integers are and the result will
         * be given.
         * @return std::vector<int> The result of multiplying `n` times `m`.
         */
        std::vector<int> multiply(int, int, int);

        /** @brief Multiplies two numbers in a given base.
         * 
         * Takes two non-negative vectors, `n` and `m`, representing a number
         * by listing their digits, (e.g., `5402` would be 
         * `Vector[5, 4, 0, 2]`) and multiplies them using the "traditional"
         * O(n^2) method.
         * 
         * @param n The greater integer.
         * @param m The second integer.
         * @param b The base in which the two integers are and the result will
         * be given.
         * @return std::vector<int> The result of multiplying `n` times `m`.
         */
        std::vector<int> multiply(std::vector<int>, std::vector<int>, int);
        /**
         * @brief Mutliplies two non-negative numbers in a given base using
         * Karatsuba's algorithm.
         * 
         * Takes two non-negative integers, converts them to vectors and calls
         * the overloading of this function to receive the integers as vectors.
         * This will compute the product `n*m` in base `b` using Karatsuba's
         * algorithm.
         * 
         * @param n A non-negative integer greater than `m`.
         * @param m A non-negative integer.
         * @param b The base of the two integers.
         * 
         * @return std::vector<int> The product `n*b` in base `b`.
         */
        std::vector<int> karatsuba_m(int, int, int);
        /**
         * @brief Mutliplies two numbers in a given base using Karatsuba's
         * algorithm.
         * 
         * Takes two non-negative integers (`n` and `m`), ordered from greatest
         * to smallest, represented as vectors, their base, and a boolean which
         * will trigger the execution of step 1 when true and not otherwise. 
         * With this, the method does the following:
         * 1. Adds zeros to the left of both integers so that they have a
         * length of the closest power of 2 of the greatest of the two 
         * integers, i.e., a non-negative integer `i` such that `2^i - n` is
         * minimized (this happens only if no previous recursion called has 
         * been made, which will be understood to happen when `p = -1`).
         * 2. Makes a recursive call until the length of the two integers is 1.
         * Then, it computes the product of the two using Karatsuba's algorithm
         * and returns them.
         * 
         * It also asumes that `n` and `m` have the same size, which is a power
         * of 2, if `balanced` is true.
         * 
         * @param n A non-negative integer as a vector greater than `m`.
         * @param m A non-negative integer as a vector.
         * @param b The base of the integer.
         * @param balanced To denote whether the addition of zeros at the left
         * of `n` and `m` has been made.
         * @return std::vector<int> The product `n*m` in base `b`.
         */
        std::vector<int> karatsuba_m(std::vector<int>, std::vector<int>, int, bool);
        std::vector<int>* divide(int, int, int);
        std::vector<int>* divide(std::vector<int>, std::vector<int>, int);
};
