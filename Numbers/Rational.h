#pragma once

#include "Number.h"
#include "Integer.h"

class Rational: public Number<Rational>
{
    private:
        // Integer numerator, denominator;

        // aqui se calcula a^{1/p}, con p entero
        Rational root(const Integer& po) const;
        // aqui se calcula a^p, con p entero
        Rational integerPow(Integer po);
    public:
        //? Can it be made private?
        Integer numerator, denominator;
        //Rational(long long x): Rational(Integer(x), 1) {}
        Rational(): Rational(0, 1) {}
        Rational(const Integer& numerator) 
        {
            this->sign = numerator.getSign();
            this->numerator = numerator;
            this->denominator = 1;
            this->numerator.setSign(true);
        }

        Rational(const Integer& num, const Integer& den)
        {
            if (den == 0)
                throw std::invalid_argument("Denominator cannot be zero");

            // Signo: true = positivo, false = negativo
            sign = (num.getSign() == den.getSign());

            // Magnitudes absolutas
            Integer absNum = num;
            Integer absDen = den;
            absNum.setSign(true);
            absDen.setSign(true);

            // Reducción a mínima expresión
            Integer g = Integer::binaryEuclidean(absNum, absDen);
            if(g > 1)
            {
                numerator   = absNum / g;
                denominator = absDen / g;
            }
            else
            {
                numerator = absNum;
                denominator = absDen;
            }
        }
        Rational(double x);

        // implementación de los métodos de comparación
        bool operator==(const Rational& other) const;
        bool operator<(const Rational& other) const;

        // implementación de los métodos de operaciones
        Rational operator+(const Rational& other) const override;
        Rational operator-(const Rational& other) const;
        Rational operator-() const;
        Rational operator*(const Rational& other) const;
        Rational operator/(const Rational& other) const;
        friend Rational operator/(const Rational& num, int den);
        Rational operator^(const Rational& other) const;
        Rational operator=(const Rational& other);

        static Rational abs(const Rational& p)
        {
            if(p < 0) return -p;
            return p;
        }

        friend std::ostream& operator<<(std::ostream& os, const Rational& num)
        {
            if (!num.sign) os << "-";

            os << Integer::abs(num.numerator);
            if (num.denominator != 1)
                os << "/" << Integer::abs(num.denominator);

            // Integer nume = num.numerator, den = num.denominator;
            
            // for(int i = 0; i < 5; i++)
            // {
            //     Integer q = nume/den;
            //     if(i == 1) os << ".";
            //     os << q;
            //     nume = nume - q*den;
            //     nume = Integer::multiplyByBase(nume, 1);
            // }

            return os;
        }

        //***GETTERS***
        Integer getDenominator() const;
        Integer getNumerator() const;
};