#include <iostream>
#include <sstream>
#include "include/Natural.h"
#include "include/Integer.h"
#include "include/Rational.h"

int main() {
    Rational pi(3.141596), e(2.7198247);

    std::cout << pi*e;
}