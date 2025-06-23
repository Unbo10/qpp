#pragma once

#include <iostream>
#include "../utils/List.h"
#include "SndPolyTerm.h"

class SndPoly {
private:
    bool is_ordered = false;

public:
    SndPoly() = default;
    SndPoly(const SndPoly& poly);
    SndPoly(const SndPolyTerm& term);

    std::vector<SndPolyTerm> dense;
    std::vector<SndPolyTerm> sparse;

    //***STREAM OPERATIONS***

    /**
     * @brief Output stream operator for printing the polynomial.
     * 
     * Prints the polynomial as a sum of terms in the form a*x^b*y^c where:
     * - a is the coefficient (rational number).
     * - b is the exponent of x.
     * - c is the exponent of y.
     * 
     * Terms are printed in descending order of the degree of y and then of x.
     * 
     * @param os The output stream
     * @param poly The polynomial to be printed
     * @return The modified output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const SndPoly& poly);
    /**
     * @brief Assigning operator that takes a string to form a two-variable
     * polynomial.
     * 
     * The string must contain an amount of numbers, separated by a space, 
     * divisible by $3$. In each trio of numbers, the first one can be a
     * rational and will represent the coefficient associated to a power of the
     * $y$ variable; the second one is the exponent of the $x$ variable, and
     * the third one is the exponent of the $x$ variable.
     * 
     * In short, each term will have the form $a \cdot x^b \cdot y^c$, where
     * $a$ is rational, and $b$ and $c$ are integers; you can input such a
     * polynomial as a string `a b c`.
     * 
     * For example, $x^2 \cdot y^2 + 4 x \cdot y^3 -9/3 \cdot y + 4 x \cdot y$
     * can be input as `1 2 2 4 0 3 -9/3 0 1 4 1 1`.
     */
    SndPoly operator=(std::string str);

    //***UTILS***

    void order_poly();

    void clear();

    bool isZero();

    //***ARITHMETIC OPERATIONS***

    /**
     * @brief Adds two polynomials together.
     * 
     * This function performs the addition of two polynomials. It does so by
     * adding the polynomials with the same y exponent.
     * 
     * @param other The polynomial to add to this polynomial
     * @return A new SndPoly object representing the sum of the two polynomials
     */
    SndPoly operator+(const SndPoly& other) const;

    SndPoly operator-() const;

    SndPoly operator-(const SndPoly& other) const;

    friend SndPoly operator*(const SndPoly& poly, const SndPolyTerm& term);

    friend SndPoly operator*(const Integer num, const SndPoly& poly);

    friend SndPoly operator/(const SndPoly& dividend, const Polynomial& divisor);

    Integer getUnit() const;

    Polynomial getCont() const;

    SndPoly getPrimitivePart() const;

    /**
     * @brief Computes the greatest common divisor of two polynomials (with
     * two variables).
     * 
     * - The unit is defined as the sign of the leading coefficient of the
     * leading polynomial.
     */
    SndPoly gcd(const SndPoly& lhs, const SndPoly& rhs);
};