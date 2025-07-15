#include "../include/Rational.h"

unsigned int Rational::decimalPoints = 5;

Rational::Rational(const Rational& other) {
    this->numerator = other.numerator;
    this->denominator = other.denominator;
    this->sign = other.sign;
}

//***CONSTRUCTORS***

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

Rational::Rational(std::string str) {
    int starting_pos = 0;
    if(str[0] == '-') {
        this->sign = false;
        starting_pos = 1;
    }
    
    size_t slash_pos = str.find('/');

    int num;
    if(slash_pos != std::string::npos) {
        num = std::stoi(str.substr(starting_pos, slash_pos));
        if(slash_pos == str.size())
            throw std::invalid_argument("No denominator given");
        int den = std::stoi(str.substr(slash_pos + 1));
        this->numerator = num;
        this->denominator = den;
    }
    else {
        this->numerator = Natural(std::stoi(str.substr(starting_pos)));
        this->denominator = 1;
    }
}

//***COMPARISON AND ASSIGNING OPERATIONS***

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
    if(this->numerator == 0 && other.numerator == 0)
        return true;
    else
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

//***ARITHMETIC OPERATIONS***

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
        if(result.abs() == 0)
            result.setSign(true);
        else
            result.setSign(this->sign);
        return result;
    }

    List<Natural> res = numerator * (other.denominator/gcd) - other.numerator * (denominator/gcd);
    result.numerator = res[0];
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
    if(result.abs() == 0){
        result.sign = true;
        result.denominator = 1;
    }
    return result;
}

Rational Rational::operator-() const 
{
    Rational result;
    result.denominator = denominator;
    result.numerator = numerator;
    result.sign = !this->sign;
    return result;
}

Rational Rational::operator-(const Rational& other) const
{

    Natural gcd = Natural::gcd(this->denominator, other.denominator);
    Rational result;
    if(this->sign != other.sign)
    {
        result.sign = this->sign;
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
    if(result.abs() == 0){
        result.sign = true;
        result.denominator = 1;
    }
    return result;
}

Rational Rational::operator*(const Rational& other) const
{
    Natural gcd1 = Natural::gcd(other.numerator, this->denominator);
    Natural gcd2 = Natural::gcd(this->numerator, other.denominator);
    
    Rational result;
    result.sign = (this->sign == other.sign);
    // std::cout << "other: " << other.sign << " and " << this->sign << " is " << result.sign << " vs " << (this->sign == other.sign) << "\n";

    result.numerator = ((gcd1 == 1)? other.numerator: other.numerator/gcd1)*
                       ((gcd2 == 1)? this->numerator: this->numerator/gcd2);

    result.denominator = ((gcd1 == 1)? this->denominator: this->denominator/gcd1)*
                         ((gcd2 == 1)? other.denominator: other.denominator/gcd2);

    gcd1 = Natural::gcd(result.numerator, result.denominator);
    if(gcd1 != 1)
    {
        result.numerator = result.numerator/gcd1;
        result.denominator = result.denominator/gcd1;
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
    result.sign = (this->sign == other.sign);
    result.numerator = ((gcd1 == 1)? numerator: numerator/gcd1) *
                       ((gcd2 == 1)? other.denominator: other.denominator/gcd2);

    result.denominator = ((gcd1 == 1)? other.numerator: other.numerator/gcd1) *
                         ((gcd2 == 1)? denominator: denominator/gcd2);

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

//***STREAM OPERATIONS***

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
    for(unsigned int i = 0; i < Rational::decimalPoints; i++)
    {
        if(num == 0) return os;
        Natural q = num/den;
        os << q;
        if(i == 0) os << ".";
        num = (num - q*den)[0];
        num.multiplyBy10();
    }
    // os << number.numerator;
    // os << "/";
    // os << number.denominator;
    return os;
}

std::istream& operator>>(std::istream& is, Rational& num)
{
    std::string str;
    is >> str;
    num = Rational(str);
    return is;
}


void showFraction(const Rational& num)
{ 
    if(!num.sign) std::cout << "-";
    if(num.denominator == 1)
        std::cout << num.numerator;
    else std::cout << num.numerator << "/" << num.denominator;
}

//*Util method for GCD

Rational Rational::invert() const {
    if(this->numerator == 0)
        return Rational(0, 1);
        
    Rational result;
    result.numerator = this->denominator;
    result.denominator = this->numerator;
    result.sign = this->sign;

    return result;
}