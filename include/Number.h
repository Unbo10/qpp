#pragma once

#include <iostream>

#include "../utils/Comparable.h"

template <typename T>
class Number: public Comparable<T>
{
    protected:
        static const int DEFAULT_BASE = 100000;
        // bool base_initialized;
        bool sign;
        int BASE;
    public:
        Number() : sign(true), BASE(DEFAULT_BASE) {}
        Number(bool sgn, int base) : sign(sgn), BASE(base) {}
        Number(bool sgn) : sign(sgn), BASE(DEFAULT_BASE) {}
        ~Number() {}

        virtual bool operator<(const T& other) const = 0;
        virtual bool operator==(const T& other) const = 0;
        virtual T operator=(const T& other) = 0;
        
        virtual T operator+(const T& other) const = 0;
        virtual T operator-() const = 0;
        virtual T operator-(const T& other) const = 0;
        virtual T operator*(const T& other) const = 0;
        virtual T operator/(const T& other) const = 0;
        //virtual T operator%(const T& other) const = 0;
        virtual T operator^(const T& other) const = 0;
        
        friend T& operator+=(T& lhs, const T& rhs)
        {
            T result = lhs + rhs;
            lhs = result;
            return lhs;
        }

        friend T& operator-=(T& lhs, const T& rhs)
        {
            T result = lhs - rhs;
            lhs = result;
            return lhs;
        }

        friend T& operator*=(T& lhs, const T& rhs)
        {
            T result = lhs * rhs;
            lhs = result;
            return lhs;
        }

        friend T& operator/=(T& lhs, const T& rhs)
        {
            T result = lhs / rhs;
            lhs = result;
            return lhs;
        }

        /*friend T& operator%=(T& lhs, const T& rhs)
        {
            T result = lhs % rhs;
            lhs = result;
            return lhs;
        }*/

        friend T& operator^=(T& lhs, const T& rhs)
        {
            T result = lhs ^ rhs;
            lhs = result;
            return lhs;
        }

        bool getSign() const {return sign;}

        void setSign(bool sign) {this->sign = sign;}
};