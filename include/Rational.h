#pragma once

#include <variant>

#include "Number.h"
#include "Integer.h"

class Rational: public Number<Rational>
{
    private:
        Natural numerator, denominator;

        // aqui se calcula a^{1/p}, con p entero
        Rational root(const Integer& po) const;
        // aqui se calcula a^p, con p entero
        Rational integerPow(Integer po);
    public:
        static unsigned int decimalPoints;

        //Rational(long long x): Rational(Integer(x), 1) {}
        Rational(): Rational(0, 1) {}
        Rational(const Integer& numeratr): numerator(numeratr.getAbsolutePart()), denominator(1)  {}
        Rational(const Integer& num, const Integer& den);
        Rational(double x);

        // implementación de los métodos de comparación y asignacion
        bool operator==(const Rational& other) const;
        bool operator<(const Rational& other) const;
        Rational operator=(const Rational& other);

        // implementación de los métodos de operaciones
        Rational operator+(const Rational& other) const override;
        Rational operator-(const Rational& other) const;
        Rational operator-() const;
        Rational operator*(const Rational& other) const;
        Rational operator/(const Rational& other) const;
        Rational operator^(const Rational& other) const;
        
        std::variant<Integer, Rational> checkForInteger() const 
        {
            if(denominator != 1)
                return std::variant<Integer, Rational>(
                    std::in_place_type<Rational>,
                    Rational(Integer(numerator, this->sign), denominator)
                );

                
            return std::variant<Integer, Rational>(
                std::in_place_type<Integer>,
                Integer(numerator, this->sign)
            );
        }

        static Rational abs(const Rational& p)
        {
            if(p < 0) return -p;
            return p;
        }

        friend std::ostream& operator<<(std::ostream& os, const Rational& num);
        friend void showFraction(const Rational& num);

        explicit operator Natural() {return this->numerator/this->denominator;}
        explicit operator Integer() {return Integer(this->numerator/this->denominator, this->sign);}
};