#include <iostream>

#include "include/LinearAlgebra/Matrix.h"


int main()
{
    std::cout << Rational(8, 4)*Rational(16, 16) << std::endl;
    std::cout << Rational(3, 2)<< std::endl;
    std::cout << Rational(3, 2) - Rational(8, 4)*Rational(16, 16);

    return 0;
}