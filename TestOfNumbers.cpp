#include <iostream>

#include "include/LinearAlgebra/Matrix.h"


int main()
{
    std::cout << Rational(-1155 , 35522)*3 + Rational(-1774, 17761) * Rational(1, 4) << std::endl;
    Rational result = Rational(-1155 , 35522)*3 + Rational(-1774, 17761) * Rational(1, 4);
    showFraction(result);
    std::cout << std::endl;
    std::cout << result + Rational(816, 17761) * Rational(8, 3) << std::endl;
    std::cout << Rational(-1155 , 35522)*3 + Rational(-1774, 17761) * Rational(1, 4) + Rational(816, 17761) * Rational(8, 3);
    return 0;
}