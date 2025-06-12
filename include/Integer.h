#pragma once

#include <iostream>
#include "Number.h"
#include "Natural.h"

class Integer : public Number<Integer>
{
    private:
        Natural absolutePart;
    public:
        Integer() {}
        Integer(long long x): absolutePart((x < 0)? -x : x) {this->sign = x>0;}
        Integer(const Natural& natural): absolutePart(natural) {this->sign = 1;}
        Integer(const Natural& natural, bool sign): absolutePart(natural) {setSign(sign);}

        bool operator<(const Integer& other) const;
        bool operator==(const Integer& other) const;
        Integer operator=(const Integer& other);
        Integer operator+(const Integer& other) const;
        Integer operator-(const Integer& other) const;
        Integer operator*(const Integer& other) const;
        Integer operator-() const {Integer r(*this); r.setSign(!this->sign); return r;}
        Integer operator/(const Integer& other) const;
        Integer operator%(const Integer& other) const;
        Integer operator^(const Integer& other) const;
        unsigned short operator[](int index) const;
        Natural getAbsolutePart() const {return absolutePart;}

        static Natural gcd(const Integer& num1, const Integer& num2);

        friend std::ostream& operator<<(std::ostream& os, const Integer& num);
        friend std::istream& operator>>(std::istream& is, Integer& num);
};