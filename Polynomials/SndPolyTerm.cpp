#include "SndPolyTerm.h"

//***UTILS***

bool SndPolyTerm::isZero() {
    if(poly.isZero()) {
        exp = 0;
        return true;
    }
    return false;
}

//***STREAM OPERATIONS***

std::ostream& operator<<(std::ostream& os, const SndPolyTerm& term) {
    os << "(" << term.poly << ")" << SndPolyTerm::sndVar << "^" << term.exp;
    return os;
}

//***ARITHMETIC OPERATIONS***

SndPolyTerm SndPolyTerm::operator+(const SndPolyTerm& other) {
    SndPolyTerm result(*this);
    result.poly = result.poly + other.poly;
    return result;
}

SndPolyTerm SndPolyTerm::operator-() const {
    return SndPolyTerm(-(this->poly), this->exp);
}

SndPolyTerm SndPolyTerm::operator-(const SndPolyTerm& other) {
    return (*this) + (-other);
}

SndPolyTerm SndPolyTerm::operator*(const SndPolyTerm& other) {
    SndPolyTerm result;
    result.poly = this->poly * other.poly;
    result.exp = this->exp + other.exp;
    return result;
}

SndPolyTerm SndPolyTerm::operator/(const SndPolyTerm& other) const {
    if(other.exp - this->exp < 0)
        throw std::invalid_argument("Divisor has greater degree than dividend");
    
    SndPolyTerm result;
    result.exp = other.exp - this->exp;
    result.poly = other.poly / this->poly;

    return result;
}
