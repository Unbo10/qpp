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

//*You can run main copying and running the following command in the terminal:
//* ->Linux: ./run.sh src/*.cpp src/LinearAlgebra/*.cpp main.cpp
//* ->Windows: run.bat src\*.cpp src\LinearAlgebra\*.cpp main.cpp
    Matrix m1(4, 4);

    m1[0][0] = Rational(11);       
    m1[0][1] = Rational(4, 5);    
    m1[0][2] = Rational(3);      
    m1[0][3] = Rational(-2);      

    m1[1][0] = Rational(1, 2);    
    m1[1][1] = Rational(7);         
    m1[1][3] = Rational(5);       

    m1[2][0] = Rational(-3);        
    m1[2][1] = Rational(2);        
    m1[2][2] = Rational(1, 4);     
    m1[2][3] = Rational(6);         
     
    m1[3][1] = Rational(9);         
    m1[3][2] = Rational(8, 3);      
    m1[3][3] = Rational(-1);        

    //std::cout << m1 << "\n"<< std::endl;
    Matrix x = Matrix::scalonadeForm(m1);
    // printWithoutBracketsAndFractionForm(x);
    // printWithoutBracketsAndFractionForm(Matrix::inverse(x));
    Rational y = Matrix::inverse(x)[3][0];
    Rational z(0);
    std::cout << z.getNumerator().getList() << "/" << z.getDenominator().getList() << std::endl;
    std::cout << (y==0) << std::endl;
    std::cout << y.getNumerator().getList() << "/" << y.getDenominator().getList();
}
