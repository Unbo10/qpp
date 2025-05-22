#ifndef RATIONAL_H
#define RATIONAL_H

#include "Number.cpp"
#include "Integer.cpp"

class Rational: public Number
{
    private:
        Integer numerator, denominator;

    public:
        Rational() : numerator(0), denominator(1) {}

        Rational(const Integer& numerator, const Integer& denominator)
        {
            if(denominator == 0) throw std::invalid_argument("Math error: division by cero");
            Integer gcd = Integer::binaryEcludian(denominator, numerator);
            this->denominator = denominator/gcd;
            this->numerator = numerator/gcd;
        }

        friend std::ostream& operator<<(std::ostream& os, Rational num)
        {
            os << num.numerator;
            if(num.denominator != 1)
            {
                os << '/';
                os << num.denominator;
            }
            return os;
        }
};

#endif