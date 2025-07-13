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
    //*The approximation could be done by calculating one more decimal place and approximate if necessary
    Vector x({pi, e});
    std::cout << x << std::endl;
    std::cout << norm(x) << std::endl;

    int n = 251;
    std::cout << Natural::smallestGeqPowerOfBase(n, 2) << "\n";

    Rational p;
    std::cout << "Rational\n";
    // std::cin >> p;
    // std::cout << p << "\n";

    // Vector v;
    // std::cin >> v;
    // std::cout << v << "\n";

    std::cout << "Matrix mm\n";
    // Matrix m;
    // std::cin >> m;
    // // 3
    // // 1 2 3
    // // 4 5 6
    // // 7 8 9
    // std::cout << m << "\n";

    // std::string str = "4\n1 2 6 7\n3 4 0 -1\n-5 -6 -1/2 -3\n0 1 -1 0";

    Matrix m1, m2;
    std::string str = "7\n1 2 6\n3 4 0\n-5 -6 -1/2\n0 1 -1\n1 2 6\n3 4 0\n-5 -6 -1/2";
    std::istringstream iss1(str);
    iss1 >> m1;
    str = "3\n1 2 5 6 7 -1 2\n3 4 -1/2 2 -5 6 8\n5 -1 0 6 0 0 1\n";
    std::istringstream iss2(str);
    iss2 >> m2;
    std::cout << "Matrix 1:\n";
    std::cout << m1 << "\n" << "*\n";
    std::cout << "Matrix 2:\n";
    std::cout << m2 << "\n\n";
    Matrix mm = Matrix::strassenMm(m1, m2);
    std::cout << "Final result of mm:\n";
    std::cout << mm << "\n";
    std::cout << "Using the usual algorithm: \n";
    std::cout << m1*m2 << "\n";
}

//*You can run main copying and running the following command in the terminal:
//* ->Linux: ./run.sh src/*.cpp src/LinearAlgebra/*.cpp main.cpp
//* ->Windows: run.bat src\*.cpp src\LinearAlgebra\*.cpp main.cpp