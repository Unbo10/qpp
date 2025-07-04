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
    /*showFraction(Rational(-1155, 35522)*Rational(11,1) + Rational(2061, 17761)*Rational(1, 2) + Rational(-1774, 17761)*Rational(-3, 1));
    std::cout << w;
     Matrix x = Matrix::identy(17);
    std::cout << x << std::endl;*/
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
    Matrix x (Matrix::inverse(m1));
    std::cout << x << std::endl;
    printWithoutBracketsAndFractionForm(x*m1);
    printWithoutBracketsAndFractionForm(x);
    //std::cout << x*m1;
}