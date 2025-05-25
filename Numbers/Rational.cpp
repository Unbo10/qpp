#ifndef RATIONAL_H
#define RATIONAL_H

#include "Number.cpp"
#include "Integer.cpp"

class Rational: public Number<Rational>
{
    private:
        Integer numerator, denominator;

        //TODO: Implement the rest of the virtual methods
        Rational add(const Rational& other) const override{

        }
        Rational subtract(const Rational& other) const override{

        }
        Rational negate() const override{

        }
        Rational multiply(const Rational& other) const override{

        }
        Rational divide(const Rational& other) const override{

        }
        Rational modulo(const Rational& other) const override{

        }
        Rational power(const Rational& other) const override{

        }
        void assign(const Rational& other) {

        }
        bool eq(const Rational& other) const override{

        }
        bool lt(const Rational& other) const override{

        }
        bool leq(const Rational& other) const override{

        }

    public:
        Rational() : numerator(0), denominator(1) {}

        Rational(const Integer& numerator) : numerator(numerator), denominator(1) {}

        Rational(const Integer& numerator, const Integer& denominator)
        {
            if(denominator == 0) throw std::invalid_argument("Math error: division by cero");
            Integer gcd = Integer::binaryEcludian(denominator, numerator);
            this->denominator = denominator/gcd;
            this->numerator = numerator/gcd;
            sign = denominator.getSign();
        }

        void setSign(bool sign) {
            sign = sign;
        }

        friend std::ostream& operator<<(std::ostream& os, Rational num)
        {
            os << num.numerator;
            if(num.denominator != 1)
            {
                os << '/';
                os << num.denominator;
            }
            return os;
        }

        friend std::istream& operator>>(std::istream& is, Rational& num) {
            std::string input;
            is >> input;
            bool sign;
            if (input.empty())
                throw std::runtime_error("Empty input");
            if (input == "-")
                throw std::runtime_error("Invalid input: single negative sign");
            
            size_t slash_pos = input.find('/');
            //*In case there is only a numerator given and no slash
            if (slash_pos == std::string::npos) {
                num.numerator = Integer(std::stoll(input)); 
                num.denominator = Integer(1);
                return is;
            }

            //*No numerator given
            if (slash_pos == 0 || (slash_pos == 1 && input[0] == '-')) {
                throw std::runtime_error("No numerator given");
            }
            
            if (slash_pos + 1 >= input.length()) {
                throw std::runtime_error("No denominator given");
            }
            
            std::string num_str = input.substr(0, slash_pos);
            std::string denom_str = input.substr(slash_pos + 1);
            
            if (denom_str.empty() || denom_str == "-")
                throw std::runtime_error("No denominator given");

            sign = num.numerator.getSign() ^ num.denominator.getSign();
            num.setSign(sign);
            
            return is;
        }
};

#endif