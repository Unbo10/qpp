#include <iostream>
#include "../Numbers/Integer.cpp"
#include "../Numbers/Number.cpp"
#include "../Numbers/Rational.h"
#include "../utils/OrderedList.cpp"




int main() {
    Integer num1 = 17, num2 = 9;
    Rational num(num1, num2);

    std::cout << num << std::endl;

    Rational num3(6, 3);

    std::cout << num3;
}