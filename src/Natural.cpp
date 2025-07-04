#include "../include/Natural.h"
unsigned short BASE = 100;

//***UTILS***

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

//***UTILS FOR ARITHMETIC OPERATIONS***

List<Natural> subtract(const Natural& num1, const Natural& num2, bool reorder)
{
    if(reorder && num1 < num2)
        return {subtract(num2, num1, 0)[0], 0};
        
    bool carry = 0;
    int maxSize = (num1.digits.size() < num2.digits.size())? num2.digits.size(): num1.digits.size();
    Natural result(0, maxSize);
    for(int i = 0; i < maxSize; i++)
    {
        short kResult = num1[i] - num2[i] - carry;
        if(kResult < 0)
        {
            carry = 1;
            kResult += BASE;
        }
        else carry = 0;
        result.digits.replace(kResult, i);
    }

    Natural::cleanDigits(result);
    //?Why don't we just return the result?
    return {result, 1};
}

unsigned short estimateTrialQuotient(const Natural& num1, const Natural& num2)
{
    int size = num1.digits.size()-1;
    if(size == 0)
        return num1[size]/num2[num2.digits.size()-1];
    return (num1[size]*100 + num1[size -1])/num2[num2.digits.size()-1];
}

//***CONSTRUCTORS***

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

Natural::Natural(const Natural& other)
{
    digits = other.digits;
}

//***COMPARISON OPERATIONS***

bool Natural::operator<(const Natural& num) const 
{
    //?Deberiamos limpiar los digitos antes de hacer la comparacion?
    int size = (num.digits.size() < digits.size())? digits.size(): num.digits.size();

    for(int i = size-1; i >= 0; i--)
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

//***ASSIGNING AND INDEX-ACCESSING OPERATIONS***

void Natural::operator=(const Natural& num2)
{
    digits = num2.digits;
}

unsigned short Natural::operator[](int index) const
{
    if(index < 0 || digits.size() <= index)
        return 0;

    return digits[index];
}

//***ARITHMETIC OPERATIONS***

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
        result.digits.replace(res, i);
    }

    if(carry) result.digits.replace(1, size);
    Natural::cleanDigits(result);
    return result;
}

List<Natural> operator-(const Natural& num1, const Natural& num2)
{
    return subtract(num1, num2, 1);
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

Natural operator/(const Natural& num1, const Natural& num2)
{
    if(num1 == 0 && num2 == 0) return num1;
    if(num2 == 0) 
        throw std::invalid_argument("Math error: division by zero");

    if(num1.digits.size() < num2.digits.size())
        return 0;
    if(num1 == num2)
        return 1;
    

    if(num2 == 2) return Natural::divideBy2(num1);
    if(num2 == 1) return num1;

    unsigned short scaleFactor = 100/(num2.digits[num2.digits.size()-1] + 1);
    Natural dividend = num1*scaleFactor;
    Natural divisor = num2*scaleFactor;
    int m = dividend.digits.size() - divisor.digits.size()-1;
    Natural U(0, divisor.digits.size()+1);
    Natural quant(0, m+1);
    for(int i = m; i < dividend.digits.size(); i++)
        U.digits.replace(dividend[i], i-m);
        
    for(int j = m; j >= 0; j--)
    {
        unsigned short q;
        if(U[divisor.digits.size()] == divisor[divisor.digits.size()-1])
            q = 99;
        else q = estimateTrialQuotient(U, divisor);
        Natural w = divisor*q;
        while(w > U)
        {
            q--;
            w = (w - divisor)[0];
        }
        quant.digits.replace(q, j);
        U = (U - w)[0];
        if(j > 0)
            U.digits.add(dividend[j-1], 0);
    }
    return quant;
}

//***STREAM OPERATIONS***

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
        throw std::invalid_argument("Can't have a negative Natural. Maybe you want to use an Integer?");

    int pos = 0;
    while (x != 0)
    {
        //!Double check this logic
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

//***PUBLIC UTILS***

Natural Natural::divideBy2(const Natural& num)
{
    if(num == 0) return 0;

    Natural quant(0, (num[num.digits.size()-1] < 2) ?  num.digits.size()-1: num.digits.size());

    int currentResult = (num[num.digits.size()-1] < 2) ? num[num.digits.size()-1]: 0;
    for(int i = quant.digits.getCapacity()-1; i >= 0; i--)
    {
        currentResult = currentResult*100 + num[i];
        quant.digits.replace(currentResult/2, i);
        currentResult = currentResult%2;
    }

    return quant;
}

void Natural::multiplyBy10()
{
    int size = this->digits.size();
    if(size == 0) return;
    unsigned short peek = this->operator[](size-1);
    List<unsigned short> copy((peek < 10)? size: size+1);
    unsigned short carry = 0;
    for(unsigned short x: this->digits)
    {
        copy.add((x % 10)*10 + carry);
        carry = x/10;
    }

    if(carry != 0)
        copy.add(carry);

    this->digits = copy;
}

Natural Natural::gcd(const Natural& num1, const Natural& num2)
{
    if(num1 == 0 && num2 == 0)
        return Natural(1);
    if(num1 == 0)
        return num2;
    if(num2 == 0)
        return num1;
    
    Natural number1 = num1, number2 = num2;

    Natural gcd = 1;
    while(number1[0]%2 == 0 && number2[0]%2 == 0)
    {
        number1 = Natural::divideBy2(number1);
        number2 = Natural::divideBy2(number2);
        gcd = 2*gcd;
    }

    while(number1 > 0 && number2 != 1)
    {
        while(number1[0]%2 == 0) number1 = Natural::divideBy2(number1);
        while(number2[0]%2 == 0) number2 = Natural::divideBy2(number2);
        Natural t = (number1 - number2)[0];
        if(number1 < number2) number2 = number1;
        number1 = t;
    }

    return gcd*number2;
}

List<unsigned short> Natural::getList()
{
    return List<unsigned short>(digits);
}