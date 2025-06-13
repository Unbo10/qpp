#pragma once
#ifndef VECTOR_H
#define VECTOR_H

//#include "../../utils/List.h"
#include "../Rational.h"
#include "../Integer.h"
#include "../../utils/Iterable.h"

#include <variant>
using Datos = std::variant<Integer, Rational>;

inline std::ostream& operator<<(std::ostream& os, const Datos& data)
{
    std::visit([&os](auto&& value) {
        os << value;
            }, data);
    return os;
}

class Vector: public Iterable<Datos>
{
    private:
        List<Datos> components;

    public:
        Vector(int INITIAL_SIZE): components(INITIAL_SIZE) 
        {
            for(int i = 0; i < INITIAL_SIZE; i++)
                components.add(Integer(0));        
        }
        Vector(const Vector& another);

        int size() const {return components.getCapacity();}
        void replace(const Datos& value, int index);

        Iterator<Datos> begin() const {return components.begin();}
        Iterator<Datos> end() const {return components.end();}

        friend std::ostream& operator<<(std::ostream& os, const Vector& tuple)
        {
            os << tuple.components;
            return os;
        }
};

#endif