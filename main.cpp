#include <iostream>
#include <sstream>
#include "include/Integer.h"
#include "include/Number.h"
#include "include/Rational.h"
#include "utils/OrderedList.h"
#include "include/Natural.h"
#include "include/LinearAlgebra/Vector.h"
#include "include/LinearAlgebra/Matrix.h"

int main() {
    Rational pi(3.14159265358979323), e(2.71828182846);
    std::cout << pi*e << std::endl;
    std::cout << pi/e << std::endl;
    Vector x({pi, e});
    std::cout << x << std::endl;
    std::cout << norm(x) << std::endl;
}