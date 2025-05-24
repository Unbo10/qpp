#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>

#include "../utils/Comparable.cpp"
//!The header guards should go in header files. There their need.

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
        ~Number() {}

        virtual T add(const T& other) const = 0;
        virtual T subtract(const T& other) const = 0;
        virtual T negate() const = 0;
        virtual T multiply(const T& other) const = 0;
        virtual T divide(const T& other) const = 0;
        virtual T modulo(const T& other) const = 0;
        virtual T power(const T& other) const = 0;
        virtual void assign(const T& other) = 0;
        virtual bool eq(const T& other) const = 0;
        virtual bool lt(const T& other) const = 0;
        virtual bool leq(const T& other) const = 0;
        
        friend T operator+(const T& first, const T& second) {
            return first.add(second);
        }

        friend T operator-(const T& first) {
            return first.negate();
        }

        friend T operator-(const T& first, const T& second) {
            return first.subtract(second);
        }
        
        friend T operator*(const T& first, const T& second) {
            return first.multiply(second);
        }
        
        friend T operator/(const T& first, const T& second) {
            return first.divide(second);
        }
        
        friend T operator%(const T& first, const T& second) {
            return first.modulo(second);
        }
        
        friend T operator^(const T& first, const T& second) {
            return first.power(second);
        }
        
        void operator=(const T& other) {
            this->assign(other);
        }
        
        void operator+=(const T& other) {
            T result = this->add(other);
            *this = *result;
            delete result;
        }

        void operator-=(const T& other) {
            T result = this->subtract(other);
            *this = *result;
            delete result;
        }

        void operator*=(const T& other) {
            T result = this->multiply(other);
            *this = *result;
            delete result;
        }

        void operator/=(const T& other) {
            T result = this->divide(other);
            *this = result;
        }

        void operator%=(const T& other) {
            T result = this->modulo(other);
            *this = result;
        }

        void operator^=(const T& other) {
            T result = this->power(other);
            *this = result;
        }

};

#endif