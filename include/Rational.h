#pragma once

#include <cmath>

#include "Number.h"
#include "Integer.h"

class Rational: public Number<Rational>
{
    private:
        Natural numerator, denominator;

        // aqui se calcula a^{1/p}, con p entero
        Rational root(const Natural& po) const;
        // aqui se calcula a^p, con p entero
        Rational integerPow(const Natural& po) const;
    public:
        static unsigned int decimalPoints;

        //Rational(long long x): Rational(Integer(x), 1) {}
        Rational(): numerator(0), denominator(1) {this->setSign(true);}
        Rational(const Integer& numeratr): numerator(numeratr.getAbsolutePart()), denominator(1)  {this->setSign(numeratr.getSign());}
        Rational(const Integer& num, const Integer& den);
        Rational(const Natural& num): numerator(num), denominator(1) {this->setSign(true);}
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
        friend Rational operator/(const Integer& other, const Rational& number)
        {
            return Rational(other)/number;
        }
        Rational operator^(const Rational& other) const;
        double toDouble() const;

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