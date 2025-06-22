#include <bits/stdc++.h>
#include "../include/Integer.h"
#include "../include/Rational.h"
#include "SndPoly.h"

int main() {
    Rational r("-5/2"), r2(0);
    std::cout << r << "\n";
    Integer i("-0"); //*Still ads the negative sign, but it's fine for now
    std::cout << i << "\n";
    std::cout << (r2 != 0) << "\n";

    SndPoly poly;
    poly = "1 2 2 4 0 3 -9/3 0 1 4 1 1";
    // std::cout << poly << "\n";
    //x^2 \cdot y^2 + 4 \cdot y^3 -9/3 \cdot y + 4 x \cdot y

    SndPoly poly1, poly2;
    poly1 = "-2 2 2 3 4 6 2 0 1 -1/2 2 1";
    poly2 = "2 2 2 -6 4 6 -5/2 0 1 2 2 1";
    std::cout << poly1 << "\n";
    std::cout << "+\n";
    std::cout << poly2 << "\n";
    std::cout << "---------------------------------\n";
    std::cout << poly1 + poly2 << "\n";
}