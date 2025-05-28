#include <iostream>
#include "Integer.h"

//? Consider implementing a toString method to improve the erorr messages

//---PRIVATE---

//***NON-STATIC HELPER METHODS***

void Integer::addDigit(long long newDigit)
{
    if(newDigit <= 0) return;
    forceAdd(newDigit);
}

void Integer::addDigit(const Integer& newDigit)
{
    if(BASE != newDigit.BASE)
        throw std::invalid_argument("Not implemented digits in diferents bases");
    
    for(int x: newDigit.digitsInteger)
        digitsInteger.add(x);
    
}

void Integer::forceAdd(long long newDigit)
{
    if(newDigit == 0) digitsInteger.add(0);
    while(0 < newDigit)
    {
        int res = newDigit%BASE;
        newDigit /= BASE;
        digitsInteger.add(res);
    }
}

void Integer::setSize(int newSize)
{
    List<int> newList(newSize);
    for(int i = 0; i < newSize; i++)
        newList.add(digitAt(i));

    digitsInteger = newList;
}


int Integer::digitAt(int index) const
{
    try{
        return digitsInteger[index];
    }catch(const std::invalid_argument& e)
    {
        return 0;
    }
}

//*Only to access the index (for now)
int Integer::operator[](int index) const {
    if (index >= 0 && index < digitsInteger.size()) {
        return digitsInteger[index];
    }
    return 0;
}

//***STATIC HELPER METHODS***

void Integer::cleanDigits(Integer& num)
{
    int length = num.digitsInteger.getCapacity();
    while(0 < length && num.digitAt(length-1) == 0)
        length--;
    if(length == num.getNumberSize()) return;
    List<int> clean(length);
    for(int i = 0; i < length; i++)
        clean.add(num.digitAt(i));

    num.digitsInteger = clean;
}

int Integer::max_int(int x, int y)
{
    if(x < y) return y;
    return x;
}

int Integer::min_int(int y, int x)
{
    if(x < y) return x;
    return y;
}

int Integer::getNumOfDigits(long long x)
{
    if(x == 0) return 1;
    int c = 0;
    while(x != 0)
    {
        x /= 10;
        c++;
    }
    return c;
}


//***PARTITION METHODS FOR ALGORITHMS***

Integer Integer::getHighPart(int index) const
{
    Integer toR;
    for(int i = digitsInteger.size() - index -1; i < digitsInteger.size(); i++)
        toR.addDigit(this->digitAt(i));

    Integer::cleanDigits(toR);
    return toR;
}

Integer Integer::getLowPart(int index) const
{
    Integer toR;
    for(int i = 0; i < index; i++)
        toR.digitsInteger.add(this->digitAt(i));
    Integer::cleanDigits(toR);
    return toR;
}


//***MULTIPLICATION ALGORITHMS***

Integer Integer::multiplyConventional(const Integer& num1, const Integer& num2)
{
    Integer product;
    product.BASE = num1.BASE;
    int totalSize = num1.getNumberSize() + num2.getNumberSize();

    for(int i = 0; i < totalSize; i++)
        product.digitsInteger.add(0);

    for(int j = 0; j < num2.getNumberSize(); j++)
    {
        if(num2.digitAt(j) == 0) continue;
        long long carry = 0;
        for(int i = 0; i < num1.getNumberSize(); i++)
        {
            long long realSum = carry + 1LL * num1.digitAt(i)*num2.digitAt(j) + product.digitAt(i+j);
            product.digitsInteger.replace(realSum%num1.BASE, i+j);
            carry = realSum/num1.BASE;
        }
        product.digitsInteger.replace(carry, num1.getNumberSize()+j);
    }

    Integer::cleanDigits(product);
    return product;
}

Integer Integer::multiplyKaratsuba(const Integer& num1, const Integer& num2)
{
    if(num1.getNumberSize() <= 15 || num2.getNumberSize() <= 15)
        return multiplyConventional(num1, num2);
    int upperSize = Integer::max_int(num1.getNumberSize(), num2.getNumberSize())/2;

    Integer uper1 = num1.getHighPart(upperSize);
    Integer lower1 = num1.getLowPart(upperSize);
    Integer upper2 = num2.getHighPart(upperSize);
    Integer lower2 = num2.getLowPart(upperSize);

    Integer U = multiplyKaratsuba(uper1, upper2);
    Integer V = multiplyKaratsuba(lower1, lower2);
    Integer W = multiplyKaratsuba(uper1 + lower1, upper2 + lower2) -U -V;
    return multiplyByBase(V, 2*upperSize) + multiplyByBase(W, upperSize) + U;
}

//***DIVISION HELPER***


int Integer::estimateQuotient(const Integer& rem, const Integer& divisor) {
    const int n = divisor.getNumberSize(), m = rem.getNumberSize();
    const long long top = 1LL * rem.digitAt(m-1) * rem.BASE + rem.digitAt(m-2);
    return min_int(top / divisor.digitAt(n-1), rem.BASE-1);
}


//---PRIVATE METHODS---

//***CONSTRUCTORS AND DESTRUCTOR***

Integer::Integer(): Number<Integer>() {}
Integer::Integer(long long x): Number<Integer>()
{
    sign = x >= 0;
    addDigit(sign? x: -x);
    Integer::cleanDigits(*this);
}
Integer::Integer(const Integer& toC) : Number<Integer>(toC.sign, toC.BASE), digitsInteger(toC.digitsInteger) {}
Integer::~Integer()=default;


//***COMPARISON OPERATORS***

bool Integer::operator==(const Integer& other) const 
{
    return other.sign == sign &&
            other.BASE == BASE &&
            other.digitsInteger == digitsInteger;
}  

bool operator==(const int int_num, const Integer& num)
{
    Integer num1(int_num);
    return num1 == num;
}

bool operator==(const Integer& num, const int int_num)
{
    Integer num2(int_num);
    return num == num2;
}

bool operator!=(const Integer& num1, const int num2)
{
    Integer num2_integer = num2;
    return !(num1 == num2_integer);
}

bool operator!=(const int num1, const Integer& num2)
{
    Integer num1_integer(num1);
    return !(num1_integer == num2);
}

bool Integer::operator<(const Integer& other) const
{
    if(sign == 0 && other.sign == 1) return true;
    else if(sign == 1 && other.sign == 0) return false;
    else if(sign == 1 && other.sign == 1)
    {
        //*This case does take into account when both numbers are equal
        int length = Integer::max_int(this->getNumberSize(), other.getNumberSize());
        for(int i = length - 1; 0 <= i; i--)
        {
            if(other.digitAt(i) < this->digitAt(i))
                return false;
            else if(this->digitAt(i) < other.digitAt(i))
                return true;
        }

        return false;
    }
    else
        //*Both are negative
        return -other < -(*this); //!May be wrong
}

bool Integer::operator<(const int int_num)
{
    Integer num = int_num;
    return (*this) < num;
}

bool operator<(int int_num1, const Integer& num2)
{
    Integer num1(int_num1);
    return num2 < num1;
}


bool operator<=(const int int_num, const Integer& num)
{
    Integer num1(int_num);
    return num1 <= num;
}

bool operator<=(const Integer& num, const int int_num)
{
    Integer num2(int_num);
    return num <= num2;
}


bool operator>(const int int_num1, const Integer& num2)
{
    return !(int_num1 <= num2);
}

bool operator>(const Integer& num1, const int int_num2)
{
    return !(num1 <= int_num2);
}

bool operator>=(const int int_num1, const Integer& num2)
{
    return int_num1 > num2 || int_num1 == num2;
}

bool operator>=(const Integer& num1, const int int_num2)
{
    return num1 > int_num2 || num1 == int_num2;
}
        

//***ARITHMETIC OPERATORS***

Integer Integer::operator+(const Integer& other) const
{
    if (BASE != other.BASE) 
        throw std::invalid_argument("Not defined sum of integers in different Bases yet");
    
    if (sign ^ other.sign) 
    {
        if(sign)
            return *this - (-other);
        return other - (-(*this)); //!This may not work.
    }

    Integer sumOfIntegers;
    sumOfIntegers.BASE = BASE;
    int length = Integer::max_int(getNumberSize(), other.getNumberSize());
    int c = 0;
    long long res = 0;

    while (c < length || res != 0)
    {
        res += digitAt(c) + other.digitAt(c);
        sumOfIntegers.forceAdd(res % BASE);
        res /= BASE;
        c++;
    }
    sumOfIntegers.sign = sign;
    Integer::cleanDigits(sumOfIntegers);
    return sumOfIntegers;
}

Integer operator+(int num1, const Integer& num2)
{
    Integer new_int = num1;
    return new_int + num2;
}

Integer operator+(const Integer& num1, int num2)
{
    Integer new_int = num2;
    return num1 + new_int;
}

Integer Integer::operator-(const Integer& other) const
{
    if((*this) < other)
        return -(other - (*this));
    if(!other.sign)
        return *this + (-other);

    bool carry = 0;
    int maxSize = Integer::max_int(getNumberSize(), other.getNumberSize());
    Integer result;
    result.BASE = BASE;

    for(int i = 0; i < maxSize; i++)
    {
        int kResult = digitAt(i) - other.digitAt(i) - carry;
        if(kResult < 0)
        {
            carry = 1;
            kResult += BASE;
        }
        else carry = 0;
        result.forceAdd(kResult);
    }

    Integer::cleanDigits(result);
    return result;
}

Integer operator-(int num1, Integer& num2)
{
    Integer new_int = num1;
    return new_int - num2;
}

Integer operator-(Integer& num1, int num2)
{
    Integer new_int = num2;
    return num1 - new_int;
}

Integer Integer::operator-() const
{
    Integer toR(*(this));
    toR.sign = !toR.sign;
    return toR;
}

Integer Integer::operator*(const Integer& other) const
{
    if(BASE != other.BASE) throw std::invalid_argument("Error");
    if(*this == 0 || other == 0) return Integer();
    Integer mult = Integer::multiplyKaratsuba(*this, other);
    mult.sign = !(sign ^ other.sign);
    mult.BASE= BASE;
    Integer::cleanDigits(mult);
    return mult;
}

Integer operator*(int num1, const Integer& num2)
{
    Integer new_int = num1;
    return new_int * num2;
}

Integer operator*(const Integer& num1, int num2)
{
    Integer new_int = num2;
    return num1 * new_int;
}

Integer Integer::operator/(const Integer& other) const
{
    if (other == 0) throw std::invalid_argument("Division by zero");
    if (BASE != other.BASE) throw std::invalid_argument("Different bases");
    
    // Manejo rápido de casos especiales
    if (getNumberSize() < other.getNumberSize()) return 0;
    if (other == 1) return *this;

    if(other == 2)
        return this->divideBy2();

    Integer a = (sign) ? *this: -*this;
    Integer b = (other.sign)? other: -other;
    if(b.digitAt(b.getNumberSize() -1) < BASE/2)
    {
        long long x = BASE/(b.digitAt(b.getNumberSize() -1) + 1);
        a = a.multiplyByDigit(x);
        b = b.multiplyByDigit(x);
    }

    const int m = a.getNumberSize() - b.getNumberSize();
    Integer quant;
    quant.setSize(m + 1);

    Integer currentRemainder;
    for(int i = m; i < a.getNumberSize(); i++)
        currentRemainder.digitsInteger.add(a.digitAt(i));

    for (int j = m; j >= 0; --j) {
        
        int q;
        if(currentRemainder < b) q = 0;
        else q = Integer::estimateQuotient(currentRemainder, b);
        Integer help = b.multiplyByDigit(q);
        while (help > currentRemainder) {
            q--; help -= b;
            // std::cout << q << std::endl;
        }
        
        currentRemainder = currentRemainder - help;
        quant.digitsInteger.replace(q, j); 
        currentRemainder.digitsInteger.add(a.digitAt(j), 0);
    }

    Integer::cleanDigits(quant);
    return quant;
}

Integer operator/(int num1, const Integer& num2)
{
    Integer new_int = num1;
    return new_int / num2;
}

Integer operator/(const Integer& num1, int num2)
{
    Integer new_int = num2;
    return num1 / new_int;
}

Integer Integer::operator%(const Integer& other) const 
{
    //? Could also be this->add((this->divide(other)).multiply(other).negate());
    return *this - (*this/other)*other;
}

Integer operator%(int num1, const Integer& num2)
{
    Integer new_int = num1;
    return new_int % num2;
}

Integer operator%(const Integer& num1, int num2)
{
    Integer new_int = num2;
    return num1 % new_int;
}

Integer Integer::operator^(const Integer& other) const
{
    if (other < Integer(0))
        return 1/((*this)^other);

    Integer exp(other);
    Integer base(*this);
    Integer result(1);
    while (exp > 0)
    {
        if (!exp.isEven())
            result = result * base;

        base *= base;
        exp /= 2;
    }

    return result;
}

Integer Integer::operator=(const Integer& other)
{
    this->sign = other.sign;
    this->BASE = other.BASE;
    this->digitsInteger = other.digitsInteger;
    return *this;
}

Integer Integer::operator=(const long long num_int)
{
    Integer num(num_int);
    return *this = num;
}


//***NON-STATIC UTILITY METHODS***

Integer Integer::divideBy2() const
{
    Integer result;
    result.sign = this->sign;
    result.setSize(digitsInteger.size());

    int carry = 0;
    for (int i = (int)digitsInteger.size() - 1; i >= 0; --i) {
        long long current = carry * 100000LL + this->digitAt(i);  // base = 10^5
        result.digitsInteger.replace(current / 2, i);
        carry = current % 2;
    }

    Integer::cleanDigits(result);
    return result;
}  

Integer Integer::multiplyByDigit(int x) const
{
    if(x == 0) return Integer(0);
    if(x == 1) return *this;
    if(x == -1) return -*this;
    bool flag = false;
    if(x < 0)
    {
        flag = true;
        x = -x;
    }

    Integer result; //result.setSize(this->getNumberSize() + 1);
    long long carry = 0;
    for(long long num: digitsInteger)
    {
        long long sum = x*num + carry;
        result.digitsInteger.add(sum%BASE);
        carry = sum/BASE;
    }
    if(carry > 0) result.addDigit(carry);
    result.sign = (!flag == this->sign);
    Integer::cleanDigits(result);
    return result;
}


//***STATIC UTILITY METHODS***

Integer Integer::abs(const Integer& r)
{
    if(r.sign) return r;
    return -r;
}

Integer Integer::multiplyByBase(const Integer& num, int times)
{
    Integer result;
    for(int i = 0; i < times; i++)
        result.digitsInteger.add(0);
    result.addDigit(num);
    return result;
}

Integer Integer::divideRecursively(const Integer& num1, const Integer& num2)
{
    if(num1.getNumberSize() < 15 || num2.getNumberSize() < 15)
        return num1/num2;

    int upperSize = Integer::max_int(num1.getNumberSize(), num2.getNumberSize())/2;

    Integer upper1 = num1.getHighPart(upperSize);
    Integer lower1 = num1.getLowPart(upperSize);
    Integer upper2 = num2.getHighPart(upperSize);
    //Integer lower2 = num2.getLowPart(upperSize);

    Integer q1 = Integer::divideRecursively(upper1, upper2);
    Integer r1 = upper1 - q1 * upper2;

    Integer comb;
    comb.digitsInteger = List<int>::concatenate(r1.digitsInteger, lower1.digitsInteger);

    Integer q2 = Integer::divideRecursively(comb, upper1);

    q1.digitsInteger = List<int>::concatenate(q1.digitsInteger, q2.digitsInteger);
    return q1;
}

List<Integer> Integer::extendEuclidean(const Integer& num1, const Integer& num2)
{
    List<Integer> u = {(num1.sign)? num1: -num1, 1, 0};
    List<Integer> v = {(num2.sign)? num2: -num2, 0, 1};

    while(0 != v[0])
    {
        Integer q = u[0]/v[0];

        List<Integer> r = {u[0] - (q*v[0]), u[1] - (q*v[1]), u[2] - (q*v[2])};
        u = v;
        v = r;
    }
    return u;
}

Integer Integer::binaryEcludian(Integer n1, Integer n2)
{
    if(!n1.sign)
        n1.sign = true;
    if(!n2.sign)
        n2.sign = true;
    if(n1 == 0 || n2 == 0)
        return ((n1 < n2) ? n2 : n1); //*max

    Integer gcd = 1;
    while(n1.digitAt(0)%2 == 0 && n2.digitAt(0)%2 == 0)
    {
        n1 = n1.divideBy2();
        n2 = n2.divideBy2();
        gcd = 2*gcd;
    }

    while(0 < n1 && n2 != 1)
    {
        while(n1.digitAt(0)%2 == 0) n1 = n1.divideBy2();
        while(n2.digitAt(0)%2 == 0) n2 = n2.divideBy2();
        Integer t = n1 - n2;
        t.sign = true;
        if(n1 < n2) n2 = n1; 
        n1 = t;
    }
    return gcd*n2;
}

void Integer::changeBase(int newBase, Integer& number)
{
    if(newBase < 2) throw std::invalid_argument("Base must be grader than 2");
    Integer divisor;
    divisor.BASE = number.BASE;
    divisor.addDigit(newBase);
    Integer zero = 0;
    
    List<int> digit;
    while(number != zero)
    {
        Integer quotient = number/divisor;
        //añadir el residuo de la división
        digit.add((number - quotient*divisor).digitAt(0));
        number = quotient;
    }

    number.BASE = newBase;
    number.digitsInteger = digit;
    Integer::cleanDigits(number);
}

//***STREAM OPERATORS***

std::ostream& operator<<(std::ostream& os, const Integer& number)
{
    if(number.digitsInteger.size() == 0) return os << '0';

    if(!number.sign) os << "-";
    
    os << number.digitAt(number.digitsInteger.size() - 1);
    if(number.BASE != Integer::DEFAULT_BASE)
    {
        for(int i = number.digitsInteger.size() - 2; i >= 0; i--)
            os << number.digitAt(i);
    }
    else for(int i = number.digitsInteger.size() - 2; i >= 0; i--)
    {
        for(int j = 0; j < Integer::digitsByBlock - Integer::getNumOfDigits(number.digitAt(i)); j++)
            os << '0';
        os << number.digitAt(i);
    }  
    return os /*<< " (based-)" << number.BASE*/;
}

std::istream& operator>>(std::istream& is, Integer& num)
{
    long long read;
    is >> read;
    num = read;
    return is;
}


//***GETTERS***

int Integer::getBase() const
{
    return BASE;
}

int Integer::getNumberSize() const
{
    return digitsInteger.size();
}

List<int> Integer::getList()
{
    return List(digitsInteger);
}

bool Integer::isEven() const
{
    return digitAt(0)%2 == 0;
}

