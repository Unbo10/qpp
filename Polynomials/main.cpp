#include <bits/stdc++.h>
#include "../include/Integer.h"
#include "../include/Rational.h"
#include "SndPoly.h"

int main() {
    Rational r("-5/2"), r2(0), r3(78, 5);
    std::cout << r << "\n";
    Integer i("-0"), i1(-130); //*Still ads the negative sign, but it's fine for now
    std::cout << i << "\n";
    std::cout << (r2 != 0) << "\n\n";
    std::cout << r2 << "*" << r3 << "=" << r2 + r3 << "\n";

    // Polynomial oPoly1, oPoly2, oPoly3;
    // oPoly1 = "1 2 3 1 2 0";
    // oPoly2 = "1 0";
    // std::cout << oPoly1 << "\n";
    // std::cout << oPoly2 << "\n";
    // std::cout << oPoly1 * oPoly2 << "\n";
    // std::cout << "awefawe\n";
    // std::cout << oPoly1 -oPoly2 << "\n";

    // SndPoly poly;
    // poly = "1 2 2 4 0 3 -9/3 0 1 4 1 1";
    // std::cout << poly << "\n";
    // // x^2 \cdot y^2 + 4 \cdot y^3 -9/3 \cdot y + 4 x \cdot y

    // //*Subtraction and addition tests
    // SndPoly poly1, poly2;
    // poly1 = "-2 2 2 3 4 6 2 0 1 -1/2 2 1";
    // poly2 = "2 2 2 -6 4 6 -5/2 0 1 2 2 1";
    // std::cout << poly1 << "\n";
    // std::cout << "-\n";
    // std::cout << poly2 << "\n";
    // std::cout << "---------------------------------\n";
    // std::cout << poly1 - poly2 << "\n";

    // //*Multiplication tests
    // std::cout << "\n";
    // poly1 = "-2 2 2 2 0 1 -1/2 2 1";
    // SndPolyTerm term1;
    // term1.poly = "0 0";
    // term1.exp = 1;
    // std::cout << poly1 << "\n";
    // std::cout << "*\n";
    // std::cout << term1 << "\n";
    // std::cout << "---------------------------------\n";
    // std::cout << poly1 * term1 << "\n";

    //*GCD tests
    Polynomial poly5, poly6, poly7, poly8;
    poly5 = "75 1 -130 0";
    poly6 = "135 2 -225 1";
    poly7 = "2 3 3 2 -10 1 8 0";
    poly8 = "1 1 2 0";
    std::cout << "Remainder: " << Polynomial::remainder(poly6, poly5) << "\n";
    std::cout << "Remainder: " << Polynomial::remainder(poly7, poly8) << "\n";
    // std::cout << "GCD of " << poly5 << " and " << poly6 << " is: \n";
    // Polynomial gcd = Polynomial::monicPolyGCD(poly5, poly6);
    // std::cout << "|" << gcd << "\n";
    // SndPoly poly3;
    // poly3 = "125 0 2 -75 1 2 135 2 1 -225 1 1 30 3 0 -50 2 0";
    // std::cout << poly3 << "\n";
    // std::cout << poly3.getUnit() << "\n";
    // std::cout << poly3.getCont() << "\n";
}