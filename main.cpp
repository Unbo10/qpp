#include <iostream>
#include "Numbers/Integer.cpp"
#include "Numbers/Number.cpp"
#include "Numbers/Rational.cpp"

int main() {
    Integer u = 100, v = 9;
    std::cout << u/v << " is equal to " << 100 / 9 << "\n";

    Integer a = 10000, b = 100;
    // std::cout << a * b << "\n";

    // std::cout << u * v << "\n";

    // Integer m = 7000, m2 = 4500, k = -1;
    // List<Integer> gcd = Integer::extendEuclidean(m, m2);

    // std::cout << gcd[0] << " =? " << m*gcd[1] + m2*gcd[2];
}