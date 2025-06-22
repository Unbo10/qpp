#include "SndPolyTerm.h"

//***STREAM OPERATIONS***

std::ostream& operator<<(std::ostream& os, const SndPolyTerm& term) {
    os << "(" << term.poly << ")" << SndPolyTerm::sndVar << "^" << term.exp;
    return os;
}