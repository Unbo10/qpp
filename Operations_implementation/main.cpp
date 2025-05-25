#include <iostream>
#include <sstream>
#include "../Numbers/Integer.cpp"
#include "../Numbers/Number.cpp"
// #include "../Numbers/Rational.cpp"
#include "../utils/OrderedList.cpp"

int main() {
    //*Ordered list
    // OrderedList<Integer> sorted;
    // Integer num = 15;
    // sorted.add(15);
    // sorted.add(2);
    // sorted.add(18);
    // sorted.add(16);

    // OrderedList<Integer>::cleanBlanckSpaces(sorted);
    // sorted.replace(12, 1);
    // std::cout << sorted;

    //*Operations
    Integer a(2), b(10);
    a = b;
    // a %= b;
    std::cout << (a != b) << "\n";
    std::cout << a*b << "\n";

    // Integer exp(10);
    // for(int i = 0; i < 10; i++) {
    //     std::cout << (exp ^ 5) << "\n";
    // }

    //!ISSUES FOUND
    //!19 divided by 10
    //!-10 modulo -2
    //!Exponentiation and division (and therefore modulo) are taking too long. The rest of the operations seem fine

    //***RATIONALS***
    // Rational rational;
    // std::cin >> rational;
    // std::cout << rational;
}