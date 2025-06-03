#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <algorithm>
#include <sstream>
#include <cmath>
#include "../Numbers/Integer.cpp"
#include "../Numbers/Number.cpp"
#include "../Numbers/Rational.h"
#include "../Numbers/ClasesImplementation/Rational.cpp"
#include "../utils/OrderedList.cpp"

// template <typename T>
// class Comparable
// {
// public:
//     virtual bool operator==(const T& other) const = 0;
//     virtual bool operator<(const T& other) const = 0;

//     friend bool operator!=(const T& comp1, const T& comp2) {
//         return !(comp1 == comp2);
//     }

//     friend bool operator>(const T& comp1, const T& comp2) {
//         return comp1 < comp2;
//     }

//     friend bool operator<=(const T& comp1, const T& comp2) {
//         return !(comp2 < comp1);
//     }

//     friend bool operator>=(const T& comp1, const T& comp2) {
//         return !(comp1 < comp2);
//     }

//     virtual ~Comparable() = default;
// };

// template <typename T>
// class Number: public Comparable<T>
// {
//     protected:
//         static const int DEFAULT_BASE = 100000;
//         // bool base_initialized;
//         bool sign;
//         int BASE;
//     public:
//         Number() : sign(true), BASE(DEFAULT_BASE) {}
//         Number(bool sgn, int base) : sign(sgn), BASE(base) {}
//         Number(bool sgn) : sign(sgn), BASE(DEFAULT_BASE) {}
//         ~Number() {}

//         virtual bool operator<(const T& other) const = 0;
//         virtual bool operator==(const T& other) const = 0;
//         virtual T operator=(const T& other) = 0;
        
//         virtual T operator+(const T& other) const = 0;
//         virtual T operator-() const = 0;
//         virtual T operator-(const T& other) const = 0;
//         virtual T operator*(const T& other) const = 0;
//         virtual T operator/(const T& other) const = 0;
//         //virtual T operator%(const T& other) const = 0;
//         virtual T operator^(const T& other) const = 0;
        
//         friend T& operator+=(T& lhs, const T& rhs)
//         {
//             T result = lhs + rhs;
//             lhs = result;
//             return lhs;
//         }

//         friend T& operator-=(T& lhs, const T& rhs)
//         {
//             T result = lhs - rhs;
//             lhs = result;
//             return lhs;
//         }

//         friend T& operator*=(T& lhs, const T& rhs)
//         {
//             T result = lhs * rhs;
//             lhs = result;
//             return lhs;
//         }

//         friend T& operator/=(T& lhs, const T& rhs)
//         {
//             T result = lhs / rhs;
//             lhs = result;
//             return lhs;
//         }

//         /*friend T& operator%=(T& lhs, const T& rhs)
//         {
//             T result = lhs % rhs;
//             lhs = result;
//             return lhs;
//         }*/

//         friend T& operator^=(T& lhs, const T& rhs)
//         {
//             T result = lhs ^ rhs;
//             lhs = result;
//             return lhs;
//         }

//         bool getSign() const {return sign;}

//         void setSign(bool sign) {sign = sign;}
// };



// template <typename U>
// class Iterator
// {
//     private:
//         U* ptr;
//     public:
//         Iterator(U* p) : ptr(p) {}

//         U& operator*() const { return *ptr; }

//         Iterator& operator++() 
//         {
//             ptr++;
//             return *this;
//         }

//         bool operator!=(const Iterator& other) const
//         {
//             return ptr != other.ptr;
//         }
// };



// template <typename U>
// class Iterable
// {
//     public:
//         virtual Iterator<U> begin() const = 0;
//         virtual Iterator<U> end() const = 0;
// };



// template <typename U>
// class List: public Iterable<U> {
//     protected:
//         static const int DEFAULT_INITIAL_SIZE = 10;
//         static constexpr double DEFAULT_RESIZE = 1.4;

//         U* array;
//         int capacity;
//         int length;


//         void resize()
//         {
//             int NEW_CAPACITY = capacity*DEFAULT_RESIZE;
//             U* help = array;
//             array = new U[NEW_CAPACITY];

//             for(int i = 0; i < length; i++)
//                 array[i] = help[i];

//             delete[] help;
//             capacity = NEW_CAPACITY;
//         }

        
//     public:
//         List(int INITIAL_SIZE)
//         {
//             array = new U[INITIAL_SIZE];
//             capacity = INITIAL_SIZE;
//             length = 0;
//         }

//         List() : List(DEFAULT_INITIAL_SIZE) {}

//         List(const List<U>& another) : List(another.size())
//         {
//             for(int i = 0; i < another.length; i++)
//                 add(another[i]);
//         }

//         List(std::initializer_list<U> values)
//         {
//             length = values.size();
//             capacity = length > 0 ? length : DEFAULT_INITIAL_SIZE;
//             array = new U[capacity];
//             int i = 0;
//             for (const U& val : values)
//                 array[i++] = val;
//         }


//         ~List() 
//         {
//             delete[] array;
//         }

//         void add(const U& item, int index)
//         {
//             if(length < index || index < 0)
//                 return;
            
//             if(length == capacity) 
//                 resize();

//             for(int i = length-1; index <= i; i--)
//                 array[i+1] = array[i];
            
//             array[index] = item;
//             length++;
//         }

//         void replace(const U& item, int index)
//         {
//             if(length <= index || index < 0)
//                 throw std::invalid_argument("Index out bound");

//             array[index] = item;
//         }

//         // add last*
//         void add(const U& item)
//         {
//             add(item, length);
//         }

//         U pop(int index)
//         {
//             if(length <= index || index < 0 || length == 0)
//                 throw std::out_of_range("Index out of bounds");

//             U item = array[index];
//             for(int i = index; i < length - 1; i++)
//                 array[i] = array[i+1];

//             length--;
//             return item;
//         }

//         U pop()
//         {
//             return pop(0);
//         }

//         bool isEmpty()
//         {
//             return length == 0;
//         }

//         int size() const
//         {
//             return length;
//         }

//         int getCapacity() const 
//         {
//             return capacity;
//         }

//         U* getArray() const
//         {
//             return array;
//         }

//         void clear()
//         {
//             delete[] array;
//             length = 0;
//             array = new U[DEFAULT_INITIAL_SIZE];
//             capacity = DEFAULT_INITIAL_SIZE;
//         }

//         template <typename M>
//         static List<M> concatenate(const List<M> l1, const List<M> l2)
//         {
//             List<M> toR;
//             for(M item: l1)
//                 toR.add(item);
//             for(M item: l2)
//                 toR.add(item);
//             return toR;
//         }

//         friend bool operator==(const List<U> l1, const List<U> l2)
//         {
//             if(l1.size() != l2.size()) return false;

//             for(int i = 0; i < l1.size(); i++)
//                 if(l1[i] != l2[i]) return false;

//             return true;
//         }

//         U& operator[](int index) const
//         {
//             if (index < 0 || index >= length) {
//                 throw std::invalid_argument("Index out of the range, entro");
//             }

//             return this->array[index];
//         }

//         List<U>& operator=(const List<U>& another)
//         {
//             delete[] array;
//             capacity = another.capacity;
//             length = another.length;
//             array = new U[capacity];
//             for (int i = 0; i < length; i++)
//                 array[i] = another.array[i];

//             return *this;
//         }


//         friend std::ostream& operator<<(std::ostream& os, const List& list)
//         {
//             os << "[";
//             for(int i = 0; i < list.length; i++)
//             {
//                 os << list.array[i];
//                 if(i != list.length - 1)
//                     os << ", ";
//             }
//             os << "]";
//             return os;
//         }
        
//         Iterator<U> begin() const { return Iterator<U>(array); }
//         Iterator<U> end() const { return Iterator<U>(array + length); }
// };



// class Integer: public Number<Integer> {
//     private:
//         static const int digitsByBlock = 5;
//         List<int> digitsInteger;

//         //***NON-STATIC HELPER METHODS***
//         void addDigit(long long newDigit);
//         void addDigit(const Integer& newDigit);
//         void forceAdd(long long newDigit);
//         void setSize(int newSize);
//         int digitAt(int index) const;
//         int operator[](int index) const;

//         //***STATIC HELPER METHODS***
//         static void cleanDigits(Integer& num);
//         static int digits(long long x);
//         static int max_int(int x, int y);
//         static int min_int(int x, int y);
//         static int getNumOfDigits(long long x);

//         //***PARTITION METHODS FOR ALGORITHMS***
//         Integer getHighPart(int index) const;
//         Integer getLowPart(int index) const;

//         //***MULTIPLICATION ALGORITHMS***
//         static Integer multiplyConventional(const Integer& num1, const Integer& num2);
//         static Integer multiplyKaratsuba(const Integer& num1, const Integer& num2);
        
//         //***DIVISION HELPER***
//         static int estimateQuotient(const Integer& rem, const Integer& divisor);

//     public:
//         //***CONSTRUCTORS***
//         Integer();
//         Integer(long long x);
//         Integer(const Integer& toC);
//         ~Integer();

//         //***COMPARISON OPERATORS***
        
//         bool operator==(const Integer& other) const override;
//         friend bool operator==(const int int_num, const Integer& num);
//         friend bool operator==(const Integer& num, const int int_num);
        
//         friend bool operator!=(const Integer& num1, const int num2);
//         friend bool operator!=(const int num1, const Integer& num2);
        
//         bool operator<(const Integer& other) const override;
//         bool operator<(const int int_num);
//         friend bool operator<(int int_num1, const Integer& num2);

//         friend bool operator<=(const int int_num, const Integer& num);
//         friend bool operator<=(const Integer& num, const int int_num);
        
//         friend bool operator>(const int int_num1, const Integer& num2);
//         friend bool operator>(const Integer& num1, const int int_num2);
        
//         friend bool operator>=(const int int_num1, const Integer& num2);
//         friend bool operator>=(const Integer& num1, const int int_num2);

//         //***ARITHMETIC OPERATORS***
//         Integer operator+(const Integer& other) const override;
//         friend Integer operator+(int num1, const Integer& num2);
//         friend Integer operator+(const Integer& num1, int num2);

//         Integer operator-(const Integer& other) const override;
//         friend Integer operator-(int num1, Integer& num2);
//         friend Integer operator-(Integer& num1, int num2);
//         Integer operator-() const override;

//         Integer operator*(const Integer& other) const override;
//         friend Integer operator*(int num1, const Integer& num2);
//         friend Integer operator*(const Integer& num1, int num2);

//         Integer operator/(const Integer& other) const override;
//         friend Integer operator/(int num1, const Integer& num2);
//         friend Integer operator/(const Integer& num1, int num2);

//         Integer operator%(const Integer& other) const;
//         friend Integer operator%(int num1, const Integer& num2);
//         friend Integer operator%(const Integer& num1, int num2);

//         Integer operator^(const Integer& other) const override;
        
//         Integer operator=(const Integer& other) override;
//         Integer operator=(const long long num_int);

//         //***NON-STATIC UTILITY METHODS***
//         Integer divideBy2() const;
//         Integer multiplyByDigit(int x) const;
        
//         //***STATIC UTILITY METHODS***
//         static Integer abs(const Integer& r);
//         static Integer divideRecursively(const Integer& num1, const Integer& num2);
//         static Integer multiplyByBase(const Integer& num, int times);
//         static Integer binaryEuclidean(Integer n1, Integer n2);
//         static List<Integer> extendEuclidean(const Integer& num1, const Integer& num2);
        
//         //***BASE CONVERSION***
//         void changeBase(int newBase, Integer& number);

//         //***STREAM OPERATORS***
//         friend std::ostream& operator<<(std::ostream& os, const Integer& number);
//         friend std::istream& operator>>(std::istream& is, Integer& num);
        
//         //***GETTERS***
//         int getBase() const;
//         int getNumberSize() const;
//         List<int> getList();
//         bool isEven() const;
// };

// void Integer::addDigit(long long newDigit)
// {
//     if(newDigit <= 0) return;
//     forceAdd(newDigit);
// }

// void Integer::addDigit(const Integer& newDigit)
// {
//     if(BASE != newDigit.BASE)
//         throw std::invalid_argument("Not implemented digits in diferents bases");
    
//     for(int x: newDigit.digitsInteger)
//         digitsInteger.add(x);
    
// }

// void Integer::forceAdd(long long newDigit)
// {
//     if(newDigit == 0) digitsInteger.add(0);
//     while(0 < newDigit)
//     {
//         int res = newDigit%BASE;
//         newDigit /= BASE;
//         digitsInteger.add(res);
//     }
// }

// void Integer::setSize(int newSize)
// {
//     List<int> newList(newSize);
//     for(int i = 0; i < newSize; i++)
//         newList.add(digitAt(i));

//     digitsInteger = newList;
// }


// int Integer::digitAt(int index) const
// {
//     try{
//         return digitsInteger[index];
//     }catch(const std::invalid_argument& e)
//     {
//         return 0;
//     }
// }

// //*Only to access the index (for now)
// int Integer::operator[](int index) const {
//     if (index >= 0 && index < digitsInteger.size()) {
//         return digitsInteger[index];
//     }
//     return 0;
// }

// //***STATIC HELPER METHODS***

// void Integer::cleanDigits(Integer& num)
// {
//     int length = num.digitsInteger.getCapacity();
//     while(0 < length && num.digitAt(length-1) == 0)
//         length--;
//     if(length == num.getNumberSize()) return;
//     List<int> clean(length);
//     for(int i = 0; i < length; i++)
//         clean.add(num.digitAt(i));

//     num.digitsInteger = clean;
// }

// int Integer::max_int(int x, int y)
// {
//     if(x < y) return y;
//     return x;
// }

// int Integer::min_int(int y, int x)
// {
//     if(x < y) return x;
//     return y;
// }

// int Integer::getNumOfDigits(long long x)
// {
//     if(x == 0) return 1;
//     int c = 0;
//     while(x != 0)
//     {
//         x /= 10;
//         c++;
//     }
//     return c;
// }


// //***PARTITION METHODS FOR ALGORITHMS***

// Integer Integer::getHighPart(int index) const
// {
//     Integer toR;
//     for(int i = digitsInteger.size() - index -1; i < digitsInteger.size(); i++)
//         toR.addDigit(this->digitAt(i));

//     Integer::cleanDigits(toR);
//     return toR;
// }

// Integer Integer::getLowPart(int index) const
// {
//     Integer toR;
//     for(int i = 0; i < index; i++)
//         toR.digitsInteger.add(this->digitAt(i));
//     Integer::cleanDigits(toR);
//     return toR;
// }


// //***MULTIPLICATION ALGORITHMS***

// Integer Integer::multiplyConventional(const Integer& num1, const Integer& num2)
// {
//     Integer product;
//     product.BASE = num1.BASE;
//     int totalSize = num1.getNumberSize() + num2.getNumberSize();

//     for(int i = 0; i < totalSize; i++)
//         product.digitsInteger.add(0);

//     for(int j = 0; j < num2.getNumberSize(); j++)
//     {
//         if(num2.digitAt(j) == 0) continue;
//         long long carry = 0;
//         for(int i = 0; i < num1.getNumberSize(); i++)
//         {
//             long long realSum = carry + 1LL * num1.digitAt(i)*num2.digitAt(j) + product.digitAt(i+j);
//             product.digitsInteger.replace(realSum%num1.BASE, i+j);
//             carry = realSum/num1.BASE;
//         }
//         product.digitsInteger.replace(carry, num1.getNumberSize()+j);
//     }

//     Integer::cleanDigits(product);
//     return product;
// }

// Integer Integer::multiplyKaratsuba(const Integer& num1, const Integer& num2)
// {
//     if(num1.getNumberSize() <= 15 || num2.getNumberSize() <= 15)
//         return multiplyConventional(num1, num2);
//     int upperSize = Integer::max_int(num1.getNumberSize(), num2.getNumberSize())/2;

//     Integer uper1 = num1.getHighPart(upperSize);
//     Integer lower1 = num1.getLowPart(upperSize);
//     Integer upper2 = num2.getHighPart(upperSize);
//     Integer lower2 = num2.getLowPart(upperSize);

//     Integer U = multiplyKaratsuba(uper1, upper2);
//     Integer V = multiplyKaratsuba(lower1, lower2);
//     Integer W = multiplyKaratsuba(uper1 + lower1, upper2 + lower2) -U -V;
//     return multiplyByBase(V, 2*upperSize) + multiplyByBase(W, upperSize) + U;
// }

// //***DIVISION HELPER***


// int Integer::estimateQuotient(const Integer& rem, const Integer& divisor) {
//     const int n = divisor.getNumberSize(), m = rem.getNumberSize();
//     const long long top = 1LL * rem.digitAt(m-1) * rem.BASE + rem.digitAt(m-2);
//     return min_int(top / divisor.digitAt(n-1), rem.BASE-1);
// }


// //---PRIVATE METHODS---

// //***CONSTRUCTORS AND DESTRUCTOR***

// Integer::Integer(): Number<Integer>() {}
// Integer::Integer(long long x): Number<Integer>()
// {
//     sign = x >= 0;
//     addDigit(sign? x: -x);
//     Integer::cleanDigits(*this);
// }
// Integer::Integer(const Integer& toC) : Number<Integer>(toC.sign, toC.BASE), digitsInteger(toC.digitsInteger) {}
// Integer::~Integer()=default;


// //***COMPARISON OPERATORS***

// bool Integer::operator==(const Integer& other) const 
// {
//     return other.sign == sign &&
//             other.BASE == BASE &&
//             other.digitsInteger == digitsInteger;
// }  

// bool operator==(const int int_num, const Integer& num)
// {
//     Integer num1(int_num);
//     return num1 == num;
// }

// bool operator==(const Integer& num, const int int_num)
// {
//     Integer num2(int_num);
//     return num == num2;
// }

// bool operator!=(const Integer& num1, const int num2)
// {
//     Integer num2_integer = num2;
//     return !(num1 == num2_integer);
// }

// bool operator!=(const int num1, const Integer& num2)
// {
//     Integer num1_integer(num1);
//     return !(num1_integer == num2);
// }

// bool Integer::operator<(const Integer& other) const
// {
//     if(sign == 0 && other.sign == 1) return true;
//     else if(sign == 1 && other.sign == 0) return false;
//     else if(sign == 1 && other.sign == 1)
//     {
//         //*This case does take into account when both numbers are equal
//         int length = Integer::max_int(this->getNumberSize(), other.getNumberSize());
//         for(int i = length - 1; 0 <= i; i--)
//         {
//             if(other.digitAt(i) < this->digitAt(i))
//                 return false;
//             else if(this->digitAt(i) < other.digitAt(i))
//                 return true;
//         }

//         return false;
//     }
//     else
//         //*Both are negative
//         return -other < -(*this); //!May be wrong
// }

// bool Integer::operator<(const int int_num)
// {
//     Integer num = int_num;
//     return (*this) < num;
// }

// bool operator<(int int_num1, const Integer& num2)
// {
//     Integer num1(int_num1);
//     return num1 < num2;
// }


// bool operator<=(const int int_num, const Integer& num)
// {
//     Integer num1(int_num);
//     return num1 <= num;
// }

// bool operator<=(const Integer& num, const int int_num)
// {
//     Integer num2(int_num);
//     return num <= num2;
// }


// bool operator>(const int int_num1, const Integer& num2)
// {
//     return !(int_num1 <= num2);
// }

// bool operator>(const Integer& num1, const int int_num2)
// {
//     return !(num1 <= int_num2);
// }

// bool operator>=(const int int_num1, const Integer& num2)
// {
//     return int_num1 > num2 || int_num1 == num2;
// }

// bool operator>=(const Integer& num1, const int int_num2)
// {
//     return num1 > int_num2 || num1 == int_num2;
// }
        

// //***ARITHMETIC OPERATORS***

// Integer Integer::operator+(const Integer& other) const
// {
//     if (BASE != other.BASE) 
//         throw std::invalid_argument("Not defined sum of integers in different Bases yet");
    
//     if (sign ^ other.sign) 
//     {
//         if(sign)
//             return *this - (-other);
//         return other - (-(*this)); //!This may not work.
//     }

//     Integer sumOfIntegers;
//     sumOfIntegers.BASE = BASE;
//     int length = Integer::max_int(getNumberSize(), other.getNumberSize());
//     int c = 0;
//     long long res = 0;

//     while (c < length || res != 0)
//     {
//         res += digitAt(c) + other.digitAt(c);
//         sumOfIntegers.forceAdd(res % BASE);
//         res /= BASE;
//         c++;
//     }
//     sumOfIntegers.sign = sign;
//     Integer::cleanDigits(sumOfIntegers);
//     return sumOfIntegers;
// }

// Integer operator+(int num1, const Integer& num2)
// {
//     Integer new_int = num1;
//     return new_int + num2;
// }

// Integer operator+(const Integer& num1, int num2)
// {
//     Integer new_int = num2;
//     return num1 + new_int;
// }

// Integer Integer::operator-(const Integer& other) const
// {
//     if((*this) < other)
//         return -(other - (*this));
//     if(!other.sign)
//         return *this + (-other);

//     bool carry = 0;
//     int maxSize = Integer::max_int(getNumberSize(), other.getNumberSize());
//     Integer result;
//     result.BASE = BASE;

//     for(int i = 0; i < maxSize; i++)
//     {
//         int kResult = digitAt(i) - other.digitAt(i) - carry;
//         if(kResult < 0)
//         {
//             carry = 1;
//             kResult += BASE;
//         }
//         else carry = 0;
//         result.forceAdd(kResult);
//     }

//     Integer::cleanDigits(result);
//     return result;
// }

// Integer operator-(int num1, Integer& num2)
// {
//     Integer new_int = num1;
//     return new_int - num2;
// }

// Integer operator-(Integer& num1, int num2)
// {
//     Integer new_int = num2;
//     return num1 - new_int;
// }

// Integer Integer::operator-() const
// {
//     Integer toR(*(this));
//     toR.sign = !toR.sign;
//     return toR;
// }

// Integer Integer::operator*(const Integer& other) const
// {
//     if(BASE != other.BASE) throw std::invalid_argument("Error");
//     if(*this == 0 || other == 0) return Integer();
//     Integer mult = Integer::multiplyKaratsuba(*this, other);
//     mult.sign = !(sign ^ other.sign);
//     mult.BASE= BASE;
//     Integer::cleanDigits(mult);
//     return mult;
// }

// Integer operator*(int num1, const Integer& num2)
// {
//     Integer new_int = num1;
//     return new_int * num2;
// }

// Integer operator*(const Integer& num1, int num2)
// {
//     Integer new_int = num2;
//     return num1 * new_int;
// }

// Integer Integer::operator/(const Integer& other) const
// {
//     if(other == 0) throw std::invalid_argument("Division by zero");
//     if(BASE != other.BASE) throw std::invalid_argument("Different bases");
    
//     // Manejo rápido de casos especiales
//     if(getNumberSize() < other.getNumberSize()) return 0;
//     if(*this == other) return 1;
//     if(other == 1) return *this;

//     if(other == 2)
//         return this->divideBy2();

//     Integer a = (sign) ? *this: -*this;
//     Integer b = (other.sign)? other: -other;
//     if(b.digitAt(b.getNumberSize() -1) < BASE/2)
//     {
//         long long x = BASE/(b.digitAt(b.getNumberSize() -1) + 1);
//         a = a.multiplyByDigit(x);
//         b = b.multiplyByDigit(x);
//     }

//     const int m = a.getNumberSize() - b.getNumberSize();
//     Integer quant;
//     quant.setSize(m + 1);

//     Integer currentRemainder;
//     for(int i = m; i < a.getNumberSize(); i++)
//         currentRemainder.digitsInteger.add(a.digitAt(i));

//     for (int j = m; j >= 0; --j) {
        
//         int q;
//         if(currentRemainder < b) q = 0;
//         else q = Integer::estimateQuotient(currentRemainder, b);
//         Integer help = b.multiplyByDigit(q);
//         while (help > currentRemainder) {
//             q--; help -= b;
//             // std::cout << q << std::endl;
//         }
        
//         currentRemainder = currentRemainder - help;
//         quant.digitsInteger.replace(q, j); 
//         currentRemainder.digitsInteger.add(a.digitAt(j), 0);
//     }

//     Integer::cleanDigits(quant);
//     return quant;
// }

// Integer operator/(int num1, const Integer& num2)
// {
//     Integer new_int = num1;
//     return new_int / num2;
// }

// Integer operator/(const Integer& num1, int num2)
// {
//     Integer new_int = num2;
//     return num1 / new_int;
// }

// Integer Integer::operator%(const Integer& other) const 
// {
//     //? Could also be this->add((this->divide(other)).multiply(other).negate());
//     return *this - (*this/other)*other;
// }

// Integer operator%(int num1, const Integer& num2)
// {
//     Integer new_int = num1;
//     return new_int % num2;
// }

// Integer operator%(const Integer& num1, int num2)
// {
//     Integer new_int = num2;
//     return num1 % new_int;
// }

// Integer Integer::operator^(const Integer& other) const
// {
//     if (other < Integer(0))
//         return 1/((*this)^other);

//     Integer exp(other);
//     Integer base(*this);
//     Integer result(1);
//     while (exp > 0)
//     {
//         if (!exp.isEven())
//             result = result * base;

//         base *= base;
//         exp /= 2;
//     }

//     return result;
// }

// Integer Integer::operator=(const Integer& other)
// {
//     this->sign = other.sign;
//     this->BASE = other.BASE;
//     this->digitsInteger = other.digitsInteger;
//     return *this;
// }

// Integer Integer::operator=(const long long num_int)
// {
//     Integer num(num_int);
//     return *this = num;
// }


// //***NON-STATIC UTILITY METHODS***

// Integer Integer::divideBy2() const
// {
//     Integer result;
//     result.sign = this->sign;
//     result.setSize(digitsInteger.size());

//     int carry = 0;
//     for (int i = (int)digitsInteger.size() - 1; i >= 0; --i) {
//         long long current = carry * 100000LL + this->digitAt(i);  // base = 10^5
//         result.digitsInteger.replace(current / 2, i);
//         carry = current % 2;
//     }

//     Integer::cleanDigits(result);
//     return result;
// }  

// Integer Integer::multiplyByDigit(int x) const
// {
//     if(x == 0) return Integer(0);
//     if(x == 1) return *this;
//     if(x == -1) return -*this;
//     bool flag = false;
//     if(x < 0)
//     {
//         flag = true;
//         x = -x;
//     }

//     Integer result; //result.setSize(this->getNumberSize() + 1);
//     long long carry = 0;
//     for(long long num: digitsInteger)
//     {
//         long long sum = x*num + carry;
//         result.digitsInteger.add(sum%BASE);
//         carry = sum/BASE;
//     }
//     if(carry > 0) result.addDigit(carry);
//     result.sign = (!flag == this->sign);
//     Integer::cleanDigits(result);
//     return result;
// }


// //***STATIC UTILITY METHODS***

// Integer Integer::abs(const Integer& r)
// {
//     if(r.sign) return r;
//     return -r;
// }

// Integer Integer::multiplyByBase(const Integer& num, int times)
// {
//     Integer result;
//     for(int i = 0; i < times; i++)
//         result.digitsInteger.add(0);
//     result.addDigit(num);
//     return result;
// }

// Integer Integer::divideRecursively(const Integer& num1, const Integer& num2)
// {
//     if(num1.getNumberSize() < 15 || num2.getNumberSize() < 15)
//         return num1/num2;

//     int upperSize = Integer::max_int(num1.getNumberSize(), num2.getNumberSize())/2;

//     Integer upper1 = num1.getHighPart(upperSize);
//     Integer lower1 = num1.getLowPart(upperSize);
//     Integer upper2 = num2.getHighPart(upperSize);
//     //Integer lower2 = num2.getLowPart(upperSize);

//     Integer q1 = Integer::divideRecursively(upper1, upper2);
//     Integer r1 = upper1 - q1 * upper2;

//     Integer comb;
//     comb.digitsInteger = List<int>::concatenate(r1.digitsInteger, lower1.digitsInteger);

//     Integer q2 = Integer::divideRecursively(comb, upper1);

//     q1.digitsInteger = List<int>::concatenate(q1.digitsInteger, q2.digitsInteger);
//     return q1;
// }

// List<Integer> Integer::extendEuclidean(const Integer& num1, const Integer& num2)
// {
//     List<Integer> u = {(num1.sign)? num1: -num1, 1, 0};
//     List<Integer> v = {(num2.sign)? num2: -num2, 0, 1};

//     while(0 != v[0])
//     {
//         Integer q = u[0]/v[0];

//         List<Integer> r = {u[0] - (q*v[0]), u[1] - (q*v[1]), u[2] - (q*v[2])};
//         u = v;
//         v = r;
//     }
//     return u;
// }

// Integer Integer::binaryEuclidean(Integer n1, Integer n2)
// {
//     if(!n1.sign)
//         n1.sign = true;
//     if(!n2.sign)
//         n2.sign = true;
//     if(n1 == 0 || n2 == 0)
//         return ((n1 < n2) ? n2 : n1); //*max

//     Integer gcd = 1;
//     while(n1.digitAt(0)%2 == 0 && n2.digitAt(0)%2 == 0)
//     {
//         n1 = n1.divideBy2();
//         n2 = n2.divideBy2();
//         gcd = 2*gcd;
//     }

//     while(0 < n1 && n2 != 1)
//     {
//         while(n1.digitAt(0)%2 == 0) n1 = n1.divideBy2();
//         while(n2.digitAt(0)%2 == 0) n2 = n2.divideBy2();
//         Integer t = n1 - n2;
//         t.sign = true;
//         if(n1 < n2) n2 = n1; 
//         n1 = t;
//     }
//     return gcd*n2;
// }

// void Integer::changeBase(int newBase, Integer& number)
// {
//     if(newBase < 2) throw std::invalid_argument("Base must be grader than 2");
//     Integer divisor;
//     divisor.BASE = number.BASE;
//     divisor.addDigit(newBase);
//     Integer zero = 0;
    
//     List<int> digit;
//     while(number != zero)
//     {
//         Integer quotient = number/divisor;
//         //añadir el residuo de la división
//         digit.add((number - quotient*divisor).digitAt(0));
//         number = quotient;
//     }

//     number.BASE = newBase;
//     number.digitsInteger = digit;
//     Integer::cleanDigits(number);
// }

// //***STREAM OPERATORS***

// std::ostream& operator<<(std::ostream& os, const Integer& number)
// {
//     if(number.digitsInteger.size() == 0) return os << '0';

//     if(!number.sign) os << "-";
    
//     os << number.digitAt(number.digitsInteger.size() - 1);
//     if(number.BASE != Integer::DEFAULT_BASE)
//     {
//         for(int i = number.digitsInteger.size() - 2; i >= 0; i--)
//             os << number.digitAt(i);
//     }
//     else for(int i = number.digitsInteger.size() - 2; i >= 0; i--)
//     {
//         for(int j = 0; j < Integer::digitsByBlock - Integer::getNumOfDigits(number.digitAt(i)); j++)
//             os << '0';
//         os << number.digitAt(i);
//     }  
//     return os /*<< " (based-)" << number.BASE*/;
// }

// std::istream& operator>>(std::istream& is, Integer& num)
// {
//     long long read;
//     is >> read;
//     num = read;
//     return is;
// }


// //***GETTERS***

// int Integer::getBase() const
// {
//     return BASE;
// }

// int Integer::getNumberSize() const
// {
//     return digitsInteger.size();
// }

// List<int> Integer::getList()
// {
//     return List<int>(digitsInteger);
// }

// bool Integer::isEven() const
// {
//     return digitAt(0)%2 == 0;
// }



// class Rational: public Number<Rational>
// {
//     private:
//         Integer numerator, denominator;

//         // aqui se calcula a^{1/p}, con p entero
//         Rational root(const Integer& po) const;
//         // aqui se calcula a^p, con p entero
//         Rational integerPow(Integer po);
//     public:
//         Rational(): Rational(0, 1) {}
//         Rational(const Integer& numerator) 
//         {
//             std::cout << numerator << "\n";
//             this->sign = numerator.getSign();
//             this->numerator = numerator;
//             this->denominator = 1;
//             this->numerator.setSign(true);
//         }

//         Rational(const Integer& num, const Integer& den)
//         {
//             if (den == 0)
//                 throw std::invalid_argument("Denominator cannot be zero");

//             sign = (num.getSign() == den.getSign());

//             Integer absNum = num;
//             Integer absDen = den;
//             absNum.setSign(true);
//             absDen.setSign(true);

//             Integer g = Integer::binaryEuclidean(absNum, absDen);
//             if(g > 1)
//             {
//                 numerator   = absNum / g;
//                 denominator = absDen / g;
//             }
//             else
//             {
//                 numerator = absNum;
//                 denominator = absDen;
//             }
//         }

//         Rational(double x);

//         bool operator==(const Rational& other) const;
//         bool operator<(const Rational& other) const;

//         Rational operator+(const Rational& other) const override;
//         Rational operator-(const Rational& other) const;
//         Rational operator-() const;
//         Rational operator*(const Rational& other) const;
//         Rational operator/(const Rational& other) const;
//         Rational operator^(const Rational& other) const;
//         Rational operator=(const Rational& other);

//         static Rational abs(const Rational& p)
//         {
//             if(p < 0) return -p;
//             return p;
//         }

//         friend std::ostream& operator<<(std::ostream& os, const Rational& num)
//         {
//             if(!num.sign)  os << "-";
//             if(num.denominator == 1)
//             {
//                 os << num.numerator;
//                 return os;
//             }
//             Integer nume = num.numerator, den = num.denominator;

//             for(int i = 0; i < 5; i++)
//             {
//                 Integer q = nume / den;
//                 if(i == 1) os << ".";
//                 os << q;
//                 nume = nume - q * den;
//                 nume = Integer::multiplyByBase(nume, 1);
//             }

//             return os;
//         }

//         Integer getNumerator()
//         {
//             return numerator;
//         }

//         Integer getDenominator()
//         {
//             return denominator;
//         }
// };

// Rational Rational::root(const Integer& po) const
// {
//     return 1;
// }

// Rational Rational::integerPow(Integer exp)
// {
//     if(numerator == 0) return 0;
//     if(numerator == denominator) return 1;
//     bool flag = false;
//     if (exp < 0)
//     {
//         flag = true;
//         exp.setSign(true);
//     }

//     Rational base = *this;
//     Rational result = 1;
//     while (exp > 0)
//     {
//         if (!exp.isEven())
//             result = result * base;

//         base = base * base;
//         exp = exp.divideBy2();
//     }

//     if(flag) return Rational(result.denominator, result.numerator);
//     return result;
// }

// Rational::Rational(double x)
// {
//     if(x < 0) 
//     {
//         this->sign = 0;
//         x = -x;
//     }

//     long long digits = x;
//     int base = 0;

//     while(x != digits)
//     {
//         x *= 10;
//         digits = x;
//         base++;
//     }

//     denominator = 1;
//     for(int i = 0; i < base % 5; i++)
//         denominator = denominator * 10;
//     denominator = Integer::multiplyByBase(denominator, base / 5);
//     numerator = x;

//     Integer gcd = Integer::binaryEuclidean(numerator, denominator);
//     numerator = numerator / gcd;
//     denominator = denominator / gcd;
// }

// bool Rational::operator==(const Rational& other) const 
// {
//     return numerator == other.numerator && denominator == other.denominator;
// }

// bool Rational::operator<(const Rational& other) const 
// {
//     if (!sign && other.sign) return true;
//     if (sign && !other.sign) return false;
//     if(this->sign == 1 && other.sign == 1)
//         return numerator * other.denominator < other.numerator * denominator;

//     return numerator * other.denominator > other.numerator * denominator;
// }

// Rational Rational::operator*(const Rational& other)  const 
// {
//     return Rational(numerator * other.numerator, denominator * other.denominator);
// }

// Rational Rational::operator/(const Rational& other)  const
// {
//     return Rational(numerator * other.denominator, denominator * other.numerator);
// }

// Rational Rational::operator^(const Rational& other) const
// {
//     return (this->root(other.denominator)).integerPow(other.numerator);
// }

// Rational Rational::operator=(const Rational& other)
// {
//     this->sign = other.getSign();
//     numerator = other.numerator;
//     denominator = other.denominator;
//     return *this;
// }

// Rational Rational::operator+(const Rational& other) const
// {       
//     Integer gcd = Integer::binaryEuclidean(denominator, other.denominator);
//     Integer num1 = numerator * ((gcd != 1)? (other.denominator)/gcd: other.denominator);
//     Integer num2 = other.numerator * ((gcd != 1)? (denominator)/gcd: denominator);
//     if(other.sign == this->sign)
//     {
//         Rational result(num1 + num2, (denominator * other.denominator) / gcd);
//         result.setSign(this->sign);
//         return result;
//     }

//     if(!other.sign)
//         return Rational(num1 - num2, (denominator * other.denominator) / gcd);

//     return Rational(num2 - num1, (denominator * other.denominator) / gcd);
// }

// Rational Rational::operator-(const Rational& other) const
// {
//     Rational inv = other;
//     inv.sign = !inv.sign;
//     return *this + inv;
// }

// Rational Rational::operator-() const
// {
//     Rational inv(numerator, denominator);
//     inv.sign = !inv.sign;
//     return inv;
// }


class PolyTerm {
    public:
        Rational coeff;
        //!ISSUE WHEN ORDERING INTEGERS
        int exp;

        PolyTerm() : coeff(Rational(0)), exp(0) {}
        PolyTerm(Rational coeff, int exp) : coeff(coeff), exp(exp) {}
        PolyTerm(Integer coeff, int exp) : coeff(Rational(coeff, Integer(1))), exp(exp) {}
        PolyTerm(int coeff, int exp) : coeff(Rational(coeff)), exp(exp) {}
        ~PolyTerm() {}

        //***ARITHMETIC OPERATIONS***

        friend PolyTerm operator+(const PolyTerm& term1, const PolyTerm& term2) {
            if(term1.exp != term2.exp) throw std::invalid_argument("The terms must have the same exponent for them to be added");
            
            PolyTerm result;
            result.coeff = term1.coeff + term2.coeff;
            result.exp = term1.exp;
            return result;
        }

        friend PolyTerm operator*(const PolyTerm& term1, const PolyTerm& term2) {
            PolyTerm prod;
            prod.coeff = term1.coeff * term2.coeff;
            prod.exp = term1.exp + term2.exp;
            return prod;
        }
        
        //***ISTREAM AND OSTREAM***

        friend std::ostream& operator<<(std::ostream& os, const PolyTerm& term) {
            os << term.coeff << "x^" << term.exp;
            return os;
        }
};

class Polynomial {
private:
    std::vector<Rational> dense;  // Dense representation: coefficients indexed by power
    std::vector<PolyTerm> sparse;  // Sparse representation: [coefficient, power] pairs
    bool is_dense_valid = false;
    bool is_ordered = false;
    bool is_rational = false;
    bool is_sparse_valid = false;
    int degree = 0;

public:

    Polynomial() = default;

    Polynomial(PolyTerm& term) {
        dense = std::vector<Rational>(term.exp);
        degree = term.exp;
        sparse.push_back(term);
        if((term.coeff.getDenominator() != 1) || (term.coeff.getDenominator() != -1)) 
            is_rational = true;
        is_dense_valid = true;
        is_sparse_valid = true;
    }
    Polynomial(const std::string& str) { *this = str; }

    // // Parse polynomial from string
    // void parseFromString(const std::string& poly_str) {
    //     clear();
    //     std::map<int, double> terms;
        
    //     // Clean the string: remove spaces and handle signs
    //     std::string cleaned = poly_str;
    //     cleaned.erase(std::remove(cleaned.begin(), cleaned.end(), ' '), cleaned.end());
        
    //     // Add '+' at the beginning if it doesn't start with '+' or '-'
    //     if (!cleaned.empty() && cleaned[0] != '+' && cleaned[0] != '-') {
    //         cleaned = "+" + cleaned;
    //     }
        
    //     // Regular expression to match terms like +3x^4, -2x^2, +5x, -7, etc.
    //     std::regex term_regex(R"([+-](?:\d*\.?\d*)?(?:x(?:\^-?\d+)?)?)");
        
    //     std::sregex_iterator iter(cleaned.begin(), cleaned.end(), term_regex);
    //     std::sregex_iterator end;
        
    //     for (; iter != end; ++iter) {
    //         std::string term = iter->str();
    //         if (term.empty() || term == "+" || term == "-") continue;
            
    //         double coeff = 0;
    //         int power = 0;
            
    //         // Parse coefficient and power
    //         if (term.find('x') == std::string::npos) {
    //             // Constant term
    //             coeff = std::stod(term);
    //             power = 0;
    //         } else {
    //             // Term with x
    //             size_t x_pos = term.find('x');
                
    //             // Extract coefficient
    //             std::string coeff_str = term.substr(0, x_pos);
    //             if (coeff_str == "+" || coeff_str.empty()) {
    //                 coeff = 1;
    //             } else if (coeff_str == "-") {
    //                 coeff = -1;
    //             } else {
    //                 coeff = std::stod(coeff_str);
    //             }
                
    //             // Extract power
    //             if (x_pos + 1 < term.length() && term[x_pos + 1] == '^') {
    //                 power = std::stoi(term.substr(x_pos + 2));
    //             } else {
    //                 power = 1;  // Just 'x' means x^1
    //             }
    //         }
            
    //         // Add to terms map (combining like terms)
    //         terms[power] += coeff;
    //         degree = std::max(degree, power);
    //     }
        
    //     // Convert to sparse representation
    //     for (const auto& term : terms) {
    //         if (term.second != 0) {  // Only store non-zero coefficients
    //             sparse.push_back({term.second, term.first});
    //         }
    //     }
        
    //     // Sort sparse representation by power (descending)
    //     std::sort(sparse.begin(), sparse.end(), 
    //               [](const std::pair<double, int>& a, const std::pair<double, int>& b) {
    //                   return a.second > b.second;
    //               });
        
    //     is_sparse_valid = true;
    //     generateDense();
    // }
    
    // // Generate dense representation from sparse (stored in descending order of powers)
    // void generateDense() {
    //     if (!is_sparse_valid) return;
        
    //     dense.clear();
    //     dense.resize(degree + 1, 0.0);
        
    //     for (const auto& term : sparse) {
    //         if (term.second >= 0 && term.second <= degree) {
    //             // Store in descending order: index 0 = highest power, index degree = constant term
    //             dense[degree - term.second] = term.first;
    //         }
    //     }
        
    //     is_dense_valid = true;
    // }
    
    // // Generate sparse representation from dense (dense is in descending order)
    // void generateSparse() {
    //     if (!is_dense_valid) return;
        
    //     sparse.clear();
    //     for (int i = 0; i < static_cast<int>(dense.size()); ++i) {
    //         if (dense[i] != 0) {
    //             // Convert from descending order index to actual power
    //             int power = degree - i;
    //             sparse.push_back({dense[i], power});
    //         }
    //     }
        
    //     is_sparse_valid = true;
    // }
    
    // Get maximum degree of the polynomial
    int getDegree() {
        return degree;
    }

    // // Get dense representation
    // std::vector<Rational> getDense() {
    //     if (!is_dense_valid) generateDense();
    //     return dense;
    // }
    
    // Get sparse representation
    // std::vector<PolyTerm> getSparse() {
    //     if (!is_sparse_valid) generateSparse();
    //     return sparse;
    // }
    
    // // Print dense representation
    // void printDense() {
    //     if (!is_dense_valid) generateDense();
        
    //     std::cout << "Dense representation: [";
    //     for (size_t i = 0; i < dense.size(); ++i) {
    //         std::cout << dense[i];
    //         if (i < dense.size() - 1) std::cout << ", ";
    //     }
    //     std::cout << "]" << std::endl;
    // }
    
    // // Print sparse representation
    // void printSparse() {
    //     if (!is_sparse_valid) generateSparse();
        
    //     std::cout << "Sparse representation: [";
    //     for (size_t i = 0; i < sparse.size(); ++i) {
    //         std::cout << "[" << sparse[i].first << ", " << sparse[i].second << "]";
    //         if (i < sparse.size() - 1) std::cout << ", ";
    //     }
    //     std::cout << "]" << std::endl;
    // }
    
    // Print the polynomial in standard mathematical form
    void printPolynomial() {
        // print only the nonzero coefficients in the dense representation
        // int degree = getDegree();
        // for (const auto& coeff : dense) {
        //     if (coeff != 0) {
        //         std::cout << coeff << " " << "x^" << degree--;
        //         if (degree >= 0) {
        //             std::cout << " + ";
        //         }
        //     }
        //     else {
        //         degree--;
        //     }
            
        // }
        std::cout << std::endl;
        int n = sparse.size();
        
        for(int i = 0; i < n; i++) {
            std::cout << sparse[i].coeff << "x^" << sparse[i].exp;
            if(i < n - 1) std::cout<< " + ";
        }
        std::cout << std::endl;



        // if (!is_sparse_valid) generateSparse();
        
        // if (sparse.empty()) {
        //     std::cout << "0" << std::endl;
        //     return;
        // }
        
        // std::cout << "Polynomial: ";
        // bool first = true;
        
        // for (const auto& term : sparse) {
        //     double coeff = term.first;
        //     int power = term.second;
            
        //     // Handle sign
        //     if (!first) {
        //         std::cout << (coeff >= 0 ? " + " : " - ");
        //         coeff = std::fabs(coeff);
        //     } else if (coeff < 0) {
        //         std::cout << "-";
        //         coeff = std::fabs(coeff);
        //     }
            
        //     // Handle coefficient
        //     if (power == 0 || coeff != 1) {
        //         std::cout << coeff;
        //     }
            
        //     // Handle variable and power
        //     if (power > 0) {
        //         std::cout << "x";
        //         if (power > 1) {
        //             std::cout << "^" << power;
        //         }
        //     }
            
        //     first = false;
        // }
        // std::cout << std::endl;
    }
    
    void clear() {
        dense.clear();
        sparse.clear();
        is_dense_valid = false;
        is_sparse_valid = false;
        degree = 0;
    }

    bool isZero() const {
        if(is_dense_valid) {
            for(const auto& coeff : dense) {
                if(coeff != Rational(0)) return false;
            }
        }
        else {
            for(const auto& term : sparse) {
                if(term.coeff != Rational(0)) return false;
            }
        }
        return true;
    }

    //***UTILS***

    //*Sorts them in descending order (greatest to smallest exponent)
    void order_poly() {
        if(is_ordered) return;

        std::sort(sparse.begin(), sparse.end(), 
            [](const PolyTerm& a, const PolyTerm& b) {
                return a.exp > b.exp;
            });

        is_ordered = true;
    }

    //***OSTREAM AND ISTREAM***

    Polynomial operator=(const Polynomial& other) {
        degree = other.degree;
        dense = other.dense;
        sparse = other.sparse;
        is_dense_valid = other.is_dense_valid;
        is_ordered = other.is_ordered;
        is_rational = other.is_rational;
        is_sparse_valid = other.is_sparse_valid;
        return *this;
    }

    Polynomial operator=(std::string str) {
        if(str.find('/') != std::string::npos) is_rational = true;

        std::vector<std::string> tokens;
        std::stringstream ss(str);
        std::string token;
        
        while (std::getline(ss, token, ' ')) {
            tokens.push_back(token);
        }

        PolyTerm term;
        std::string::size_type num_index;
        int num, den;
        int n = tokens.size();
        // for (const std::string& token : tokens) {
        //     std::cout << "Token: " << token << "\n";
        // }
        if(n % 2 == 1) throw std::invalid_argument("There must be one coefficient per each exponent");

        for(int i = 0; i < n; i += 2) {
            num_index = tokens[i].find('/');
            
            //*This part could be handled by the operator= of a PolyTerm
            if(is_rational) {
                //*Rational number
                if(num_index != std::string::npos) {
                    num = std::stoi(tokens[i].substr(0, num_index));
                    den = std::stoi(tokens[i].substr(num_index + 1));
                    // std::cout << "Coefficient: " << tokens[i] << "\n";
                }
                else {
                    num = std::stoi(tokens[i].substr(0));
                    den = 1;
                }
            }
            else {
                //*Integer
                num = std::stoi(tokens[i]);
                den = 1;
            }
            // std::cout << "Checkpoint 1. Num: " << num << ", den: " << den << "\n";
            Rational coeff(num, den);
            // std::cout << "Final coefficient: " << coeff << "\n";
            term.coeff = coeff;
            term.exp = std::stoi(tokens[i + 1]);
            sparse.push_back(term);
        }

        order_poly();
        dense = std::vector<Rational>(degree);
        degree = sparse[0].exp;  // The first term is the one with the greatest exponent
        //std::cout << "Degree: " << degree << " "<< sparse.size() << "\n";

        // Generate dense representation from sparse
        int deg = degree;
        int i = 0;
        while (deg != -1){
            if (deg == sparse[i].exp){
                dense.push_back(sparse[i].coeff);
                i++;
            }
            else {
                dense.push_back(Rational(0));
            }
            deg--;
        }
        is_dense_valid = true;
        return *this;
    }

    Polynomial update_sparse(){
        sparse.clear();
        int n = dense.size();
        for(int i = 0; i < n; i++) {
            if(dense[i] != Rational(0)) {
                PolyTerm term;
                term.coeff = dense[i];
                term.exp = n - 1 - i;  // Convert index to exponent
                sparse.push_back(term);
            }
        }
        return *this;
    }

    friend std::istream& operator>>(std::istream& is, Polynomial& poly) {
        std::string line;
        std::getline(is, line);
        if (!line.empty()) {
            poly = line;
        }
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {

        if(poly.is_dense_valid) {
            os << "Dense representation: ";
            for (const auto& coeff : poly.dense) {
                os << coeff << " ";
            }
            os << "\n";
        }
        else{
            int n = poly.sparse.size();

            for(int i = 0; i < n; i++) {
                os << poly.sparse[i];
                if(i < n - 1) os << " + ";
            }
        }
        return os;
    }

    //***COMPARISON OPERATIONS***

    // std::istream& operator>>(std::istream& is, const Polynomial& other) {

    // }

    //***ARITHMETIC OPERATIONS***

    Polynomial multiply_by_single_term_poly(const PolyTerm& singleTerm) {
        this->order_poly();
        if((singleTerm.coeff == 1) && (singleTerm.exp == 0)) return *this;

        int n = this->sparse.size();
        Polynomial prod;
        PolyTerm prodTerm;

        for(int i = 0; i < n; i++) {
            prodTerm = this->sparse[i] * singleTerm;
            prod.sparse.push_back(prodTerm);
        }
        prod.is_ordered = true;
        return prod;
    }

    Polynomial multiply_by_single_term_poly(const Polynomial& singleTerm) {
        if(singleTerm.sparse.size() != 1) throw std::invalid_argument("Polynomial is not a single-term polynomial; has " + std::to_string(singleTerm.sparse.size()) + " non-zero terms");

        return this->multiply_by_single_term_poly(singleTerm.sparse[0]);
    }

    Polynomial operator+(const Polynomial& other) const {
        int j = 0, i = 0, this_size = sparse.size(), other_size = other.sparse.size();
        Polynomial result;
        PolyTerm newTerm;

        while((i < this_size) && (j < other_size))
        {
            // std::cout << sparse[i].exp << " " << other.sparse[j].exp << "\n";
            if(sparse[i].exp > other.sparse[j].exp) {
                result.sparse.push_back(sparse[i]);
                i++;
            }
            else if (sparse[i].exp == other.sparse[j].exp) {
                newTerm.coeff = sparse[i].coeff + other.sparse[j].coeff;
                newTerm.exp = sparse[i].exp;
                result.sparse.push_back(newTerm);
                i++;
                j++;
            }
            else if (sparse[i].exp < other.sparse[j].exp){
                result.sparse.push_back(other.sparse[j]);
                j++;
            }
            // std::cout << result << "\n";
        }

        //*Include the trailing polynomial terms that were not included because
        //*one of the two polynomials has been completely traversed over.
        if(i < this_size) {
            while (i < this_size) {
                result.sparse.push_back(sparse[i]);
                i++;
            }
        }
        else if(j < other_size) {
            while (j < other_size) {
                result.sparse.push_back(other.sparse[j]);
                j++;
            }
        }

        return result;
    }

    Polynomial to_integer_poly() {
        //!NOT WORKING
        if(!is_rational) return *this;
        
        // Find the LCM of all denominators
        Integer lcm_den = 1;
        int n = sparse.size();
        
        for(int i = 0; i < n; i++) {
            Integer current_den = sparse[i].coeff.denominador;
            Integer gcd = Integer::binaryEuclidean(lcm_den, current_den);
            lcm_den = (lcm_den * current_den) / gcd;
        }
        
        Polynomial result;
        for(int i = 0; i < n; i++) {
            PolyTerm term = sparse[i];
            Integer factor = lcm_den / term.coeff.denominador;
            // std::cout << "FActor: " << factor << ", " << lcm_den << ", " << term.coeff.getDenominator() << "\n";
            term.coeff = Rational(term.coeff.numerador * factor, 1);
            result.sparse.push_back(term);
        }
        
        result.is_ordered = is_ordered;
        result.is_rational = true;  // It's still rational, just with common denominator
        
        return result;
    }

    //*For integer polynomials
    Integer find_gcd_of_poly_terms() {
        if (sparse.size() < 2) return sparse[0].coeff.numerador;
        
        Integer gcd;
        gcd = Integer::binaryEuclidean(sparse[0].coeff.numerador, sparse[1].coeff.numerador);
        // std::cout << "GCD of " << sparse[0].coeff.getNumerator() << ", " << sparse[1].coeff.getNumerator() << " is " << gcd << ", " << sparse.size() << "\n";
        for(int i = 2; i < (int)sparse.size(); i++) {
            // std::cout << "GCD: " << gcd << "\n";
            gcd = Integer::binaryEuclidean(gcd, sparse[i].coeff.numerador);
        }

        return gcd;
    }

    Integer find_lcm_of_poly_terms() {
        if (sparse.size() < 2) return sparse[0].coeff.denominador;
        
        Integer lcm = sparse[0].coeff.denominador;
        for(int i = 1; i < (int)sparse.size(); i++) {
            Integer current_den = sparse[i].coeff.denominador;
            Integer gcd = Integer::binaryEuclidean(lcm, current_den);
            lcm = (lcm * current_den) / gcd;
        }

        return lcm;
    }

    Polynomial operator/(const Polynomial& other) {
        Polynomial u = *this;
        Polynomial r = u;
        Polynomial q;
        q.dense = std::vector<Rational>(degree - other.degree + 1);
        std::cout << q.dense.size() << " VS " << degree - other.degree << "\n";
        std::cout.flush();

        for(int i = 0; i <= u.degree - other.degree; i++){
            q.dense[i] = r.dense[i] / other.dense[0];
            for(int j = 0; j <= other.degree ; j++){
                r.dense[i + j] = r.dense[i+j] - (q.dense[i] * other.dense[j]); 
            }
        }
        q.update_sparse();
        r.update_sparse();
        return q;
    }

    std::pair<Polynomial, Polynomial> divide_by(const Polynomial& divisor) const {
        Polynomial u = *this;
        Polynomial r, q;
        r = u;
        std::string q_str = "0 " + std::to_string(u.degree - divisor.degree);
        q = q_str;

        for(int i = 0; i <= u.degree - divisor.degree; i++){
            q.dense[i] = r.dense[i] / divisor.dense[0];
            for(int j = 0; j <= divisor.degree ; j++){
                r.dense[i + j] = r.dense[i+j] - (q.dense[i] * divisor.dense[j]); 
            }
        }
        q.update_sparse();
        r.update_sparse();
        return {q, r};
    }

    Polynomial pseudoquotient(Polynomial u, Polynomial v) {
        Integer beta = u.find_lcm_of_poly_terms();
        Integer gamma = v.find_gcd_of_poly_terms();
        PolyTerm term1, term2;
        term1.coeff = Rational(beta, 1);
        term1.exp = 0;
        term2.coeff = Rational(gamma, 1);
        term2.exp = 0;

        Polynomial u_prime = u.multiply_by_single_term_poly(term1);
        Polynomial v_prime = v.multiply_by_single_term_poly(term2);

        Integer alpha = v_prime.sparse[0].coeff.denominador^Integer(u.getDegree() - v.getDegree() + 1);
        std::cout << "Alpha: " << alpha << "\n";

        PolyTerm term3;
        term3.coeff = Rational(alpha, 1);
        term3.exp = 0;

        Polynomial u_prime_scaled = u_prime.multiply_by_single_term_poly(term3);
        Polynomial q = u_prime_scaled / v_prime;

        PolyTerm term4;
        term4.coeff = Rational(gamma, beta * alpha);
        term4.exp = 0;

        Polynomial q_scaled = q.multiply_by_single_term_poly(term4);
        return q_scaled;
    }   

    Polynomial pseudoremainder(Polynomial u, Polynomial v) {
        Integer beta = u.find_lcm_of_poly_terms();
        Integer gamma = v.find_gcd_of_poly_terms();
        PolyTerm term1, term2;
        term1.coeff = Rational(beta, 1);
        term1.exp = 0;
        term2.coeff = Rational(gamma, 1);
        term2.exp = 0;

        Polynomial u_prime = u.multiply_by_single_term_poly(term1);
        Polynomial v_prime = v.multiply_by_single_term_poly(term2);

        Integer alpha = v_prime.sparse[0].coeff.denominador^Integer(u.getDegree() - v.getDegree() + 1);
        std::cout << "Alpha: " << alpha << "\n";

        PolyTerm term3;
        term3.coeff = Rational(alpha, 1);
        term3.exp = 0;

        Polynomial u_prime_scaled = u_prime.multiply_by_single_term_poly(term3);
        Polynomial r = u_prime_scaled.divide_by(v_prime).second;

        return r;
    } 

    Polynomial primitivePolyGCD(Polynomial u, Polynomial v) {

        Integer u_content = u.find_gcd_of_poly_terms();
        Integer v_content = v.find_gcd_of_poly_terms();

        PolyTerm term1, term2;
        term1.coeff = Rational(1, u_content);
        term1.exp = 0;
        term2.coeff = Rational(1, v_content);
        term2.exp = 0;

        Polynomial u_primitive = u.multiply_by_single_term_poly(term1);
        Polynomial v_primitive = v.multiply_by_single_term_poly(term2);

        Integer c = Integer::binaryEuclidean(u_content, v_content);

        while (v.getDegree() > 0) {
            Polynomial r = pseudoremainder(u_primitive ,v_primitive);
            Integer r_content = r.find_gcd_of_poly_terms();
            PolyTerm term3;
            term3.coeff = Rational(1, r_content);
            term3.exp = 0;
            Polynomial r_primitive = r.multiply_by_single_term_poly(term3);
            u_primitive = v_primitive;
            u = v;
            v = r_primitive;
        }
        if (v_primitive.isZero()) {
            PolyTerm term4;
            term4.coeff = Rational(c, 1);
            term4.exp = 0;
            return u.multiply_by_single_term_poly(term4);
        }
        else {
            Polynomial c_pol;
            c_pol.dense.push_back(c);
            c_pol.update_sparse();
            return c_pol;
        }
    }
};

int main2() {
    Rational rational(1, 2);
    // std::cout << rational + (rational / 6) << "\n";
    
    Polynomial poly, singleTerm;

    std::cin >> poly;
    std::cin >> singleTerm;
    std::cout << poly << "\n";
    std::cout << singleTerm << "\n";
    std::cout << poly.multiply_by_single_term_poly(singleTerm) << "\n";

    // PolyTerm term1, term2;
    // term1.coeff = Rational(-1, 2);
    // term2.coeff = Rational(1, 3);
    // term1.exp = Integer(2);
    // term2.exp = Integer(2);
    // std::cout << term1 << "\n";
    // std::cout << term2 << "\n";
    // std::cout << "Sum of terms: " << (term1 + term2) << "\n";

    Polynomial poly1, poly2;
    std::cin >> poly1;
    std::cout << poly1 << "\n";
    std::cin >> poly2;
    std::cout << poly2 << "\n";
    std::cout << poly1 + poly2 << "\n";
    std::cout << poly2.find_gcd_of_poly_terms() << "\n";
    std::cout << poly1.to_integer_poly() << "\n";
    
//     // Test examples
//     std::vector<std::string> test_cases = {
//         "3x^4 + 2x^2 - 1",
//         "x^3 - 2x + 5",
//         "2x^5 - x^4 + 3x^2 - 7x + 1",
//         "-x^2 + 4x - 3",
//         "5",
//         "x",
//         "-x^3"
//     };
    
//     for (const std::string& test : test_cases) {
//         std::cout << "\n" << std::string(50, '=') << std::endl;
//         std::cout << "Input: \"" << test << "\"" << std::endl;
//         std::cout << std::string(50, '=') << std::endl;
        
//         poly.parseFromString(test);
//         poly.printPolynomial();
//         poly.printDense();
//         poly.printSparse();
//     }
    
//     // Interactive mode
//     std::cout << "\n" << std::string(50, '=') << std::endl;
//     std::cout << "Interactive Mode (enter 'quit' to exit)" << std::endl;
//     std::cout << std::string(50, '=') << std::endl;
    
//     std::string input;
//     while (true) {
//         std::cout << "\nEnter a polynomial: ";
//         std::getline(std::cin, input);
        
//         if (input == "quit" || input == "exit") {
//             break;
//         }
        
//         if (input.empty()) {
//             continue;
//         }
        
//         try {
//             poly.parseFromString(input);
//             poly.printPolynomial();
//             poly.printDense();
//             poly.printSparse();
//         } catch (const std::exception& e) {
//             std::cout << "Error parsing polynomial: " << e.what() << std::endl;
//         }
//     }
    
    return 0;
}


int main(){
    Polynomial poly1, poly2;
    poly1 = "1 4 -3 3 5 2 -1 1 2 0";
    poly2 = "1 2 1 1 -1 0";

    std::cout << "\nPOLYNOMIAL DIVISION\n";
    // poly1 = "1/2 4 1/6 0";
    // poly2 = "1/4 1 -1/3 0";

    // poly1 = "1/3 3 -2/3 2 -5/3 1 10/3 0";
    // poly2 = "1/3 1 -1 0";
    Polynomial poly3 = poly1 / poly2;
    poly1.printPolynomial();
    std::cout << "/" << std::endl;
    poly2.printPolynomial();
    poly3.printPolynomial();
    return 0;
}