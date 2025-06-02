#include <iostream>
#include <sstream>
#include "../Numbers/Integer.cpp"
#include "../Numbers/Number.cpp"
#include "../Numbers/Rational.h"
#include "../Numbers/ClasesImplementation/Rational.cpp"
#include "../utils/OrderedList.cpp"

int main() {
    Integer tres = -3;
    Rational num1(tres), num2(1);

    std::cout << num1 << "  -  " << num2 << "\n";

    std::cout << num1-num2*num2;
    return 0;
}