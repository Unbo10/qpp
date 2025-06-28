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