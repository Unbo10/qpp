#ifndef INTEGER_H
#define INTEGER_H

#include <iostream>
#include "../utils/List.cpp"
#include "Number.cpp"

using namespace std;

class Integer: public Number
{
    private:
        static const int DEFAULT_BASE = 10;
        static const int digitsByBlock = 5;

        List<int> digitsInteger;
        int BASE;
        bool sign;

        static int max(int x, int y)
        {
            if(x < y) return y;
            return x;
        }

        static long long min(long long x, long long y)
        {
            if(x < y) return x;
            return y;
        }

        void forceAdd(long long newDigit)
        {
            if(newDigit == 0) digitsInteger.add(0);
            while(0 < newDigit)
            {
                int res = newDigit%BASE;
                newDigit /= BASE;
                digitsInteger.add(res);
                // std::cout << "Res: " << res << " new digit: " << newDigit << " base: " << BASE << "\n";
            }
            // std::cout << "List of digits: " << digitsInteger << "\n";
        }

        // O(log_10 (n))
        static int digits(long long x)
        {
            int c = 0;
            while(x != 0)
            {
                x /= 10;
                c++;
            }
            return c;
        }

        static void cleanDigits(Integer& num)
        {
            int length = num.numberSize();
            while(0 < length && num.digitAt(length-1) == 0)
                length--;
            if(length == num.numberSize()) return;
            List<int> clean(length);
            for(int i = 0; i < length; i++)
                clean.add(num.digitAt(i));

            num.digitsInteger = clean;
        }

        Integer highPart(int index) const
        {
            Integer toR;
            for(int i = digitsInteger.size() - index -1; i < digitsInteger.size(); i++)
                toR.addDigit(digitsInteger[i]);

            Integer::cleanDigits(toR);
            return toR;
        }

        Integer lowPart(int index) const
        {
            Integer toR;
            for(int i = 0; i < index; i++)
                toR.digitsInteger.add(digitsInteger[i]);
            Integer::cleanDigits(toR);
            return toR;
        }

        static Integer karatsuba(const Integer& num1, const Integer& num2)
        {
            if(num1.numberSize() <= 15 || num2.numberSize() <= 15)
                return conventionalForm(num1, num2);

            //*Fill with zeros 

            int upperSize = Integer::max(num1.numberSize(), num2.numberSize())/2;

            // std::cout << num1.digitsInteger << "\n";

            Integer upper1 = num1.highPart(upperSize);
            Integer lower1 = num1.lowPart(upperSize);
            Integer upper2 = num2.highPart(upperSize);
            Integer lower2 = num2.lowPart(upperSize);

            // std::cout << "A\n";
            Integer U = karatsuba(upper1, upper2);
            // std::cout << "A\n";
            Integer V = karatsuba(lower1, lower2);
            Integer W = karatsuba(upper1 + lower1, upper2 + lower2) -U -V;
            return multiplyByBase(U, 2*upperSize) + multiplyByBase(W, upperSize) + V;
        }

        static Integer conventionalForm(const Integer& num1, const Integer& num2)
        {
            Integer product;
            product.BASE = num1.BASE;
            int totalSize = num1.numberSize() + num2.numberSize();

            for(int i = 0; i < totalSize; i++)
                product.digitsInteger.add(0);

            for(int j = 0; j < num2.numberSize(); j++)
            {
                if(num2.digitAt(j) == 0) continue;
                long long carry = 0;
                for(int i = 0; i < num1.numberSize(); i++)
                {
                    long long realSum = carry + 1LL * num1.digitAt(i)*num2.digitAt(j) + product.digitAt(i+j);
                    product.digitsInteger.replace(realSum%num1.BASE, i+j);
                    carry = realSum/num1.BASE;
                }
                product.digitsInteger.replace(carry, num1.numberSize()+j);
            }
            std::cout << "Multiplication " << num1 << " * " << num2 << " result: " << product << "\n";
            Integer::cleanDigits(product);
            return product;
        }

        static Integer multiplyByBase(const Integer& num, int times)
        {
            Integer result;
            for(int i = 0; i < times; i++)
                result.digitsInteger.add(0);
            result.addDigit(num);
            return result;
        }

    public:
        Integer() :BASE(DEFAULT_BASE), sign(true) {}
        Integer(long long x): BASE(DEFAULT_BASE), sign(true)
        {
            sign = x >= 0;
            addDigit(sign? x: -x);
            Integer::cleanDigits(*this);
        }
        Integer(const Integer& toC) : digitsInteger(toC.digitsInteger), sign(toC.sign), BASE(toC.BASE) {}
        //~Integer() {}

        void setSize(int newSize)
        {
            List<int> newList(newSize);
            for(int i = 0; i < newSize; i++)
                newList.add(digitAt(i));

            digitsInteger = newList;
        }

        void addDigit(long long newDigit)
        {
            if(newDigit <= 0) return; //!Correcting this may help
            forceAdd(newDigit);
        }

        void addDigit(const Integer& newDigit)
        {
            if(BASE != newDigit.BASE)
                throw std::invalid_argument("Not implemented digits in diferents bases");
            
            for(int x: newDigit.digitsInteger)
                digitsInteger.add(x);
            
        }

        int digitAt(int index) const
        {
            try{
                return digitsInteger[index];
            }catch(const std::invalid_argument& e)
            {
                return 0;
            }
        }

        int numberSize() const
        {
            return digitsInteger.size();
        }

        int getBase()
        {
            return BASE;
        }

        // operaciones entre numeros
        friend Integer operator-(const Integer& num)
        {
            Integer toR(num);
            toR.sign = !toR.sign;
            return toR;
        }

        friend Integer operator+(Integer first, Integer second)
        {
            if (first.sign ^ second.sign) 
            {
                if(first.sign == true)
                    return first - (-second);
                return second - (-first);
            }
                

            if (first.BASE != second.BASE) 
                throw std::invalid_argument("Not defined sum of integers in different Bases yet");

            Integer sumOfIntegers;
            int length = max(first.numberSize(), second.numberSize());
            int c = 0;
            long long res = 0;

            while (c < length || res != 0)
            {
                res += first.digitAt(c) + second.digitAt(c);
                sumOfIntegers.addDigit(res % first.BASE);
                res /= first.BASE;
                c++;
            }
            sumOfIntegers.sign = first.sign;
            Integer::cleanDigits(sumOfIntegers);
            return sumOfIntegers;
        }

        friend Integer operator-(const Integer& num1, const Integer& num2)
        {
            if (num1.BASE != num2.BASE) 
                throw std::invalid_argument("Not defined difference of integers in different Bases yet");

            if(num1 < num2)
                return -(num2 - num1);
            if(!num2.sign)
                return num1 + (-num2);

            bool carry = 0;
            int maxSize = Integer::max(num1.numberSize(), num2.numberSize());
            Integer tR;
            tR.BASE = num1.BASE;

            for(int i = 0; i < maxSize; i++)
            {
                int kResult = num1.digitAt(i) - num2.digitAt(i) - carry;
                if(kResult < 0)
                {
                    carry = 1;
                    kResult += num1.BASE;
                }
                else carry = 0;
                tR.forceAdd(kResult);
            }

            Integer::cleanDigits(tR);
            return tR;
        }

        friend Integer operator*(const Integer& num1, const Integer& num2)
        {
            if(num1 == 0 || num2 == 0) return Integer();
            Integer mult = Integer::karatsuba(num1, num2);
            mult.sign = !(num1.sign ^ num2.sign);
            Integer::cleanDigits(mult);
            return mult;
        }

        friend Integer operator/(const Integer& num1, const Integer& num2)
        {
            if (num2 == Integer(0))
                throw std::invalid_argument("Math error: Division by zero");
            if (num1.BASE != num2.BASE)
                throw std::invalid_argument("Different bases not supported");
            if (num1.numberSize() < num2.numberSize())
                return Integer(0);
            if(num2 == 1) return num1;
            int top = num2.digitAt(num2.numberSize() - 1);
            std::cout << "Top: " << top << "\n";
            int scaleFactor = (top >= num2.BASE/2) 
                        ? 1 
                        : num2.BASE/(top + 1);
            //*This multiplication needs to be done always because the dividend's size must be m + n + 1, i.e., must increase by 1, which is not the case for the divisor
            Integer dividend = scaleFactor * num1;
            Integer divisor = (scaleFactor == 1 ? num2 : scaleFactor * num2);
            // if (dividend.digitAt(0) == Integer(0)) {
            //     if (dividend.numberSize() - divisor.numberSize() > num1.numberSize() - num2.numberSize()) {
            //         dividend.digitsInteger.pop(dividend.numberSize() - 1);
            //     }
            // }
            //!Somehow, we need to remove a zero from the dividend if it enters the cycle. The problem is that we need to drop the zero from the first digit of the number, not drop the first digit if it's zero
            //!Representation in base 100,000 is not clear when printing.
            
            //*This block works correctly
            int m = dividend.numberSize() - divisor.numberSize();
            Integer U; //*u'
            U.digitsInteger = List<int>(divisor.numberSize() + 1); //*Changed the size
            cout << "m: " << m << " dividend size: " << dividend.numberSize() << " divisor size: " << divisor.numberSize() << "\n";
            for(int i = dividend.numberSize(); i >= m; i--)
            {
                U.digitsInteger.add(dividend.digitAt(i));
            }

            cout << "Initial û: " << U << "\n";

            Integer quant;
            quant.BASE = num1.BASE;
            quant.setSize(m+1);
            
            std::cout << "Scale factor: " << scaleFactor << "\n";
            std::cout << "Normalized u: " << dividend << " original u: " << num1 << "\n";
            std::cout << "Normalized v: " << divisor << " original v: " << num2 << "\n";

            for(int j = m; 0 <= j; --j)
            {
                long long q;
                if (U.digitAt(U.numberSize() - 1) == divisor.digitAt(divisor.numberSize())) {
                    q = num1.BASE - 1;
                }
                else {
                    int help = U.numberSize() - 1;
                    long long high = U.digitAt(help);
                    long long low = U.digitAt(help - 1);
                    q = (1LL * high * num2.BASE + low) / divisor.digitAt(divisor.numberSize() - 1);
                }

                Integer multiplyTest = q*divisor;
                std::cout << "w: " << multiplyTest << "\n";
                std::cout << "û: " << U << "\n";
                while(U < multiplyTest)
                {
                    q--;
                    multiplyTest = multiplyTest - divisor;
                }
                Integer remainder = U - multiplyTest;
                if (0 < j){
                    Integer dj = dividend.digitAt(j - 1);
                    U = Integer::multiplyByBase(remainder, 1) + dividend.digitAt(j - 1);
                    cout << "--- HERE IS THE PROBLEM --- \n" << "Remainder * b: " << Integer::multiplyByBase(remainder, 1) << "\n" << "Dividend_{j - 1}: " << dividend.digitAt(j - 1) << "\n" << "U: " << U << "\n";
                    cout << "First addend size: " << Integer::multiplyByBase(remainder, 1).numberSize() << "\n";
                    cout << "Second addend size: " << dj << "\n";
                    cout << "------\n";
                }
                
                quant.digitsInteger.replace(q, j);
            }
            Integer::cleanDigits(quant);
            return quant;
        }

        friend Integer operator%(const Integer& num1, const Integer& num2)
        {
            return num1 - (num1/num2)*num2;
        }

        friend Integer operator^(Integer base, Integer exp)
        {
            if (exp < Integer(0))
                throw std::invalid_argument("Exponent must be non-negative");

            Integer result = 1;
            while (exp > 0)
            {
                if (exp.digitsInteger[0]%2  == 1)
                    result = result * base;

                base = base * base;
                exp = exp / 2;
            }

            return result;
        }

        static Integer max(const Integer& n1, const Integer& n2)
        {
            if(n1 < n2) return n2;
            return n1;
        }

        static Integer min(const Integer& n1, const Integer& n2)
        {
            if(n1 < n2) return n1;
            return n2;
        }

        static Integer abs(const Integer& r)
        {
            if(r.sign) return r;
            return -r;
        }

        static List<Integer> extendEuclidean(const Integer& num1, const Integer& num2)
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

        static Integer binaryEcludian(Integer n1, Integer n2)
        {
            if(!n1.sign)
                n1.sign = true;
            if(!n2.sign)
                n2.sign = true;
            if(n1 == 0 || n2 == 0)
                return max(n1, n2);

            Integer gcd = 1;
            while(n1.digitAt(0)%2 == 0 && n2.digitAt(0)%2 == 0)
            {
                n1 = n1/2;
                n2 = n2/2;
                gcd = 2*gcd;
            }

            while(0 < n1 && n2 != 1)
            {
                while(n1.digitAt(0)%2 == 0) n1 = n1/2;
                while(n2.digitAt(0)%2 == 0) n2 = n2/2;
                Integer t = Integer::abs(n1 - n2);
                n2 = Integer::min(n1, n2);
                n1 = t;
            }
            return gcd*n2;
        }


        friend std::ostream& operator<<(std::ostream& os, const Integer& number)
        {
            if(number.digitsInteger.size() == 0) return os << '0';

            if(!number.sign) os << "-";

            // cout << "Digits integer: " << number.digitsInteger << "\n";
            
            //*For now, this will be documented, and the representation of numbers will be the list of their digits inverted
            // for(int i = number.digitsInteger.size() - 1; i >= 0; i--)
            // {
            //     os << number.digitAt(i);
            //     //!It shouldn't convert to base 10 when printing unless it is indicated to do so.
            //     //!The code below will only work for base 100,000.
            //     // for(int j = 0; j < Integer::digitsByBlock- digits(number.digitAt(i)); j++)
            //     //     os << '0';
            // }  

            os << "[";
            for(int i = number.digitsInteger.size() - 1; i > 0; i--) {
                os << number.digitsInteger[i] << ", ";
            }
            os << number.digitsInteger[0] << "]";

            return os /*<< " (based-)" << number.BASE*/;
        }

        // operadora de asignacion
        void operator+=(const Integer& other)
        {
            *this = *this + other;
        }

        Integer& operator=(long long number)
        {
            digitsInteger.clear();
            sign = number >= 0;
            this->addDigit((sign)? number : -number);
            return *this;
        }

        Integer& operator=(const Integer& numb)
        {
            if(this == &numb) return *this;
            digitsInteger = numb.digitsInteger;
            sign = numb.sign;
            BASE = numb.BASE;
            return *this;
        }

        // operadores de comparacion
        friend bool operator<(const Integer& num1, const Integer& num2)
        {
            if(num2.sign == 0 && num1.sign == 1) return false;
            else if(num2.sign == 1 && num1.sign == 0) return true;
            else if(num2.sign == 1 && num1.sign == 1)
            {
                int length = Integer::max(num2.numberSize(), num1.numberSize());
                for(int i = length - 1; 0 <= i; i--)
                {
                    if(num1.digitAt(i) < num2.digitAt(i))
                        return true;
                    else if(num2.digitAt(i) < num1.digitAt(i))
                        return false;
                }

                return false;
            }

            return -num2 < -num1;
        }  

        friend bool operator>(const Integer& num1, const Integer& num2)
        {
            return num2 < num1;
        }

        friend bool operator==(const Integer& num1, const Integer& num2)
        {
            return num1.sign == num2.sign &&
                   num1.digitsInteger == num2.digitsInteger &&
                   num1.BASE == num2.BASE;
        }

        friend bool operator!=(const Integer& num1, const Integer& num2)
        {
            return !(num1 == num2);
        }

        friend bool operator<=(Integer& num1, Integer& num2)
        {
            return num1 < num2 || num1 == num2;
        }

        friend bool operator>(Integer& num1, Integer& num2)
        {
            return  num2 < num1;
        }

        friend bool operator>=(Integer& num1, Integer& num2)
        {
            return num1 > num2 || num1 == num2;
        }

        List<int> getList()
        {
            return List<int>(digitsInteger);
        }
};

#endif