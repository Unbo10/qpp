#include "../include/Rational.h"

unsigned int Rational::decimalPoints = 5;
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

Rational::Rational(double value)
{
    int max_den = 100000;
    if (value == 0.0) {
        numerator = Natural(0);
        denominator = Natural(1);
        sign = 1;
        return;
    }

    sign = (value < 0) ? 0 : 1;
    if(value < 0)
        value = -value;

    long long a = static_cast<long long>(std::floor(value));
    long long num1 = 1, num2 = a;
    long long den1 = 0, den2 = 1;

    double frac = value - a;

    while (true) {
        if (frac == 0.0) break;

        frac = 1.0 / frac;
        a = static_cast<long long>(std::floor(frac));

        long long num = a * num2 + num1;
        long long den = a * den2 + den1;

        if (den > max_den) break;

        num1 = num2;
        den1 = den2;
        num2 = num;
        den2 = den;

        frac = frac - a;

        //if (frac < 1e-12) break;
    }

    numerator = Natural(num2);
    denominator = Natural(den2);
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
    //if(this->numerator == 0 && other.numerator == 0)
      //  return true;
    return this->sign == other.sign && 
           numerator == other.numerator && 
           denominator == other.denominator;
}

Rational Rational::operator=(const Rational& other)
{  
    /*if(other == 0) 
    {
        numerator = other.numerator;
        denominator = 1;
    }
    else
    {*/
        this->sign = other.sign;
        numerator = other.numerator;
        denominator = other.denominator;
    //}
    return *this;
}

// implementación de los métodos de operaciones
Rational Rational::operator+(const Rational& other) const
{
    Natural gcd = Natural::gcd(this->denominator, other.denominator);
    Rational result;
    if(this->sign == other.sign)
    {
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
        result.setSign(this->sign);
        return result;
    }

    List<Natural> res = numerator * (other.denominator/gcd) - other.numerator * (denominator/gcd);
    result.numerator = res[0];
    if(result.numerator == 0)
    {
        result.sign = 1;
        result.denominator = 1;
        return result;
    }
    result.denominator = other.denominator * (denominator/gcd); 
    if(this->sign)
        result.sign = bool(res[1]);
    else result.sign = !bool(res[1]);

    gcd = Natural::gcd(result.numerator, result.denominator);
    if(gcd != 1)
    {
        result.numerator = result.numerator/gcd;
        result.denominator = result.denominator/gcd;
    }
    /*if(result.abs(result) == 0){
        result.sign = true;
        result.denominator = 1;
    }*/
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
    if(result.numerator == 0)
    {
        result.sign = 1;
        result.denominator = 1;
        return result;
    }
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
    if(result.numerator == 0)
    {
        result.sign = 1;
        result.denominator = 1;
        return result;
    }
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

    if(result.numerator == 0)
    {
        result.sign = 1;
        result.denominator = 1;
        return result;
    }
    return result;
}

Rational Rational::operator^(const Rational& other) const
{
    if(!this->sign && other.denominator[0]%2 == 0)
        throw std::invalid_argument("Cannot calculate the root of a negative number with even index");
    
    if(other == 0)
    {
        if(*this == 0)
            throw std::invalid_argument("0^0 is not defined");

        return 1;
    }

    if(*this == 0)
        return 0;

    double exp = other.toDouble();
    double base = this->toDouble();

    return Rational(std::pow(base, exp));
}

double Rational::toDouble() const 
{
    double r = numerator.toDouble() / denominator.toDouble();

    return (this->sign)? r: -r;
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
        std::cout << '0';
        return;
    }
    if(!num.sign) std::cout << "-";
    if(num.denominator == 1)
        std::cout << num.numerator;
    else std::cout << num.numerator << "/" << num.denominator;
}