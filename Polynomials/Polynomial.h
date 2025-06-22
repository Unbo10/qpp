#pragma once

#include <iostream>
#include <vector>

#include "PolyTerm.h"

class Polynomial {
private:
bool is_dense_valid = false;
bool is_ordered = false;
bool is_rational = false;
bool is_sparse_valid = false;
int degree = 0;

public:
    std::vector<Rational> dense;  //*Dense representation: coefficients indexed by power
    std::vector<PolyTerm> sparse;  //*Sparse representation: [coefficient, power] pairs

    Polynomial() = default;

    Polynomial(PolyTerm& term);

    Polynomial(const std::string& str);

    // Get maximum degree of the polynomial
    
    void printPolynomial();
    
    //***UTILS***
    
    void clear();
    
    bool isZero() const;

    int getDegree();

    //*Sorts them in descending order (greatest to smallest exponent)
    void order_poly();

    Rational get_leading_coefficient() const;

    //***OSTREAM AND ISTREAM***

    Polynomial operator=(const Polynomial& other);

    Polynomial operator=(std::string str);

    Polynomial update_sparse();

    Polynomial update_dense();

    friend std::istream& operator>>(std::istream& is, Polynomial& poly);

    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);

    //***COMPARISON OPERATIONS***

    // std::istream& operator>>(std::istream& is, const Polynomial& other) {

    // }

    //***ARITHMETIC OPERATIONS***

    Polynomial multiply_by_single_term_poly(const PolyTerm& singleTerm);

    Polynomial multiply_by_single_term_poly(const Polynomial& singleTerm);

    Polynomial operator+(const Polynomial& other) const;

    friend Polynomial operator+(const Polynomial& poly, PolyTerm& term);

    Polynomial to_integer_poly();

    //***INTEGER POLYNOMIALS***
    Integer find_gcd_of_poly_terms();

    Integer find_lcm_of_poly_terms();

    Polynomial operator/(const Polynomial& other);

    //***RATIONAL POLYNOMIALS***

    Polynomial remainder(const Polynomial& divisor) const;

    Integer content();

    Polynomial primitive_part();

    std::pair<Polynomial, Polynomial> divide_by(const Polynomial& divisor) const;

    Polynomial pseudoquotient(Polynomial u, Polynomial v);

    Polynomial pseudoremainder(Polynomial u, Polynomial v);

    Polynomial primitivePolyGCD(Polynomial u, Polynomial v);

    Polynomial monicPolyGCD(Polynomial u, Polynomial v);
};