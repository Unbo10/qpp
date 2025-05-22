#ifndef INTEGER_H
#define INTEGER_H

#include <iostream>
#include "../utils/List.cpp"
#include "Number.cpp"
#include "../utils/Comparable.cpp"

class Integer: public Number, public Comparable<Integer>
{
    private:
        static const int DEFAULT_BASE = 100000;
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
            }
        }

        // O(log_10 (n))
        static int digits(long long x)
        {
            int c = 1;
            while(x != 0)
            {
                x /= 10;
                c++;
            }
            return c;
        }

        static void cleanDigits(Integer& num)
        {
            int length = num.digitsInteger.getCapacity();
            while(0 < length && num.digitAt(length-1) == 0)
                length--;
            if(length == num.numberSize()) return;
            List<int> clean(length);
            for(int i = 0; i < length; i++)
                clean.add(num.digitAt(i));

            num.digitsInteger = clean;
        }

        Integer partHigh(int index) const
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
            int upperSize = Integer::max(num1.numberSize(), num2.numberSize())/2;

            Integer uper1 = num1.partHigh(upperSize);
            Integer lower1 = num1.lowPart(upperSize);
            Integer upper2 = num2.partHigh(upperSize);
            Integer lower2 = num2.lowPart(upperSize);

            Integer U = karatsuba(uper1, upper2);
            Integer V = karatsuba(lower1, lower2);
            Integer W = karatsuba(uper1 + lower1, upper2 + lower2) -U -V;
            return multiplyByBase(V, 2*upperSize) + multiplyByBase(W, upperSize) + U;
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

        static void changeBase(int newBase, Integer& number)
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

        void setSize(int newSize)
        {
            List<int> newList(newSize);
            for(int i = 0; i < newSize; i++)
                newList.add(digitAt(i));

            digitsInteger = newList;
        }

        void addDigit(long long newDigit)
        {
            if(newDigit <= 0) return;
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
            if (first.BASE != second.BASE) 
                throw std::invalid_argument("Not defined sum of integers in different Bases yet");
            
            if (first.sign ^ second.sign) 
            {
                if(first.sign == true)
                    return first - (-second);
                return second - (-first);
            }

            Integer sumOfIntegers;
            sumOfIntegers.BASE = first.BASE;
            int length = max(first.numberSize(), second.numberSize());
            int c = 0;
            long long res = 0;

            while (c < length || res != 0)
            {
                res += first.digitAt(c) + second.digitAt(c);
                sumOfIntegers.forceAdd(res % first.BASE);
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
            if(num1.BASE != num2.BASE) throw std::invalid_argument("Error");
            if(num1 == 0 || num2 == 0) return Integer();
            Integer mult = Integer::karatsuba(num1, num2);
            mult.sign = !(num1.sign ^ num2.sign);
            mult.BASE= num1.BASE;
            Integer::cleanDigits(mult);
            return mult;
        }

        /*friend Integer operator*(long long num1, const Integer& num2)
        {
            Integer help;
            help.BASE = num2.BASE;
            help.forceAdd(num1);
            std::cout << help.getBase() << "  " << help << std::endl;
            return help*num2;
        }*/

        friend Integer operator/(const Integer& num1, const Integer& num2)
        {
            if (num2 == Integer(0))
                throw std::invalid_argument("Math error: Division by zero");
            if (num1.BASE != num2.BASE)
                throw std::invalid_argument("Different bases not supported");
            if (num1.numberSize() < num2.numberSize())
                return Integer(0);
            if(num2 == 1) return num1;

            if(num1 < 0 && num2 < 0)
                return 1+(-num1/(-num2));

            if(!num2.sign)
                return -(num1/(-num2));
            if(!num1.sign)
                return -((-num1)/num2 + 1);

            int top = num2.digitAt(num2.numberSize() - 1);
            Integer scaleFactor;
            scaleFactor.BASE = num1.BASE;
            scaleFactor  = (top >= num2.BASE/2) 
                        ? 1 
                        : num2.BASE/(top + 1);
            Integer dividend = (scaleFactor == 1 ? num1 : scaleFactor * num1);
            Integer divisor = (scaleFactor == 1 ? num2 : scaleFactor * num2);

            // toda esta parte de U está resvisada y funciona correctamente
            int m = dividend.numberSize() - divisor.numberSize();
            Integer U;
            U.BASE = num1.BASE;
            U.digitsInteger = List<int>(m+1);
            for(int i = m; i < dividend.numberSize(); i++)
            {
                U.digitsInteger.add(dividend.digitAt(i));
            }
            

            //corregido un for que no se usa
            Integer quant;
            quant.BASE = num1.BASE;
            quant.setSize(m+1);

            for(int j = m; 0 <= j; --j)
            {
                int help = U.numberSize() - 1;
                long long high = U.digitAt(help);
                long long low = U.digitAt(help - 1);
                long long q = (1LL * high * num2.BASE + low) / divisor.digitAt(divisor.numberSize() - 1);
                
                if(q >= num1.BASE) q = num1.BASE - 1;
                
                Integer multiplyTest = q*divisor;
                while(U < multiplyTest)
                {
                    q--;
                    multiplyTest = multiplyTest - divisor;
                }
                Integer remainer = U - multiplyTest;
                if(0 < j)
                {
                    int newDig = dividend.digitAt(j - 1);
                    if(newDig == 0)
                        U = Integer::multiplyByBase(remainer, 2);
                    else U = Integer::multiplyByBase(remainer, 1) + newDig;
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
                std::cout << q << "   " << r << std::endl;
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
            
            os << number.digitAt(number.digitsInteger.size() - 1);
            if(number.BASE != Integer::DEFAULT_BASE)
            {
                for(int i = number.digitsInteger.size() - 2; i >= 0; i--)
                    os << number.digitAt(i);
            }
            else for(int i = number.digitsInteger.size() - 2; i >= 0; i--)
            {
                for(int j = 0; j < Integer::digitsByBlock- digits(number.digitAt(i)); j++)
                    os << '0';
                os << number.digitAt(i);
            }  
            return os /*<< " (based-)" << number.BASE*/;
        }

        friend std::istream& operator>>(std::istream& is, Integer& num)
        {
            long long read;
            is >> read;
            num = read;
            return is;
        }

        // operadora de asignacion
        void operator+=(const Integer& other)
        {
            *this = *this + other;
        }

        Integer& operator=(const Integer& numb)
        {
            if (this == &numb)
            {
                return *this;
            }
            digitsInteger = numb.digitsInteger;
            sign = numb.sign;
            BASE = numb.BASE;
            return *this;
        }

        // operadores de comparacion
        friend bool operator<(int num1, const Integer& num2)
        {
            return Integer(num1) < num2;
        }

        bool operator<(const Integer& num1) const override
        {
            if(sign == 0 && num1.sign == 1) return true;
            else if(sign == 1 && num1.sign == 0) return false;
            else if(sign == 1 && num1.sign == 1)
            {
                int length = Integer::max(this->numberSize(), num1.numberSize());
                for(int i = length - 1; 0 <= i; i--)
                {
                    if(num1.digitAt(i) < this->digitAt(i))
                        return false;
                    else if(this->digitAt(i) < num1.digitAt(i))
                        return true;
                }

                return false;
            }

            return -(*this) < -num1;
        }  

        friend bool operator>(const Integer& num1, const Integer& num2)
        {
            return num2 < num1;
        }

        bool operator==(const Integer& num1) const override
        {
            return num1.sign == sign &&
                    num1.BASE == BASE &&
                   num1.digitsInteger == digitsInteger;
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