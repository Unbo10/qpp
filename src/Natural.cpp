#include "../include/Natural.h"
unsigned short BASE = 100;
/* Metodos privados */

void Natural::cleanDigits(Natural& num)
{
    int size = num.digits.capacity();
    while(num[size] == 0)
        size--;

    if(size < 0) size = 0;
    List<unsigned short> copy(size);
    for(unsigned short x: num.digits)
        copy.add(x);

    num.digits = copy;
}

/* Fin de metodo privados */


Natural::Natural(long long x)
{
    if(x < 0)
        throw std::invalid_argument("Natural must be positive");

    while (x != 0)
    {
        digits.add((unsigned short) x%100);
        x /= 100;
    }
    Natural::cleanDigits(*this);
}

/* Comparaciones */
bool Natural::operator<(const Natural& num) const 
{
    int size = (num.digits.size() < digits.size())? digits.size(): num.digits.size();

    for(int i = 0; i < size; i++)
    {
        if(this->operator[](i) < num[i])
            return true;
        if(this->operator[](i) > num[i])
            return false;
    }
    return false;
}

bool Natural::operator==(const Natural& num) const
{
    return digits == num.digits;
}
/* Fin de las comparaciones */

/* Obtener digitos  */
unsigned short Natural::operator[](int index) const
{
    if(index < 0 || digits.size() <= index)
        return 0;

    return digits[index];
}


/* Operaciones entre naturales  */

Natural operator+(const Natural& num1, const Natural& num2)
{
    int size = (num1.digits.size() < num2.digits.size())? num2.digits.size(): num1.digits.size();
    Natural result(0, size + 1);
    unsigned short carry = 0;

    for(int i = 0; i < size; i++)
    {
        unsigned short res = num1[i] + num2[i] + carry;
        if(res >= 100) 
        {
            res -= 100;
            carry = 1;
        }
        else carry = 0;
        result.digits.add(res);
    }

    if(carry) result.digits.add(1);
    Natural::cleanDigits(result);
    return result;
}

void Natural::operator=(const Natural& num2)
{
    digits = num2.digits;
}
/* Implementacion de lectura y de salida*/

std::ostream& operator<<(std::ostream& os, const Natural& num)
{
    if(num.digits.size() == 0) 
    {
        os << "0";
        return os;
    }
    int size = num.digits.size() - 1;
    os << num[size];

    for(int i = size - 1; 0 <= i; i--)
    {
        unsigned short r = num[i];
        if(r < 10)
            os << "0" << r;
        else os << r;
    }

    return os;
}

std::istream& operator>>(std::istream& is, Natural& num)
{
    long long x;
    std::cin >> x;

}