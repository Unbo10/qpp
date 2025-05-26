#include <iostream>
#include "../Numbers/Integer.cpp"
#include "../Numbers/Number.cpp"
#include "../Numbers/Rational.h"
#include "../utils/OrderedList.cpp"

int main() {
    Rational n1 = 4;

    std::cout << n1.power(.5);
}