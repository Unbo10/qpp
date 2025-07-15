#include <iostream>

#include "include/LinearAlgebra/Matrix.h"


int main()
{
    Rational x(2, 1);
    //Rational::decimalPoints = 100;
    showFraction(x^Rational(1, 2));
    std::cout << "  "<< (x^Rational(1, 2));
}