#include <iostream>
#include "../include/Integer.h"
#include "../include/Natural.h"

/* comparasiones    */
bool Integer::operator==(const Integer& other) const
{
    return (this->sign == other.sign) && static_cast<const Natural&>(*this) == static_cast<const Natural&>(other);
}

bool Integer::operator<(const Integer& other) const
{
    if(this->sign && other.sign)
        return static_cast<const Natural&>(*this) < static_cast<const Natural&>(other);
    if(!this->sign && !other.sign)
        return static_cast<const Natural&>(*this) > static_cast<const Natural&>(other);
    if(this->sign) return 1;
    return 0;
}

Integer Integer::operator=(const Integer& other)
{
    if (this != &other)  // Protección contra autoasignación
    {
        Natural::operator=(static_cast<const Natural&>(other));
        this->sign = other.sign;
    }
    return *this;
}

/* fin de comparaciones */

/* Operaciones entre enteros*/
Integer Integer::operator+(const Integer& other) const
{
    if(this->sign == other.getSign())
    {
        Integer result(static_cast<const Natural&>(*this) + static_cast<const Natural&>(other));
        result.setSign(this->sign);
        return result;
    }
}
/*  Fin de operaciones*/