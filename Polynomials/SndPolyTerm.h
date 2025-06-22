#pragma once

#include "Polynomial.h"
#include "../include/Rational.h"

class SndPolyTerm {
public:
    const static char firstVar = 'x';
    const static char sndVar = 'y';
    Polynomial poly;
    int exp;

    SndPolyTerm() = default;
    SndPolyTerm(const Polynomial polynomial, const int y_exp) : poly(polynomial), exp(y_exp) {}

    //***STREAM OPERATIONS***

    friend std::ostream& operator<<(std::ostream& os, const SndPolyTerm&);
};