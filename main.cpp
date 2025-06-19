#include <iostream>
#include <sstream>
#include "include/LinearAlgebra/Vector.h"

int main() {
    Rational x(1, 2), y(3, 4);

    showFraction(x/y);
    /*Vector array(7), invArray(7);
    //Rational x;

    for(int i = 1; i < 7; i++)
    {
        array.replace(Rational(1, i), i);
        invArray.replace(Rational(i, 1), i);
    }
        
    std::cout << array << "\n" << invArray << "\n";    
    std::cout << array.projectionIn(invArray);*/
}