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
    // Vector vv;
    // vv.appendComponent(1);
    // vv.appendComponent(2);
    // vv.appendComponent(3);
    // std::cout << -vv << "\n:";

    std::cout << "Matrix mm\n";
    // Matrix m;
    // std::cin >> m;
    // // 3
    // // 1 2 3
    // // 4 5 6
    // // 7 8 9
    // std::cout << m << "\n";

    // std::string str = "4\n1 2 6 7\n3 4 0 -1\n-5 -6 -1/2 -3\n0 1 -1 0";
    // std::string str = "7\n1 2 6\n3 4 0\n-5 -6 -1/2\n0 1 -1\n1 2 6\n3 4 0\n-5 -6 -1/2";
    // str = "3\n1 2 5 6 7 -1 2\n3 4 -1/2 2 -5 6 8\n5 -1 0 6 0 0 1\n";

    Matrix m1, m2;
    std::string str = "7\n1 2 6\n3 4 0\n-5 -6 -1/2\n0 1 -1\n1 2 6\n3 4 0\n-5 -6 -1/2";
    std::istringstream iss1(str);
    iss1 >> m1;
    str = "3\n1 2 5 6 7 -1 2\n3 4 -1/2 2 -5 6 8\n5 -1 0 6 0 0 1\n";
    std::istringstream iss2(str);
    iss2 >> m2;
    std::cout << "Matrix 1:\n";
    std::cout << m1 << "\n" << "*\n";
    // std::cout << -m1 << "\n";
    std::cout << "Matrix 2:\n";
    std::cout << m2 << "\n\n";
    Matrix mm = Matrix::strassenMm(m1, m2);
    std::cout << "Final result of Strassen's mm:\n";
    std::cout << mm << "\n";
    std::cout << "Actual result: \n";
    std::cout << m1*m2 << "\n\n";

    Matrix m3, m4;
    std::string str3 = "2\n1 2 3\n4 5 6";
    std::istringstream iss3(str3);
    iss3 >> m3;
    std::string str4 = "3\n1 2\n3 4\n5 6";
    std::istringstream iss4(str4);
    iss4 >> m4;
    std::cout << "Matrix 3 (2x3):\n";
    std::cout << m3 << "\n";
    std::cout << "Matrix 4 (3x2):\n";
    std::cout << m4 << "\n";
    std::cout << "Result with L-W: \n";
    std::cout << Matrix::ladermanMm(m4, m3) << "\n\n";
    std::cout << "Using Strassen: \n";
    std::cout << Matrix::strassenMm(m4, m3) << "\n\n";
    std::cout << "Actual result:\n";
    std::cout << m4 * m3 << "\n";

    Matrix m5, m6;
    std::string str5 = "7\n1/2 2 3 4/3 5 6 7 8\n9 10/7 11 12 13 -14/5 15 16\n17 18 19/2 20 21 22 -23/4 24\n25 26 27 28/9 29 30 31 32\n33 -34/11 35 36 37 38 39/6 40\n41 42 43 44 45 -46/13 47 48\n49 50 51/8 52 53 54 55 56";
    std::istringstream iss5(str5);
    iss5 >> m5;
    std::string str6 = "8\n1 2/3 3 4 5 6 7\n8 9 10 11/7 12 13 14\n15 16 -17/2 18 19 20 21\n22 23 24 25 26/5 27 28\n29 30 31 -32/9 33 34 35\n36 37 38 39 40 41/4 42\n43 44 -45/11 46 47 48 49\n50 51 52 53 54/6 55 56";
    std::istringstream iss6(str6);
    iss6 >> m6;
    std::cout << "Matrix 5 (7x8):\n";
    std::cout << m5 << "\n";
    std::cout << "Matrix 6 (8x7):\n";
    std::cout << m6 << "\n";
    std::cout << "Result with L-W: \n";
    std::cout << Matrix::ladermanMm(m5, m6) << "\n\n";
    std::cout << "Using Strassen: \n";
    std::cout << Matrix::strassenMm(m5, m6) << "\n\n";
    std::cout << "Actual result:\n";
    std::cout << m5 * m6 << "\n";
    std::cout << "Are Laderman and Strassen results equal? " << (Matrix::ladermanMm(m5, m6) == Matrix::strassenMm(m5, m6)) << std::endl;
    std::cout << "Are Laderman and actual results equal? " << (Matrix::ladermanMm(m5, m6) == (m5 * m6)) << std::endl;
    std::cout << "Are Strassen and actual results equal? " << (Matrix::strassenMm(m5, m6) == (m5 * m6)) << std::endl;

    std::cout << "Computing the inverse of the hardcoded matrix for Toom Cook 4's implementation\n";
    //*Evaluating at r = 1, -1, 2, -2, 3, -3, and infty returns us the following coefficients if the polynomial in question is V(r) = C_0 + C_1 r + C_2 r^2 + C_3 r^3 + C_4 r^4 + C_5 r ^5 + C_6 r^6
    //*When r = 0:  C_0
    //*When r = -1: C_0 - C_1   + C_2   - C_3    + C_4    - C_5     + C_6
    //*When r = 1:  C_0 + C_1   + C_2   + C_3    + C_4    + C_5     + C_6
    //*When r = 2:  C_0 + 2*C_1 + 4*C_2 + 8*C_3  + 16*C_4 + 32*C_5  + 64*C_6
    //*When r = -2: C_0 - 2*C_1 + 4*C_2 - 8*C_3  + 16*C_4 - 32*C_5  + 64*C_6
    //*When r = 3:  C_0 + 3*C_1 + 9*C_2 + 27*C_3 + 81*C_4 + 243*C_5 + 729*C_6
    //*When r = -3: C_0 - 3*C_1 + 9*C_2 - 27*C_3 + 81*C_4 - 243*C_5 + 729*C_6
    //*When r = infty:                                                C_6 (coefficient of highest degree term)
    //*This system of equations can be represented using an Ax product, where A is the matrix of coefficients and x is the vector of C_i. That way, A should be the following:
    std::string coeff = "7\n1 0 0 0 0 0 0\n1 -1 1 -1 1 -1 1\n1 1 1 1 1 1 1\n1 2 4 8 16 32 64\n1 -2 4 -8 16 -32 64\n1 3 9 27 81 243 729\n1 -3 9 -27 81 -243 729\n0 0 0 0 0 0 1";
    std::istringstream issA(coeff);
    Matrix A;
    issA >> A;
    std::cout << "Original matrix:\n";
    std::cout << A << "\n\n";
    std::cout << "Inverse:\n";
    std::cout << A.inverse(A) << "\n"; //!Inverse should be static
    //*Resulting matrix
    //TODO: Confirm with another CAS
    // [[1, 0, 0, 0, 0, 0, 0],
    // [0, -3/4, 3/4, -3/20, 3/20, 1/60, -1/60],
    // [-49/36, 3/4, 3/4, -3/40, -3/40, 1/180, 1/180],
    // [0, 13/48, -13/48, 1/6, -1/6, -1/48, 1/48],
    // [7/18, -13/48, -13/48, 1/12, 1/12, -1/144, -1/144],
    // [0, -1/48, 1/48, -1/60, 1/60, 1/240, -1/240],
    // [-1/36, 1/48, 1/48, -1/120, -1/120, 1/720, 1/720]]
    //* or:
    std::string expectedInverse = "7\n1 0 0 0 0 0 0\n0 -3/4 3/4 -3/20 3/20 1/60 -1/60\n-49/36 3/4 3/4 -3/40 -3/40 1/180 1/180\n0 13/48 -13/48 1/6 -1/6 -1/48 1/48\n7/18 -13/48 -13/48 1/12 1/12 -1/144 -1/144\n0 -1/48 1/48 -1/60 1/60 1/240 -1/240\n-1/36 1/48 1/48 -1/120 -1/120 1/720 1/720";
    std::istringstream issAInverse(expectedInverse);
    std::cout << "Hardcoded Inverse\n";
    Matrix IA;
    issAInverse >> IA;
    std::cout << IA << "\n\n";
    std::cout << "Are they equal? " << (A.inverse(A) == IA) << "\n";

    Rational num1(0), num2(0);
    std::cout << (num1 == num2) << "\n";

    std::cout << "Toom-Cook 4\n";
    Integer nat1(12345678);
    std::cout << nat1.splitIn4() << "\n"; 
    Integer nat2(10000000);
    std::cout << nat2.splitIn4() << "\n";
    std::cout << Integer::toomCook4(nat1, nat2) << "\n";

    std::cout << (Integer(2)^2) << "\n";

}

//*You can run main copying and running the following command in the terminal:
//* ->Linux: ./run.sh src/*.cpp src/LinearAlgebra/*.cpp main.cpp
//* ->Windows: run.bat src\*.cpp src\LinearAlgebra\*.cpp main.cpp