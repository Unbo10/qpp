#pragma once

#include <bits/stdc++.h>
#include "../Numbers/Rational.h"

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

        friend PolyTerm operator+(const PolyTerm& term1, const PolyTerm& term2) {
            if(term1.exp != term2.exp) throw std::invalid_argument("The terms must have the same exponent for them to be added");
            
            PolyTerm result;
            result.coeff = term1.coeff + term2.coeff;
            result.exp = term1.exp;
            return result;
        }

        friend PolyTerm operator*(const PolyTerm& term1, const PolyTerm& term2) {
            PolyTerm prod;
            prod.coeff = term1.coeff * term2.coeff;
            prod.exp = term1.exp + term2.exp;
            return prod;
        }
        
        //***ISTREAM AND OSTREAM***

        friend std::ostream& operator<<(std::ostream& os, const PolyTerm& term) {
            os << term.coeff << "x^" << term.exp;
            return os;
        }
};