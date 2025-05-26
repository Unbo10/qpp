#ifndef RATIONAL_H
#define RATIONAL_H

#include "Number.cpp"
#include "Integer.cpp"

class Rational: public Number<Rational>
{
    private:
        Integer numerador, denominador;

        // aqui se calcula a^{1/p}, con p entero
        Rational root(const Integer& po) const;
        // aqui se calcula a^p, con p entero
        Rational integerPow(Integer po);
    public:
        //Rational(long long x): Rational(Integer(x), 1) {}
        Rational(): Rational(0, 1) {}
        Rational(const Integer& numerador): Rational(numerador, 1) {}
        Rational(const Integer& num, const Integer& den)
        {
            if (den == 0)
                throw std::invalid_argument("Denominator cannot be zero");

            // Signo: true = positivo, false = negativo
            sign = (num.getSign() == den.getSign());

            // Magnitudes absolutas
            Integer absNum = num;
            Integer absDen = den;
            if (!absNum.getSign()) absNum.changeSign(true);
            if (!absDen.getSign()) absDen.changeSign(true);

            // Reducción a mínima expresión
            Integer g = Integer::binaryEcludian(absNum, absDen);
            numerador   = absNum / g;
            denominador = absDen / g;
        }

        Rational(double x);

        // implementación de los métodos de comparación
        bool eq(const Rational& other) const;
        bool lt(const Rational& other) const;

        // implementación de los métodos de operaciones
        Rational add(const Rational& other) const;
        Rational subtract(const Rational& other) const;
        Rational negate() const;
        Rational multiply(const Rational& other) const;
        Rational divide(const Rational& other) const;
        Rational power(Rational other) const;
        void assign(const Rational& other);

        static Rational abs(const Rational& p)
        {
            if(p < 0) return -p;
            return p;
        }

        friend std::ostream& operator<<(std::ostream& os, const Rational& num)
        {
            Integer nume = num.numerador, den = num.denominador;
            
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

#endif