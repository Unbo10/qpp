#pragma once

/*
    El objetivo de esta clase es optimazar el uso
    de los recursos de las clases Integer y Rational, usando
    lo que comunmente se conoce como unsigned int. Se hace
    la implementacion con la clase Natural, para abstraer la
    idea de un numero sin signo, que implementa las operaciones basicas. 


    La idea general es construir las clases Integer y Rational a partir de esta,
    para ello ofrecemos un numero natural de presicion arbitraria.
*/

#include "../utils/List.h"
#include "../utils/Comparable.h"

class Natural: public Comparable<Natural>
{
    protected:
    /*
        Se hace uso de lista de presicion arbitraria, 
        para guardar los digitos del numero en orden inverso,
        en base 100. La idea de esto es conseguir eficiencia, ya que
        numeros con una gran cantidad de digitos solo se guardaran con
        la mitad del espacio.
    */
        List<unsigned short> digits;
    /*
        Para ahorrar memoria, se limpian los espacios no fundamentales,
        es decir, lugares que no se usan a la derecha, o ceros a la derecha
    */
        static void cleanDigits(Natural& num);
        static void cleanDigits(Natural& num, int index);

        Natural(int x, int size): digits(size) 
        {
            for(int i = 0; i< size; i++)
                digits.add(0);
        }
        friend List<Natural> res(const Natural& num1, const Natural& num2, bool re);
        friend unsigned short stimateQuant(const Natural& num1, const Natural& num2);
    public:
        Natural(long long x);
        Natural(const Natural& other);
        Natural() {};
        bool operator<(const Natural& num) const;
        bool operator==(const Natural& num) const;
        void operator=(const Natural& num2);

        unsigned short operator[](int index) const;
        friend Natural operator+(const Natural& num1, const Natural& num2);
        friend List<Natural> operator-(const Natural& num1, const Natural& num2);
        friend Natural operator*(const Natural& num1, const Natural& num2);
        friend Natural operator/(const Natural& num1, const Natural& num2);

        friend std::ostream& operator<<(std::ostream& os, const Natural& num);
        friend std::istream& operator>>(std::istream& is, Natural& num);

        static Natural divideBy2(const Natural& num);
        void multiplyBy100() {digits.add(0, 0);}
        void multiplyBy10();
        //**Greater or equal */
        static int smallestGeqPowerOfBase(const int num, const int base);
        int size() const {return this->digits.size();}
        static Natural gcd(const Natural& num1, const Natural& num2);

        List<unsigned short> getList() const;
        double toDouble() const;
        explicit operator bool() const 
        {
            return this->operator[](0)%2;
        }
};