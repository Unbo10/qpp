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
                components.add(Rational(0, 1));        
        }
        Vector(const Vector& another);
        Vector(): Vector(10) {}
        Vector(const List<Rational>& list): components(list) {}

        int size() const {return components.getCapacity();}
        void replace(const Rational& value, int index);

        Vector operator+(const Vector& other) const;
        Vector operator-(const Vector& other) const;
        friend Vector operator*(const Rational& num, const Vector& vector);
        friend Vector operator/(const Vector& vector, const Rational& num);
        Rational operator*(const Vector& other) const;
        friend bool operator==(const Vector& v1, const Vector& v2) {return v1.components == v2.components;}

        Vector projectionIn(const Vector& other) const;

        int dimension() const {return components.getCapacity();}

        Iterator<Rational> begin() const {return components.begin();}
        Iterator<Rational> end() const {return components.end();}

        const Rational& operator[](int index) const {return components[index];}
        Rational& operator[](int index) {return components[index];}

        friend std::ostream& operator<<(std::ostream& os, const Vector& tuple)
        {
            os << tuple.components;
            return os;
        }
};

#endif