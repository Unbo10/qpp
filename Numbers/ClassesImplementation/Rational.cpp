#include "../Rational.h"

bool Rational::eq(const Rational& other) const 
{
    return numerador == other.numerador && denominador == other.denominador;
}

bool Rational::lt(const Rational& other) const 
{
    if (!sign && other.sign) return true;
    if (sign && !other.sign) return false;
    if(this->sign == 1 && other.sign == 1)
        return numerador*other.denominador < other.numerador*denominador;

    return numerador*other.denominador > other.numerador*denominador;
}

Rational Rational::multiply(const Rational& other)  const 
{
    return Rational(numerador*other.numerador, denominador*other.denominador);
}

Rational Rational::divide(const Rational& other)  const
{
    return Rational(numerador*other.denominador, denominador*other.numerador);
}

Rational Rational::power(Rational other) const
{
    return Rational(1);
}

void Rational::assign(const Rational& other)
{
    this->sign = other.getSign();
    numerador = other.numerador;
    denominador = other.denominador;
}

Rational Rational::add(const Rational& other) const
{
    Integer gcd = Integer::binaryEcludian(denominador, other.denominador);
    Integer num1 = (numerador*other.denominador)/gcd;
    Integer num2 = (denominador*other.numerador)/gcd;

    return Rational(num1+num2, (denominador *other.denominador)/gcd);
}

Rational Rational::subtract(const Rational& other) const
{
    Rational inv = other;
    inv.sign = !inv.sign;
    return *this + inv;
}

Rational Rational::negate() const
{
    Rational inv(numerador, denominador);
    inv.sign = !inv.sign;
    return inv;
}

