#include <iostream>
#include <sstream>
#include "../Numbers/Integer.cpp"
#include "../Numbers/Number.cpp"
#include "../Numbers/Rational.h"
#include "../Numbers/ClasesImplementation/Rational.cpp"
#include "../utils/OrderedList.cpp"

int main() {
    Rational num1(-3,1), num2(1,1), num3(1,1);

    std::cout << num1 << "  -  " << num2 << "\n";

    std::cout << num1-(num2*num3);
    return 0;
}