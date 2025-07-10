#include <iostream>
#include <sstream>
#include "include/LinearAlgebra/Matrix.h"

int main() {
    Rational x(2, 1), y(1, 4);
    std::cout << y << std::endl;
    std::cout << x.toDouble() << "  " << y.toDouble() << std::endl;
    showFraction(x^y);
}