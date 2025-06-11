#include "../include/Natural.h"
unsigned short BASE = 100;
/* Metodos privados */

void Natural::cleanDigits(Natural& num)
{
    Natural::cleanDigits(num, num.digits.getCapacity() - 1);
}

void Natural::cleanDigits(Natural& num, int index)
{
    while (index >= 0 && num[index] == 0)
        index--;
    if(index < 0) index = 0;
    List<unsigned short> copy(index);
    for(int i = 0; i <= index; i++)
        copy.add(num[i]);
    num.digits = copy;
}

/* Fin de metodo privados */


Natural::Natural(long long x)
{
    if(x < 0)
        throw std::invalid_argument("Natural must be positive");

    while (x != 0)
    {
        digits.add(x%100);
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
    bool carry = 0;

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

List<Natural> operator-(const Natural& num1, const Natural& num2)
{
    bool carry = 0;
    int maxSize = (num1.digits.size() < num2.digits.size())? num2.digits.size(): num1.digits.size();
    Natural result(0, maxSize);
    for(int i = 0; i < maxSize; i++)
    {
        if(i >= num1.digits.size())
        {
            result.digits.add(num2[i]);
            carry = 1;
            continue;
        }

        int kResult = num1[i] - num2[i] - carry;
        if(kResult < 0 && !carry)
        {
            kResult = -kResult;
        }
        else if(kResult < 0)
        {
            carry = 1;
            kResult += BASE;
        }
        else carry = 0;
        result.digits.add(kResult);
    }

    Natural::cleanDigits(result);
    return {result, !carry};
}

Natural operator*(const Natural& num1, const Natural& num2)
{

    if(num2 == 0 || num1 == 0) return 0;
    if(num1 == 1) return num2;
    if(num2 == 1) return num1;

    Natural product(0, num1.digits.size() + num2.digits.size());
    for(int i = 0; i < num1.digits.size() + num2.digits.size(); i++)
        product.digits.add(0);

    for(int j = 0; j < num2.digits.size(); j++)
    {
        if(num2[j] == 0) continue;
        unsigned short carry = 0;
        for(int i = 0; i < num1.digits.size(); i++)
        {
            unsigned short realSum = carry + num1[i]*num2[j] + product[i+j];
            product.digits.replace(realSum%100, i+j);
            carry = realSum/100;
        }
        product.digits.replace(carry, num1.digits.size()+j);
    }

    Natural::cleanDigits(product);
    return product;
}

Natural operator/(Natural& num1, const Natural& num2)
{
    if(num2.digits.size() == 0) 
        throw std::invalid_argument("Math error: division by zero");

    if(num2 == 1) return num1;

    unsigned short scaleFactor = (num2.digits[num2.digits.size()-1] < 50)? 100/(num2.digits[num2.digits.size()-1] + 1): 1;
    if(scaleFactor != 1)
        num1 = num1 * scaleFactor;

    Natural divisor = (scaleFactor == 1)? num2: num2*scaleFactor;
    int m = num1.digits.size() - num2.digits.size();
    Natural quant(0, m + 1);
    for(int i = 0; i < m + 1; i++)
        quant.digits.add(0);

    Natural currentRemainder(0, num1.digits.size() - m);
    for(int i = m; i < num1.digits.size(); i++)
        currentRemainder.digits.add(num1[i]);
    
    for (int j = m; j >= 0; --j) {


    }

    return 1;
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
    if(x < 0)
        throw std::invalid_argument("Can't have a negative Natural. Do you want to use an Integer?");

    int pos = 0;
    while (x != 0)
    {
        if(pos < num.digits.size())
        {
            num.digits.replace(x%100, pos);
        }else num.digits.add(x%100);
        pos ++;
        x /= 100;
    }
    Natural::cleanDigits(num, pos-1);
    return is;
}