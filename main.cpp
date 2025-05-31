#include <iostream>
#include <sstream>
#include "Numbers/Integer.h"
#include "Numbers/Number.h"
#include "Numbers/Rational.h"
#include "utils/OrderedList.h"

int main() {
    Integer n1 = 1, n2 = 1;

    for(int i = 150; i <= 200; i++)
    {
        n1 = n1*i;
        n2 = n2*(i-50);
    }

    std::cout << n1 << "\n" << n2 << "\n";

    std::cout << n1/n2 << "\n";

    std::cout << Integer(8) * Integer(9) << "\n";
}