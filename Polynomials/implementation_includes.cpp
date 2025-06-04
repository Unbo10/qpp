#include <bits/stdc++.h>

#include "../Numbers/Rational.h"
#include "Polynomial.h"
#include "PolyTerm.h"

int main() {
    //***RATIONALS***
    Rational n1(-3, 1);
    Rational n2(1, 1);
    Rational n3(1, 1);

    std::cout << (- n1) - (n2 * n3) << "\n";

    //***POLYNOMIALS***

    // Polynomial poly1, poly2;
    // poly1 = "5 4 -1 1 2 0";
    // poly2 = "1 2 1 1 -1 0";
    // poly1.printPolynomial();
    // poly2.printPolynomial();

    // std::cout << "\nPOLYNOMIAL DIVISION\n";
    // // poly1 = "3 4 7 0";
    // // poly2 = "4 1 -1 0";
    // // poly1.printPolynomial();
    // // poly2.printPolynomial();
    // Polynomial poly3 = poly1 / poly2;
    // std::cout << poly3 << "\n";
    // return 0;
}