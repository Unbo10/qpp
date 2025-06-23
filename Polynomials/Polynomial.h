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

public:
    int degree = 0;
    std::vector<Rational> dense;  //*Dense representation: coefficients indexed by power
    std::vector<PolyTerm> sparse;  //*Sparse representation: [coefficient, power] pairs

    Polynomial();

    Polynomial(const PolyTerm& term);

    Polynomial(const std::string& str);

    Polynomial(const Polynomial& other);
        
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

    Polynomial operator-() const;

    Polynomial operator-(const Polynomial& other) const;

    Polynomial operator*(const Polynomial& other);

    friend Polynomial operator*(const Polynomial& lhs, const Polynomial& rhs);
    
    friend Polynomial operator*(const Polynomial& poly, const Integer& num);

    Polynomial operator/(const Polynomial& other);
    
    Polynomial to_integer_poly();

    //***INTEGER POLYNOMIALS***
    Integer find_gcd_of_poly_terms();

    Integer find_lcm_of_poly_terms();

    //***RATIONAL POLYNOMIALS***

    static Polynomial remainder(const Polynomial& dividend, const Polynomial& divisor);

    Integer content();

    Polynomial primitive_part();

    std::pair<Polynomial, Polynomial> divide_by(const Polynomial& divisor) const;

    static Polynomial pseudoquotient(Polynomial u, Polynomial v);

    static Polynomial pseudoremainder(Polynomial u, Polynomial v);

    static Polynomial primitivePolyGCD(Polynomial u, Polynomial v);

    static Polynomial monicPolyGCD(Polynomial u, Polynomial v);
};