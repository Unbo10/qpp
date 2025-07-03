#include <iostream>

#include "include/LinearAlgebra/Matrix.h"


int main()
{
    Rational x(3.19862312);
    Rational::decimalPoints = 100;
    std::cout << x;
}