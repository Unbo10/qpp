#include "../../include/LinearAlgebra/Vector.h"

Vector::Vector(const Vector& another): components(another.components.size())
{
    for(const Rational& x: another)
    {
        components.add(x);
    }
}

void Vector::replace(const Rational& value, int index)
{
    components.replace(value, index);
}

/*  operaciones entre vectores */

Vector Vector::operator+(const Vector& other) const
{
    if(this->dimension() != other.dimension())
        throw std::invalid_argument("Vector dimensions don't match");

    Vector result(this->dimension());
    for(int i = 0; i < this->dimension(); i++)
        result.replace(components[i] + other[i], i);

    return result;
}

Vector Vector::operator-(const Vector& other) const 
{
    if(this->dimension() != other.dimension())
        throw std::invalid_argument("Vector dimensions don't match");

    Vector result(other);
    for(int i = 0; i < this->dimension(); i++)
        result.replace(components[i] - result[i], i);

    return result;
}

Vector Vector::operator-() const
{
    Vector negated(*this);
    for(Rational& r : negated.components)
        r = -r;

    return negated;
}

Rational Vector::operator*(const Vector& other) const
{
    if(this->dimension() != other.dimension())
        throw std::invalid_argument("Vector dimensions don't match");

    Rational result(0);
    for(int i = 0; i < this->dimension(); i++)
        result = result + components[i]*other[i];
        
    return result;
}

Vector operator*(const Rational& num, const Vector& vector)
{
    if(num == 0) return Vector(vector.dimension());

    Vector result(vector);

    for(int i = 0; i < vector.dimension(); i++)
        result.replace(num*result[i], i);

    return result;
}

Rational norm(const Vector& v1)
{
    Rational sum(0);
    for(const Rational& x: v1)
    {
        sum = sum + x*x;
    }

    return (sum^(0.5));
}

Vector operator/(const Vector& vector, const Rational& num)
{
    Vector result(vector);

    for(Rational& number: result)
        number = number/num;
    
    return result;
}

Vector Vector::projectionIn(const Vector& other) const
{
    Rational scalar = (this->operator*(other))/(other*other);
    return scalar*other;
}

//*At end
void Vector::appendComponent(const Rational& component) 
{
    components.add(component);
}

//*At end
void Vector::removeComponent()
{
    if(components.getSize() == 0)
        return;
    components.pop(components.getSize() - 1);
}

void Vector::clear()
{
    components.clear();
}

std::ostream& operator<<(std::ostream& os, const Vector& v)
{
    os << v.components;
    return os;
}

std::istream& operator>>(std::istream& is, Vector& v)
{
    v.clear();
    
    //*Read the entire line
    std::string line;
    std::getline(is, line);
    
    std::istringstream iss(line);
    std::string token;
    
    //*Read each token (rational) from the string and try to make it a Rational
    while(iss >> token) {
        try {
            Rational r(token);
            v.components.add(r);
        } 
        //*Skip invalid inputs
        catch(...) {
            continue;
        }
    }
    
    return is;
}

//TODO: Test and implement >> for Rational, vector, and Matrix