#include <bits/stdc++.h>
#include "ex.cpp"

using namespace std;

int main(){
    Polynomial poly;
    poly.parseFromString("302340238947902374x^10 - 2x + 5");
    poly.printPolynomial();
    poly.printDense();
    cout << "Max Degree: " << poly.getDegree() << endl;
    poly.printSparse();
    
    return 0;
}