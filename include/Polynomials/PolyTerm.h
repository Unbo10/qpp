#pragma once

#include <iostream>
#include "../Rational.h"

class PolyTerm {
    public:
        Rational coeff;
        //!ISSUE WHEN ORDERING INTEGERS
        int exp;

        PolyTerm() : coeff(Rational(0)), exp(0) {}
        PolyTerm(Rational coeff, int exp) : coeff(coeff), exp(exp) {}
        PolyTerm(Integer coeff, int exp) : coeff(Rational(coeff, Integer(1))), exp(exp) {}
        PolyTerm(int coeff, int exp) : coeff(Rational(coeff)), exp(exp) {}
        ~PolyTerm() {}

        //***ARITHMETIC OPERATIONS***

        friend PolyTerm operator+(const PolyTerm& term1, const PolyTerm& term2);

        friend PolyTerm operator*(const PolyTerm& term1, const PolyTerm& term2);
        
        //***ISTREAM AND OSTREAM***

        friend std::ostream& operator<<(std::ostream& os, const PolyTerm& term);
};