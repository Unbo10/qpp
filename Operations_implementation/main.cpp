#include <iostream>
#include <sstream>
#include "../Numbers/Integer.cpp"
#include "../Numbers/Number.cpp"
 #include "../Numbers/Rational.h"
 #include "../Numbers/ClasesImplementation/Rational.cpp"
#include "../utils/OrderedList.cpp"

int main() {
    Integer n1 = 1, n2 = 1;

    for(int i = 150; i <= 200; i++)
    {
        n1 = n1*i;
        n2 = n2*(i-50);
    }

    std::cout << n1 << "\n" << n2 << "\n";

    std::cout << n1/n2;
}