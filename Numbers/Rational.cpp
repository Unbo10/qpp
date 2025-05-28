#include "Rational.h"

Rational Rational::root(const Integer& po) const
{
    Rational constantC = *this / po;
    Rational constantQ(po - 1, po);
    Rational x = (constantC < 1) ? Rational(1) : constantC;

    Rational prev;
    const Rational tolerance(1, 1000000);  // Precisión de 1e-6

    do {
        prev = x;
        Rational pow = x.integerPow(po - 1);
        x = constantQ * x + constantC / pow;
        std::cout << x.numerator << "  " << x.denominator << std::endl;
    } while (Rational::abs(x - prev) > tolerance);

    return x;
}


Rational Rational::integerPow(Integer exp)
{
    if(numerator == 0) return 0;
    if(numerator == denominator) return 1;
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

    if(flag) return Rational(result.denominator, result.numerator);
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

    denominator = 1;
    for(int i = 0; i < base%5; i++)
        denominator = denominator * 10;
    denominator = Integer::multiplyByBase(denominator, base/5);
    numerator = x;

    Integer gcd = Integer::binaryEcludian(numerator, denominator);
    numerator = numerator/gcd;
    denominator = denominator/gcd;
}

bool Rational::operator==(const Rational& other) const 
{
    return numerator == other.numerator && denominator == other.denominator;
}

bool Rational::operator<(const Rational& other) const 
{
    if (!sign && other.sign) return true;
    if (sign && !other.sign) return false;
    if(this->sign == 1 && other.sign == 1)
        return numerator*other.denominator < other.numerator*denominator;

    return numerator*other.denominator > other.numerator*denominator;
}

Rational Rational::operator*(const Rational& other)  const 
{
    return Rational(numerator*other.numerator, denominator*other.denominator);
}

Rational Rational::operator/(const Rational& other)  const
{
    return Rational(numerator*other.denominator, denominator*other.numerator);
}

Rational Rational::operator^(const Rational& other) const
{
    return (this->root(other.denominator)).integerPow(other.numerator);
}

Rational Rational::operator=(const Rational& other)
{
    this->sign = other.getSign();
    numerator = other.numerator;
    denominator = other.denominator;
    return *this;
}

Rational Rational::operator+(const Rational& other) const
{
    Integer gcd = Integer::binaryEcludian(denominator, other.denominator);
    Integer num1 = (numerator*other.denominator)/gcd;
    Integer num2 = (denominator*other.numerator)/gcd;

    return Rational(num1+num2, (denominator *other.denominator)/gcd);
}

Rational Rational::operator-(const Rational& other) const
{
    Rational inv = other;
    inv.sign = !inv.sign;
    return *this + inv;
}

Rational Rational::operator-() const
{
    Rational inv(numerator, denominator);
    inv.sign = !inv.sign;
    return inv;
}

