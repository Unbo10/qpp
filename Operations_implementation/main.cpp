#include <iostream>
#include <sstream>
#include "../Numbers/Integer.cpp"
#include "../Numbers/Number.cpp"
// #include "../Numbers/Rational.h"
// #include "../Numbers/Rational.cpp"
#include "../utils/OrderedList.cpp"

int main() {
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
    // Integer num1 = 17, num2 = 9;
    // Rational num(num1, num2);

    // std::cout << num << std::endl;

    // Rational num3(6, 3);

    // std::cout << num3;
}