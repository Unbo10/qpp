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

Integer operator+(const Integer& num1, const Natural& num2)
{
    Integer newNum2(num2);
    return num1 * newNum2;
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

Integer operator*(const Integer& num1, const Natural& num2)
{
    Integer newNum2(num2);
    return num1 * newNum2;
}

Integer Integer::toomCook4(const Integer& num1, const Integer& num2)
{
    if((num1.absolutePart.getNumOfDigits() <= 2) && (num1.absolutePart.getNumOfDigits() <= 2))
        return num1 * num2;
    //*Could be less than 1 if it is 0 ([])
    else if((num1.absolutePart.getNumOfDigits() <= 1) || (num1.absolutePart.getNumOfDigits() <= 1))
        return num1 * num2;
    else if((num1.absolutePart == 0) || (num2.absolutePart == 0))
        return Integer(0);

    List<Integer> A = num1.splitIn4();
    List<Integer> B = num2.splitIn4();
    List<Integer> X(5);
    X.add(1);
    X.add(-1);
    X.add(2);
    X.add(-2);
    X.add(3);

    std::cout << "X initialization and splits made\n";
    
    //*Calculate values at x = 0, 1, -1, 2, -2, 3, infty
    //*A(x) = A_0 + A_1 x + A_2 x^2 + A_3 x^3
    List<Integer> vA(7);
    vA.add(A[0]);
    for(Integer& x : X)
    {
        std::cout << "Step-by-step calculation:" << "\n";
        std::cout << "  A[0] = " << A[0] << "\n";
        std::cout << "  A[1] * x = " << A[1] << " * " << x << " = " << (A[1] * x) << "\n";
        std::cout << "  A[2] * x^2 = " << A[2] << " * " << x << "^2 = " << A[2] << " * " << (x^2) << " = " << (A[2] * (x^2)) << "\n";
        std::cout << "  A[3] * x^3 = " << A[3] << " * " << x << "^3 = " << A[3] << " * " << (x^3) << " = " << (A[3] * (x^3)) << "\n";
        std::cout << "\n";

        Integer result = A[0] + (A[1] * x) + (A[2] * (x*x)) + (A[3] * (x*x*x));
        std::cout << "Final calculation:" << "\n";
        std::cout << "  " << A[0] << " + " << (A[1] * x) << " + " << (A[2] * (x*x)) << " + " << (A[3] * (x*x*x)) << " = " << result << "\n";
        std::cout << "Adding result " << result << " to vA" << "\n";
        vA.add(A[0] + (A[1] * x) + (A[2] * (x^2)) + (A[3] * (x^3)));
    }
    vA.add(A[3]);

    std::cout << "vA: " << vA << "\n";

    //*Calculate values at x = 0, 1, -1, 2, -2, 3, infty
    //*B(x) = B_0 + B_1 x + B_2 x^2 + B_3 x^3
    List<Integer> vB(7);
    vB.add(B[0]);
    for(Integer& x : X)
    {
        vB.add(B[0] + (B[1] * x) + (B[2] * (x^2)) + (B[3] * (x^3)));
    }
    vB.add(B[3]);

    std::cout << "vB: " << vB << "\n";

    //*Multiply component-wise vA and vB to obtain V(r) = A(r) * B(r), where r = 0, 1, -1, 2, -2, 3, infty
    List<Integer> v(7);
    for(int i = 0; i < 7; i++)
    {
        v.add(vA[i] * vB[i]);
    }

    std::cout << "v: " << v << "\n";

    //*Figure out the constants C_i in the product polynomial P(x) = C_0 + C_1 x + ... + C_6 x^6 solving the system (M^(-1))v, where each row in M represents the polynomial P(x) evaluated at x_i \in {0, 1, -1, 2, -2, 3, infty} and v is the column vector where v[0] is the top and first entry. M^(-1) was computed using the Matrix class and it gave the following result:
    // Original matrix M^(-1):
    // [[1, 0, 0, 0, 0, 0, 0],
    // [0, -3/4, 3/4, -3/20, 3/20, 1/60, -1/60],
    // [-49/36, 3/4, 3/4, -3/40, -3/40, 1/180, 1/180],
    // [0, 13/48, -13/48, 1/6, -1/6, -1/48, 1/48],
    // [7/18, -13/48, -13/48, 1/12, 1/12, -1/144, -1/144],
    // [0, -1/48, 1/48, -1/60, 1/60, 1/240, -1/240],
    // [-1/36, 1/48, 1/48, -1/120, -1/120, 1/720, 1/720]]
    
    // Matrix multiplied by LCM(720):
    // [[720, 0, 0, 0, 0, 0, 0],
    // [0, -540, 540, -108, 108, 12, -12],
    // [-980, 540, 540, -54, -54, 4, 4],
    // [0, 195, -195, 120, -120, -15, 15],
    // [280, -195, -195, 60, 60, -5, -5],
    // [0, -15, 15, -12, 12, 3, -3],
    // [-20, 15, 15, -6, -6, 1, 1]]

    List<Integer> C(7);
    //!May have to be implemented in Rational due to the fractions
    //*Using the matrix multiplied by LCM(720) = 720, then divide by 720 at the end
    C.add(v[0]); // 720*v[0]/720 = v[0]
    std::cout << "C0: " << C << "\n";
    C.add(((-(540*v[1])) + 540*v[2] + (-(108*v[3])) + 108*v[4] + 12*v[5] + (-(12*v[6]))));
    std::cout << "C1: " << C << "\n";
    C.add((-(980*v[0]) + 540*v[1] + 540*v[2] + (- (54*v[3])) + (- (54*v[4])) + 4*v[5] + 4*v[6]));
    // Integer term1 = -(980 * v[0]);
    // Integer term2 = 540 * v[1];
    // Integer term3 = 540 * v[2];
    // Integer term4 = -(54 * v[3]);
    // Integer term5 = -(54 * v[4]);
    // Integer term6 = 4 * v[5];
    // Integer term7 = 4 * v[6];

    // std::cout << "\nIndividual terms:" << "\n";
    // std::cout << "  -(980 * v[0]) = -(980 * " << v[0] << ") = " << term1 << "\n";
    // std::cout << "  540 * v[1] = 540 * " << v[1] << " = " << term2 << "\n";
    // std::cout << "  540 * v[2] = 540 * " << v[2] << " = " << term3 << "\n";
    // std::cout << "  -54 * v[3] = -54 * " << v[3] << " = " << term4 << "\n";
    // std::cout << "  -54 * v[4] = -54 * " << v[4] << " = " << term5 << "\n";
    // std::cout << "  4 * v[5] = 4 * " << v[5] << " = " << term6 << "\n";
    // std::cout << "  4 * v[6] = 4 * " << v[6] << " = " << term7 << "\n";

    // Show the addition step by step
    // Integer result1 = term1 + term2 + term3 + term4 + term5 + term6 + term7;
    // std::cout << "\nStep-by-step addition:" << "\n";
    // std::cout << "  " << term1 << " + " << term2 << " + " << term3 << " + " 
            // << term4 << " + " << term5 << " + " << term6 << " + " << term7 << "\n";
    // std::cout << "  = " << result1 << "\n";
    std::cout << "C2: " << C << "\n";
    C.add((195*v[1] +(-(195*v[2])) + 120*v[3] +(-(120*v[4])) +(-(15*v[5])) + 15*v[6]));
    std::cout << "C3: " << C << "\n";
    C.add((280*v[0] +(-(195*v[1])) +(-(195*v[2])) + 60*v[3] + 60*v[4] +(-(5*v[5])) +(-(5*v[6]))));
    std::cout << "C4: " << C << "\n";
    C.add((-(15*v[1]) + 15*v[2] +(-(12*v[3])) + 12*v[4] + 3*v[5] +(-(3*v[6]))));
    std::cout << "C5: " << C << "\n";
    C.add((-(20*v[0]) + 15*v[1] + 15*v[2] +(-(6*v[3])) +(-(6*v[4])) + v[5] + v[6]));
    std::cout << "C6: " << C << "\n";

    //*Now, compute P(10^n), where n is the size of the splits
    Natural splitSize(A[3].getNumOfDigits());
    Integer powerOfSplit = Integer(100) ^ splitSize;
    std::cout << "powerOfSplit: " << powerOfSplit << "\n";
    Integer result = C[0];
    Integer currentPower(1);

    std::cout << "B\n";

    for(int i = 0; i < C.getSize(); i++)
    {
        currentPower = currentPower * powerOfSplit; //*Add 10^n
        result = result + (C[i] * currentPower);
    }

    result = result / 720;

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
        if (exp[0]%2 == 1)
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

void Integer::addDigit(unsigned short digit)
{
    absolutePart.addDigit(digit);
}

/**First element (left-most) is the most significant one */
List<Integer> Integer::splitIn4() const
{
    List<Integer> splits(4);
    for(int i = 0; i < 4; i++)
    {
        splits.add(Integer(0));
    }
    Natural newSize;
    if(*this == 0)
    {
        std::cout << "num is 0. Dividing into 4 0's";
        newSize = 4;
    }
    int originalNumOfDigits = this->absolutePart.getNumOfDigits();
    newSize = Natural::smallestGeqPowerOfBase(originalNumOfDigits, Natural(4));
    std::cout << originalNumOfDigits << " vs " << newSize << "\n";
    Natural splitSize = newSize / 4;

    //*Add zeros to each split until necessary, and then add the corresponding
    //*digits of num.
    int i = 0, j = 0, k = 0;
    bool filledWithZeros = false;
    Natural numberOfZeros = (newSize - originalNumOfDigits)[0]; //? -1: Because the array is initialized with 4 zeros?
    for(Integer& split : splits)
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

    //*To make sure the higher the index the higher the part is, the elements
    //*need to be inverted because of how Natural is conceived (the most
    //*significant parts are saved to the right starting from the left)
    splits.invert();

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