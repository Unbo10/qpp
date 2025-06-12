#include <iostream>
#include <sstream>
#include "include/Natural.h"
#include "include/Integer.h"

int main() {
    Natural num(11062401249);
    Integer x(num);

    std::cout << x;
}