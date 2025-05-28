#pragma once

#include "Number.h"
#include "Integer.h"

class Rational: public Number<Rational>
{
    private:
        Integer numerator, denominator;

        // aqui se calcula a^{1/p}, con p entero
        Rational root(const Integer& po) const;
        // aqui se calcula a^p, con p entero
        Rational integerPow(Integer po);
    public:
        //Rational(long long x): Rational(Integer(x), 1) {}
        Rational(): Rational(0, 1) {}
        Rational(const Integer& numerator): Rational(numerator, 1) {}
        Rational(const Integer& num, const Integer& den)
        {
            if (den == 0)
                throw std::invalid_argument("Denominator cannot be zero");

            // Signo: true = positivo, false = negativo
            sign = (num.getSign() == den.getSign());

            // Magnitudes absolutas
            Integer absNum = num;
            Integer absDen = den;
            if (!absNum.getSign()) absNum.setSign(true);
            if (!absDen.getSign()) absDen.setSign(true);

            // Reducción a mínima expresión
            Integer g = Integer::binaryEcludian(absNum, absDen);
            numerator   = absNum / g;
            denominator = absDen / g;
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
        Rational operator^(const Rational& other) const;
        Rational operator=(const Rational& other);

        static Rational abs(const Rational& p)
        {
            if(p < 0) return -p;
            return p;
        }

        friend std::ostream& operator<<(std::ostream& os, const Rational& num)
        {
            Integer nume = num.numerator, den = num.denominator;
            
            if(!num.sign)  os << "-";
            
            for(int i = 0; i < 5; i++)
            {
                Integer q = nume/den;
                if(i == 1) os << ".";
                os << q;
                nume = nume - q*den;
                nume = Integer::multiplyByBase(nume, 1);
            }

            return os;
        }
};