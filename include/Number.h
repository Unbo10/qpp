#pragma once

#include <iostream>

#include "../utils/Comparable.h"

template <typename T>
class Number: public Comparable<T>
{
    protected:
        static const int DEFAULT_BASE = 100;
        int BASE;
    public:
        //*True is for positive and zero and false is for negative
        bool sign;
        Number() : BASE(DEFAULT_BASE), sign(true) {}
        Number(bool sgn, int base) : BASE(base), sign(sgn) {}
        Number(bool sgn) : BASE(DEFAULT_BASE), sign(sgn) {}
        ~Number() {}

        virtual bool operator<(const T& other) const = 0;
        virtual bool operator==(const T& other) const = 0;
        virtual T operator=(const T& other) = 0;
        
        virtual T operator+(const T& other) const = 0;
        virtual T operator-() const = 0;
        virtual T operator-(const T& other) const = 0;
        virtual T operator*(const T& other) const = 0;
        virtual T operator/(const T& other) const = 0;
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

        friend T& operator^=(T& lhs, const T& rhs)
        {
            T result = lhs ^ rhs;
            lhs = result;
            return lhs;
        }

        bool getSign() const {return sign;}

        void setSign(bool sign) {this->sign = sign;}
};