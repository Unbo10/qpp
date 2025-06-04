#include "Rational.h"

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
        std::cout << x.numerator << "  " << x.denominator << std::endl;
    } while (Rational::abs(x - prev) > tolerance);

    return x;*/
    return 1;
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

    Integer gcd = Integer::binaryEuclidean(numerator, denominator);
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
    Rational ret(numerator*other.numerator, denominator*other.denominator);
    ret.setSign(this->sign == other.sign);
    std::cout << "Result: " << ret << "\n";
    return ret;
} 

Rational Rational::operator/(const Rational& other)  const
{
    Rational ret(numerator*other.denominator, denominator*other.numerator);
    ret.setSign(this->sign == other.sign);
    return ret;
}

Rational operator/(const Rational& num, int den)
{
    return num / Rational(1, 1);
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
    std::cout << *this << " + " << other << "\n";
    Integer gcd = Integer::binaryEuclidean(denominator, other.denominator);
    Integer num1 = numerator*((gcd != 1) ? (other.denominator)/gcd: other.denominator);
    num1.setSign(sign);
    std::cout << "Num2: \n";
    Integer num2 = other.numerator*((gcd != 1) ? (Integer::abs(denominator))/gcd: Integer::abs(denominator));
    num2.setSign(other.sign);
    std::cout << num2.getSign() << " " << other.sign << "\n";
    std::cout << "Nums: " << num1 << " + " << num2 << "\n";
    if(other.sign == this->sign)
    {
        Rational result(num1+num2, (denominator *other.denominator)/gcd);
        result.setSign(this->sign);
        return result;
    }
    
    if(!other.sign)
        return Rational(num1-num2, (denominator *other.denominator)/gcd);

    return Rational(num2-num1, (denominator *other.denominator)/gcd);
}

Rational Rational::operator-(const Rational& other) const
{
    Rational inv = other;
    inv.sign = !inv.sign;
    std::cout << "Inv: " << inv.sign << inv.numerator << "/" << inv.denominator << "\n";
    return *this + inv;
}

Rational Rational::operator-() const
{
    std::cout << "In -\n";
    Rational inv(numerator, denominator);
    std::cout << inv.numerator << "/" << inv.denominator << " " << inv.sign << "aaa\n";
    inv.sign = !inv.sign;
    std::cout << "Inv: " << sign << numerator << "/" << denominator << " exit\n";
    return inv;
}

Integer Rational::getDenominator() const
{
    return denominator;
}

Integer Rational::getNumerator() const
{
    return numerator;
}

