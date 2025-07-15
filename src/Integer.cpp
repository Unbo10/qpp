#include <iostream>
#include <vector>
#include <sstream>
#include "../include/Integer.h"
#include "../include/Natural.h"

//***COMPARISON AND ASSIGNING OPERATIONS***

bool Integer::operator<(const Integer& other) const
{
    if(this->sign && other.sign)
        return absolutePart < other.absolutePart;
    if(!this->sign && !other.sign)
        return absolutePart > other.absolutePart;
    if(this->sign) return 0;
    return 1;
}

bool Integer::operator==(const Integer& other) const
{
    return (this->sign == other.sign) && (absolutePart == other.absolutePart);
}

Integer Integer::operator=(const Integer& other)
{
    if (this != &other)  // Protección contra autoasignación
    {
        absolutePart = other.absolutePart;
        this->sign = other.sign;
    }
    return *this;
}

//***ARITHMETIC OPERATIONS***

Integer Integer::operator+(const Integer& other) const
{
    if(this->sign == other.getSign())
        return Integer(absolutePart + other.absolutePart, this->sign);

    List<Natural> naturalDiference = absolutePart - other.absolutePart;
    return Integer(naturalDiference[0], (this->sign)? bool(naturalDiference[1]): !bool(naturalDiference[1]));
}

Integer operator+(const Natural& num1, const Integer& num2)
{
    Integer newNum1(num1);
    return newNum1 + num2;
}

Integer Integer::operator-(const Integer& other) const
{
    if(this->sign == !other.getSign())
        return Integer(absolutePart + other.absolutePart, this->sign);

    List<Natural> naturalDiference = absolutePart - other.absolutePart;
    return Integer(naturalDiference[0], bool(naturalDiference[1]));
}

Integer Integer::operator*(const Integer& other) const 
{
    return Integer(absolutePart*other.absolutePart,this->sign == other.sign);
}

Integer operator*(const Natural& num1, const Integer& num2)
{
    Integer newNum1(num1);
    return newNum1 * num2;
}

Integer Integer::toomCook4(const Integer& num1, const Integer& num2)
{
    if((num1.absolutePart.getNumOfDigits() <= 2) && (num1.absolutePart.getNumOfDigits() <= 2))
        return num1 * num2;
    //*Could be less than 1 if it is 0 ([])
    else if((num1.absolutePart.getNumOfDigits() <= 1) || (num1.absolutePart.getNumOfDigits() <= 1))
        return num1 * num2;
    else if((num1.absolutePart == 0) || (num2.absolutePart == 0))
        return 0;

    List<Natural> A = num1.splitIn4();
    List<Natural> B = num2.splitIn4();
    List<Integer> X;
    X.add(0);
    X.add(1);
    X.add(-1);
    X.add(2);
    X.add(-2);
    X.add(3);

    //*Calculate values at x = 0, 1, -1, 2, -2, 3, infty
    //*A(x) = A_0 + A_1 x + A_2 x^2 + A_3 x^3
    List<Integer> vA(7);
    for(Integer& x : X)
    {
        vA.add(A[0] + (A[1] * x) + (A[2] * (x^2)) + (A[3] * (x^3)));
    }
    vA.add(A[3]);

    //*Calculate values at x = 0, 1, -1, 2, -2, 3, infty
    //*B(x) = B_0 + B_1 x + B_2 x^2 + B_3 x^3
    List<Integer> vB(7);
    for(Integer& x : X)
    {
        vB.add(B[0] + (B[1] * x) + (B[2] * (x^2)) + (B[3] * (x^3)));
    }
    vB.add(B[3]);

    //*Multiply component-wise vA and vB to obtain V(r) = A(r) * B(r), where r = 0, 1, -1, 2, -2, 3, infty
    List<Integer> v(7);
    for(int i = 0; i < 7; i++)
    {
        v.add(vA[i] * vB[i]);
    }

    //*Figure out the constants C_i in the product polynomial P(x) = C_0 + C_1 x + ... + C_6 x^6 solving the system (M^(-1))v, where each row in M represents the polynomial P(x) evaluated at x_i \in {0, 1, -1, 2, -2, 3, infty} and v is the column vector where v[0] is the top and first entry. M^(-1) was computed using the Matrix class and it gave the following result:
    // [[1, 0, 0, 0, 0, 0, 0],
    // [0, -3/4, 3/4, -3/20, 3/20, 1/60, -1/60],
    // [-49/36, 3/4, 3/4, -3/40, -3/40, 1/180, 1/180],
    // [0, 13/48, -13/48, 1/6, -1/6, -1/48, 1/48],
    // [7/18, -13/48, -13/48, 1/12, 1/12, -1/144, -1/144],
    // [0, -1/48, 1/48, -1/60, 1/60, 1/240, -1/240],
    // [-1/36, 1/48, 1/48, -1/120, -1/120, 1/720, 1/720]]

    List<Integer> C;
    //!May have to be implemented in Rational due to the fractions
    C.add(v[0]);
    C.add((-3/4)*v[1] + (3/4)*v[2] - (3/20)*v[3] + (3/20)*v[4] + v[5]/60 - v[6]/60);
    C.add((-49/36)*v[0] + (3/4)*v[1] + (3/4)*v[2] - (3/40)*v[3] - (3/40)*v[4] + v[5]/180 + v[6]/180);
    C.add((13/48)*v[1] - (13/48)*v[2] + v[3]/6 - v[4]/6 - v[5]/48 + v[6]/48);
    C.add((7/18)*v[0] - (13/48)*v[1] - (13/48)*v[2] + v[3]/12 + v[4]/12 - v[5]/144 - v[6]/144);
    C.add(-v[1]/48 + v[2]/48 - v[3]/60 + v[4]/60 + v[5]/240 - v[6]/240);
    C.add(v[0]/36 + v[1]/48 + v[2]/48 - v[3]/120 - v[4]/120 + v[5]/720 + v[6]/720);

    //*Now, compute P(10^n), where n is the size of the splits
    Natural splitSize(A[3].getNumOfDigits()/4);
    Integer powerOfSplit = Integer(10) ^ splitSize;
    Integer result = C[0];
    Integer currentPower(1);

    for(int i = 1; i < C.getSize(); i++)
    {
        currentPower = currentPower * powerOfSplit; //*Add 10^n
        result = result + (C[i] * currentPower);
    }

    return result;
    

    //TODO: Implement a splitting-in-4 method (fill with zeros the most-significant part) to make it divisible by a power of 4
    //TODO: Create polynomials A(x) and B(x) with those splits
    //TODO: Implement a method to evaluate a polynomial
    //TODO: Evaluate A and B in 6 points and get the 7th by using the coefficient beside the most-significant power
    //TODO: Compute V(r) using the previosly evaluated A, and B
    //TODO: Figure out Ci by making the product (IA)v, where v is the vector with V(r)
    //TODO: Assemble and sum

    //TODO: Test the split method
    //TODO: Test the algorithm itself
}

Integer Integer::operator/(const Integer& other) const 
{
    return Integer(absolutePart/other.absolutePart, this->sign == other.getSign());    
}

Integer Integer::operator%(const Integer& other) const 
{
    return *this - (*this/other)*other;
}

Integer Integer::operator^(const Integer& other) const
{
    if (other < 0)
        throw std::invalid_argument("This operation may take a Rational.");

    Natural exp(other.absolutePart);
    Natural base(absolutePart);
    Natural result(1);

    while (exp > 0)
    {
        if (!exp[0]%2 == 0)
            result = result * base;

        base = base*base;
        exp = Natural::divideBy2(exp);
    }

    return Integer(result, (this->sign)? 1: (other[0]%2 == 0)? 1: 0);
}

//***UTIL METHODS***

Natural Integer::gcd(const Integer& num1, const Integer& num2)
{
    return Natural::gcd(num1.absolutePart, num2.absolutePart);
}

unsigned short Integer::operator[](int index) const
{
    return absolutePart[index];
}

/**First element (left-most) is the most significant one */
List<Natural> Integer::splitIn4() const
{
    List<Natural> splits(4);
    for(int i = 0; i < 4; i++)
    {
        splits.add(Natural(0));
    }
    Natural newSize;
    if(*this == 0)
    {
        std::cout << "num is 0. Dividing into 4 0's";
        newSize = 4;
    }
    int originalNumOfDigits = this->absolutePart.getNumOfDigits();
    newSize = Natural::smallestGeqPowerOfBase(originalNumOfDigits, Natural(4));
    Natural splitSize = newSize / 4;

    //*Add zeros to each split until necessary, and then add the corresponding
    //*digits of num.
    int i = 0, j = 0, k = 0;
    bool filledWithZeros = false;
    Natural numberOfZeros = (newSize - originalNumOfDigits)[0]; //? -1: Because the array is initialized with 4 zeros?
    for(Natural& split : splits)
    {
        i = 0;
        while ((!filledWithZeros) && (i < splitSize))
        {
            if(k < numberOfZeros)
            {
                split.addDigit(0);
                i++;
                k++;
            }
            else
                filledWithZeros = true;
        }

        while(i < splitSize)
        {
            split.addDigit(this->absolutePart[originalNumOfDigits - j - 1]);
            i++;
            j++;
        }
    }

    return splits;
}

//***STREAM OPERATIONS***

std::ostream& operator<<(std::ostream& os, const Integer& num)
{
    os <<((num.sign)? "": "-") << num.absolutePart;
    return os;
}

std::istream& operator>>(std::istream& is, Integer& num)
{
    long long x;
    is >> x;
    if(x < 0)
    {
        num.setSign(false);
        x = -x;
    }
    num.absolutePart = x;
    return is;   
}