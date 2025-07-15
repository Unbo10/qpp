#include <iostream>
#include <sstream>
#include "include/LinearAlgebra/Matrix.h"

int main() {
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
    printWithoutBracketsAndFractionForm(x);
    printWithoutBracketsAndFractionForm(Matrix::inverse(x));
    Rational y = Matrix::inverse(x)[3][0];
    Rational z(0);
    std::cout << z.getNumerator().getList() << "/" << z.getDenominator().getList() << std::endl;
    std::cout << (y==0) << std::endl;
    std::cout << y.getNumerator().getList() << "/" << y.getDenominator().getList();
}