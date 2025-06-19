#pragma once
#ifndef VECTOR_H
#define VECTOR_H

//#include "../../utils/List.h"
#include "../Rational.h"
#include "../Integer.h"
#include "../../utils/Iterable.h"

class Vector: public Iterable<Rational>
{
    private:
        List<Rational> components;

    public:
        Vector(int INITIAL_SIZE): components(INITIAL_SIZE) 
        {
            for(int i = 0; i < INITIAL_SIZE; i++)
                components.add(Integer(0));        
        }
        Vector(const Vector& another);

        int size() const {return components.getCapacity();}
        void replace(const Rational& value, int index);

        Vector operator+(const Vector& other) const;
        friend Vector operator*(const Rational& num, const Vector& vector);
        Rational operator*(const Vector& other) const;

        int dimension() const {return components.getCapacity();}

        Iterator<Rational> begin() const {return components.begin();}
        Iterator<Rational> end() const {return components.end();}

        Rational operator[](int index) const {return components[index];}

        friend std::ostream& operator<<(std::ostream& os, const Vector& tuple)
        {
            os << tuple.components;
            return os;
        }
};

#endif