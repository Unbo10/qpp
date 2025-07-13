#pragma once

//#include "../../utils/List.h"
#include "../Rational.h"
#include "../Integer.h"
#include "../../utils/Iterable.h"
#include <sstream>

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

        int size() const {return components.getSize();}
        void replace(const Rational& value, int index);

        Vector operator+(const Vector& other) const;
        Vector operator-(const Vector& other) const;
        friend Vector operator*(const Rational& num, const Vector& vector);
        friend Vector operator/(const Vector& vector, const Rational& num);
        Rational operator*(const Vector& other) const;
        friend bool operator==(const Vector& v1, const Vector& v2) {return v1.components == v2.components;}
        friend Rational norm(const Vector& v1);

        Vector projectionIn(const Vector& other) const;

        int dimension() const {return components.getSize();}

        Iterator<Rational> begin() const {return components.begin();}
        Iterator<Rational> end() const {return components.end();}

        const Rational& operator[](int index) const {return components[index];}
        Rational& operator[](int index) {return components[index];}
        void appendComponent(const Rational& component);
        void removeComponent();
        void clear();

        friend std::ostream& operator<<(std::ostream& os, const Vector& v);
        friend std::istream& operator>>(std::istream& is, Vector& v);
};