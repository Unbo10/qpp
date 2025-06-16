#include "../../include/LinearAlgebra/Vector.h"
using Datos = std::variant<Integer, Rational>;

Vector::Vector(const Vector& another): Vector(another.size())
{
    for(const Datos& x: another)
    {
        components.add(x);
    }
}

void Vector::replace(const Datos& value, int index)
{
    if(std::holds_alternative<Rational>(value))
        components.replace(std::get<Rational>(value).checkForInteger(), index); 
    else components.replace(value, index);
    //components.replace(value, index);
}