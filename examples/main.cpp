#include <bits/stdc++.h>
#include "../include/Integer.h"
#include "../include/Rational.h"
#include "../include/Polynomials/Polynomial.h"

int main() {
    Rational r("-5/2"), r2(0), r3(78, 5);
    std::cout << r << "\n";
    Integer i("-0"), i1(-130); //*Still ads the negative sign, but it's fine for now
    std::cout << i << "\n";
    std::cout << (r2 != 0) << "\n";
    std::cout << r2 << "+" << r3 << "=" << r2 + r3 << "\n";
    std::cout << "\n";

    // Polynomial oPoly1, oPoly2, oPoly3;
    // oPoly1 = "1 2 3 1 2 0";
    // oPoly2 = "1 1";
    // std::cout << oPoly1 << "\n";
    // std::cout << "awefa\n";
    // std::cout << (oPoly2^3) << "\n";
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
    Polynomial poly5, poly6, poly7, poly8, poly9, poly10, poly11, poly12;
    poly5 = "1 1 -26/15 0";
    poly6 = "1 2 -5/3 1";
    poly7 = "2 3 3 2 -10 1 8 0";
    poly8 = "1 1 2 0";
    poly9 = "1 2 -3 1 2 0";
    poly10 = "1 3 -2 2 -1 1 2 0";
    poly11 = "1/2 3 -6 2 11/2 1 -6 0";
    poly12 = "1 2 -3/2 1 1 0";
    std::cout << poly6 << "\n/\n" << poly5 << "\n";
    std::cout << "Remainder: " << Polynomial::remainder(poly6, poly5) << "\n";
    std::cout << "Division: " << poly6 / poly5 << "\n";
    std::cout << poly7 << "\n/\n" << poly8 << "\n";
    std::cout << "Remainder: " << Polynomial::remainder(poly7, poly8) << "\n";
    std::cout << "Division : " << poly7 / poly8 << "\n";
    // std::cout << "GCD of " << poly5 << " and " << poly6 << " is: \n";
    // Polynomial gcd = Polynomial::monicPolyGCD(poly5, poly6);
    // std::cout << "|" << gcd << "\n";
    // std::cout << "GCD of " << poly9 << " and " << poly10 << " is: " << Polynomial::monicPolyGCD(poly9, poly10) << "\n";
    // std::cout << "GCD of " << poly11 << " and " << poly12 << " is: " << Polynomial::monicPolyGCD(poly11, poly12) << "\n";
}