#pragma once

#include <iostream>
#include "../utils/List.h"
#include "../Numbers/Number.h"
#include "Natural.h"

class Integer : public Number<Integer>, public Natural {
private:
    public:
        Integer(long long x): Natural((x < 0)? -x : x) {this->sign = x>0;}
        Integer(const Natural& natural): Natural(natural) {this->sign = 1;}

        bool operator<(const Integer& other) const;
        bool operator==(const Integer& other) const;
        Integer operator=(const Integer& other);
        Integer operator+(const Integer& other) const;
        Integer operator-(const Integer& other) const;
        Integer operator*(const Integer& other) const;
        Integer operator-() const {Integer r(*this); r.setSign(!this->sign); return r;}
        Integer operator/(const Integer& other) const {return 1;};
        Integer operator^(const Integer& other) const {return 1;};
};