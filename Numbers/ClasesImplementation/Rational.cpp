#include "../Rational.h"

Rational Rational::root(const Integer& po) const
{
    /*Rational constantC = *this / po;
    Rational constantQ(po - 1, po);
    Rational x = (constantC < 1) ? Rational(1) : constantC;

    Rational prev;
    const Rational tolerance(1, 1000000);  // Precisión de 1e-6

    do {
        prev = x;
        Rational pow = x.integerPow(po - 1);
        x = constantQ * x + constantC / pow;
        std::cout << x.numerador << "  " << x.denominador << std::endl;
    } while (Rational::abs(x - prev) > tolerance);

    return x;*/
    return 1;
}


Rational Rational::integerPow(Integer exp)
{
    if(numerador == 0) return 0;
    if(numerador == denominador) return 1;
    bool flag = false;
    if (exp < 0)
    {
        flag = true;
        exp.setSign(true);
    }

    Rational base = *this;
    Rational result = 1;
    while (exp > 0)
    {
        if (!exp.isEven())
            result = result * base;

        base = base * base;
        exp = exp.divideBy2();
    }

    if(flag) return Rational(result.denominador, result.numerador);
    return result;
}


Rational::Rational(double x)
{
    if(x < 0) 
    {
        this->sign = 0;
        x = -x;
    }

    long long digits = x;
    int base = 0;

    while(x != digits)
    {
        x *= 10;
        digits = x;
        base++;
    }

    denominador = 1;
    for(int i = 0; i < base%5; i++)
        denominador = denominador * 10;
    denominador = Integer::multiplyByBase(denominador, base/5);
    numerador = x;

    Integer gcd = Integer::binaryEcludian(numerador, denominador);
    numerador = numerador/gcd;
    denominador = denominador/gcd;
}

bool Rational::operator==(const Rational& other) const 
{
    return numerador == other.numerador && denominador == other.denominador;
}

bool Rational::operator<(const Rational& other) const 
{
    if (!sign && other.sign) return true;
    if (sign && !other.sign) return false;
    if(this->sign == 1 && other.sign == 1)
        return numerador*other.denominador < other.numerador*denominador;

    return numerador*other.denominador > other.numerador*denominador;
}

Rational Rational::operator*(const Rational& other)  const 
{
    return Rational(numerador*other.numerador, denominador*other.denominador);
}

Rational Rational::operator/(const Rational& other)  const
{
    return Rational(numerador*other.denominador, denominador*other.numerador);
}

Rational Rational::operator^(const Rational& other) const
{
    return (this->root(other.denominador)).integerPow(other.numerador);
}

Rational Rational::operator=(const Rational& other)
{
    this->sign = other.getSign();
    numerador = other.numerador;
    denominador = other.denominador;
    return *this;
}

Rational Rational::operator+(const Rational& other) const
{
    Integer gcd = Integer::binaryEcludian(denominador, other.denominador);
    Integer num1 = (numerador*other.denominador)/gcd;
    Integer num2 = (denominador*other.numerador)/gcd;

    return Rational(num1+num2, (denominador *other.denominador)/gcd);
}

Rational Rational::operator-(const Rational& other) const
{
    Rational inv = other;
    inv.sign = !inv.sign;
    return *this + inv;
}

Rational Rational::operator-() const
{
    Rational inv(numerador, denominador);
    inv.sign = !inv.sign;
    return inv;
}

