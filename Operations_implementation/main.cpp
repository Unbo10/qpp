#include <iostream>
#include <sstream>
#include "../Numbers/Integer.cpp"
#include "../Numbers/Number.cpp"
#include "../Numbers/Rational.h"
#include "../Numbers/ClasesImplementation/Rational.cpp"
#include "../utils/OrderedList.cpp"

int main() {
    Integer n1 = 1, n2 = 2;
    //std::cout << (0 < n1) << "\n";
    std::cout << Integer::binaryEcludian(n1, n2) << "\n";
    Rational num(1, 2);
    std::cout << num;
    return 0;
}