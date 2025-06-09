#include <iostream>
#include <sstream>
#include "Numbers/Integer.h"
#include "Numbers/Number.h"
#include "Numbers/Rational.h"
#include "utils/OrderedList.h"
#include "include/Natural.h"

int main() {
    Natural num1(157), num2(366);

    std::cout << num1 + num2;
}