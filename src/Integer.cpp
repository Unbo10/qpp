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
        num.sign = false;
        x = -x;
    }
    num.absolutePart = x;
    return is;   
}