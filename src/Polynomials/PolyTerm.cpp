#include "../../include/Polynomials/PolyTerm.h"

//***ARITHMETIC OPERATIONS***

PolyTerm operator+(const PolyTerm& term1, const PolyTerm& term2) {
    if(term1.exp != term2.exp) throw std::invalid_argument("The terms must have the same exponent for them to be added");
    
    PolyTerm result;
    result.coeff = term1.coeff + term2.coeff;
    result.exp = term1.exp;
    return result;
}

PolyTerm operator*(const PolyTerm& term1, const PolyTerm& term2) {
    PolyTerm prod;
    prod.coeff = term1.coeff * term2.coeff;
    prod.exp = term1.exp + term2.exp;
    return prod;
}

//***ISTREAM AND OSTREAM***

std::ostream& operator<<(std::ostream& os, const PolyTerm& term) {
    os << term.coeff << "x^" << term.exp;
    return os;
}
