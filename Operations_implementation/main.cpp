#include <iostream>
#include <sstream>
#include "../Numbers/Integer.cpp"
#include "../Numbers/Number.cpp"
#include "../Numbers/Rational.h"
#include "../Numbers/ClasesImplementation/Rational.cpp"
#include "../utils/OrderedList.cpp"

int main() {
    Integer n1 = 6, n2 = 3;
    //std::cout << (0 < n1) << "\n";
    std::cout << Integer::binaryEcludian(n1, n2) << "\n";
    //std::cout << n1/n2 << "\n";
    Rational num(-6, 3);
    std::cout << num;
    return 0;
}