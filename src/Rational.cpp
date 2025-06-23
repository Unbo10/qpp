#include "../include/Rational.h"

unsigned int Rational::decimalPoints = 5;

/*  Metodos privados  */

Rational Rational::root(const Integer& po) const
{
    return 1;
}

Rational Rational::integerPow(Integer po)
{
    return 1;
}
/* constructores    */

Rational::Rational(const Integer& num, const Integer& den)
{
    if(den == 0)
        throw std::invalid_argument("Math error: division by zero");
        
    this->sign = (num.getSign() == den.getSign());
    numerator = num.getAbsolutePart();
    denominator = den.getAbsolutePart();
    Natural gcd(Natural::gcd(numerator, denominator));
    if(gcd != 1)
    {
        numerator = numerator/gcd;
        denominator = denominator/gcd;
    }
}

Rational::Rational(double x)
{
    if(x < 0) 
    {
        this->sign = 0;
        x = -x;
    }

    int y = x;
    int baseCounted = 0;
    while(y != x)
    {
        x *= 10;
        baseCounted++;
        y = x;
    }

    denominator = (baseCounted%2 == 0)? 1: 10;
    for(int i = 0; i < baseCounted/2; i++)
        denominator.multiplyBy100();

    numerator = x;
    Natural gcd = Natural::gcd(numerator, denominator);
    if(gcd != 1)
    {
        numerator = numerator/gcd;
        denominator = denominator/gcd;
    }
}

// implementacion de comparaciones y asignacion

bool Rational::operator<(const Rational& other) const 
{
    if(this->sign && other.sign)
        return numerator*other.denominator < other.numerator * denominator;

    if(!this->sign && !other.sign)
        return numerator*other.denominator > other.numerator * denominator;
    
    if(this->sign) return false;
    return true;
}

bool Rational::operator==(const Rational& other) const
{
    return this->sign == other.sign && 
           numerator == other.numerator && 
           denominator == other.denominator;
}

Rational Rational::operator=(const Rational& other)
{
    this->sign = other.sign;
    numerator = other.numerator;
    denominator = other.denominator;
    return *this;
}

// implementación de los métodos de operaciones
Rational Rational::operator+(const Rational& other) const
{
    Natural gcd = Natural::gcd(this->denominator, other.denominator);
    Rational result;
    if(this->sign == other.sign)
    {
        result.setSign(this->sign);
        if(gcd == 1)
        {
            result.numerator = numerator * other.denominator + other.numerator * denominator;
            result.denominator = other.denominator * denominator;
        }else 
        {
            result.numerator = numerator * (other.denominator/gcd) + other.numerator * (denominator/gcd);
            result.denominator = other.denominator * (denominator/gcd); 
        }
        gcd = Natural::gcd(result.numerator, result.denominator);

        if(gcd != 1)
        {
            result.numerator = result.numerator/gcd;
            result.denominator = result.denominator/gcd;
        }
        return result;
    }

    List<Natural> res = numerator * (other.denominator/gcd) - other.numerator * (denominator/gcd);
    result.numerator = res[0];
    result.denominator = other.denominator * (denominator/gcd); 
    if(this->sign)
        result.setSign(bool(res[1]));
    else result.setSign(!bool(res[1]));

    gcd = Natural::gcd(result.numerator, result.denominator);
    if(gcd != 1)
    {
        result.numerator = result.numerator/gcd;
        result.denominator = result.denominator/gcd;
    }
    return result;
}

Rational Rational::operator-() const 
{
    Rational result;
    result.denominator = denominator;
    result.numerator = numerator;
    result.setSign(!this->sign);
    return result;
}

Rational Rational::operator-(const Rational& other) const
{
    Natural gcd = Natural::gcd(this->denominator, other.denominator);
    Rational result;
    if(this->sign != other.sign)
    {
        result.setSign(this->sign);
        if(gcd == 1)
        {
            result.numerator = numerator * other.denominator + other.numerator * denominator;
            result.denominator = other.denominator * denominator;
        }else 
        {
            result.numerator = numerator * (other.denominator/gcd) + other.numerator * (denominator/gcd);
            result.denominator = other.denominator * (denominator/gcd); 
        }
        return result;
    }

    List<Natural> res = numerator * (other.denominator/gcd) - other.numerator * (denominator/gcd);
    result.numerator = res[0];
    result.denominator = other.denominator * (denominator/gcd); 
    if(this->sign)
        result.setSign(bool(res[1]));
    else result.setSign(!bool(res[1]));

    gcd = Natural::gcd(numerator, denominator);
    if(gcd != 1)
    {
        result.numerator = result.numerator/gcd;
        result.denominator = result.denominator/gcd;
    }
    return result;
}

Rational Rational::operator*(const Rational& other) const
{
    Natural gcd1 = Natural::gcd(other.numerator, this->denominator);
    Natural gcd2 = Natural::gcd(this->numerator, other.denominator);

    Rational result;
    result.setSign(this->sign == other.sign);

    result.numerator = ((gcd1 == 1)? other.numerator: other.numerator/gcd1)*
                       ((gcd2 == 1)? this->numerator: this->numerator/gcd2);

    result.denominator = ((gcd1 == 1)? this->denominator: this->denominator/gcd1)*
                         ((gcd2 == 1)? other.denominator: other.denominator/gcd2);

    return result;
}

Rational Rational::operator/(const Rational& other) const
{
    if (other.numerator == 0)
        throw std::invalid_argument("Math error: division by cero");
    
    Natural gcd1 = Natural::gcd(numerator, other.numerator);
    Natural gcd2 = Natural::gcd(denominator, other.denominator);

    Rational result;
    result.setSign(this->sign == other.sign);
    result.numerator = ((gcd1 == 1)? numerator: numerator/gcd1) *
                       ((gcd2 == 1)? other.denominator: other.denominator/gcd2);

    result.denominator = ((gcd1 == 1)? other.numerator: other.numerator/gcd1) *
                         ((gcd2 == 1)? denominator: denominator/gcd2);

    return result;
}

Rational Rational::operator^(const Rational& other) const
{
    return 1;
}

// entradas y salidas
std::ostream& operator<<(std::ostream& os, const Rational& number)
{
    if(number.numerator == 0) 
    {
        os << "0";
        return os;
    }
    if(!number.sign) os << '-';
    if(number.denominator == 1 /*|| number.denominator == 0*/)
    {
        os << number.numerator;
        return os;   
    }

    Natural num = number.numerator, den = number.denominator;
    if(Rational::decimalPoints == 0)
    {
        os << num/den;
        return os;
    }
    for(int i = 0; i < Rational::decimalPoints; i++)
    {
        if(num == 0) return os;
        Natural q = num/den;
        os << q;
        if(i == 0) os << ".";
        num = (num - q*den)[0];
        num.multiplyBy10();
    }
    return os;
}

void showFraction(const Rational& num)
{
    if(num.numerator == 0)
    {
        std::cout << "0";  
        return;
    }
        
    if(!num.sign) std::cout << "-";
    if(num.denominator == 1)
        std::cout << num.numerator;
    else std::cout << num.numerator << "/" << num.denominator;
}