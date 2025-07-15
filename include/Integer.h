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
        Integer(long long x) : absolutePart((x < 0)? -x : x) {this->sign = x>=0;}
        Integer(const Natural& natural) : absolutePart(natural) {this->sign = 1;}
        Integer(const Natural& natural, bool sign) : absolutePart(natural) {this->sign = sign;}
        Integer(std::string str)
        {
            int starting_pos = 0;
            if(str[0] == '-') {
                this->sign = false;
                starting_pos = 1;
            }

            absolutePart = std::stoi(str.substr(starting_pos));
        }

        //***COMPARISON AND ASSIGNING OPERATIONS***

        bool operator<(const Integer& other) const;
        bool operator==(const Integer& other) const;
        Integer operator=(const Integer& other);

        //***ARITHMETIC OPERATIONS***

        Integer operator+(const Integer& other) const;
        friend Integer operator+(const Natural& num1, const Integer& num2);
        Integer operator-(const Integer& other) const;
        Integer operator*(const Integer& other) const;
        friend Integer operator*(const Natural& num1, const Integer* num2);
        static Integer toomCook4(const Integer& num1, const Integer& num2);
        Integer operator-() const {Integer r(*this); r.setSign(!this->sign); return r;} //!Check if using setSign is correct
        Integer operator/(const Integer& other) const;
        Integer operator%(const Integer& other) const;
        Integer operator^(const Integer& other) const;

        //***UTIL METHODS***

        unsigned short operator[](int index) const;
        Natural getAbsolutePart() const {return absolutePart;}
        static Natural gcd(const Integer& num1, const Integer& num2);
        List<Natural> splitIn4() const;
        
        //***STREAM OPERATIONS***

        friend std::ostream& operator<<(std::ostream& os, const Integer& num);
        friend std::istream& operator>>(std::istream& is, Integer& num);
};