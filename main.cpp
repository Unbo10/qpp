#include <iostream>
#include <sstream>
#include "include/LinearAlgebra/Vector.h"

int main() {
    Rational number(1, 1);
    Rational::decimalPoints = 10000;
    while(number != 0)
    {
        std::cout << number << std::endl;
        number = number/2;
    }
}