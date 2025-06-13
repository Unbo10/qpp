#include <iostream>
#include <sstream>
#include "include/LinearAlgebra/Vector.h"

int main() {
    Vector x(10);

    for(int i = 0; i < 10; i++)
        x.replace(Rational(1, 50), i);

    std::cout << x << std::endl;
}