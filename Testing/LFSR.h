#pragma once
#include <vector>
#include <cstdlib>
#include <ctime>
#include <climits>

/**
 * @file LFSR.h
 * @brief Header file for Linear Feedback Shift Register (LFSR) implementation.
 * 
 * This file contains the definition of the LFSR class, which simulates a
 * linear feedback shift register for generating pseudo-random sequences.
 * 
 * This particular implementation uses a 16-bit LFSR with specific feedback
 * coefficients. The LFSR has a primitive polynomial defined by the feedback coefficients, meaning
 * it can generate a maximum-length sequence of pseudo-random bits.
 * The period is 2^16 - 1, which is the maximum for a 16-bit LFSR.
 * 
 */
class LeftShiftRegister{
    private:
        int length = 16;  // Length of the LFSR
        int feedback_coefficients[4] = {16, 15, 13, 4}; // Feedback coefficients for the LFSR
    public:
        int LFSR[16];
        /**
         * @brief Constructs a new LFSR object with a random initial state.
         * 
         */
        LeftShiftRegister();
        /**
         * @brief Generates a pseudo-random sequence of n bits using the LFSR.
         * 
         * This method generates a sequence of bits based on the LFSR's feedback
         * coefficients and current state. It returns a vector containing the
         * generated bits.
         * 
         * @return std::vector<int> A vector containing the generated pseudo-random bits.
         */
        std::vector<int> generate(int n);
        /**
         * @brief Warms up the LFSR by generating a sequence of bits.
         * 
         * This method runs n times generate() to warm up the
         * LFSR, ensuring that it is in a good state for subsequent calls to
         * generate().
         */
        void warmup(int n);
};