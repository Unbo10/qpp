#ifndef INTEGER_H
#define INTEGER_H

#include <iostream>
#include "../utils/List.cpp"
#include "Number.cpp"

//*Changes:
//*Replaced the private max and min methods for max_int and min_int, respectively, for better clarity
//*The overloads for the operations with mixed types has to be done in Rationals to avoid circular imports.

//TODO: Initialize base in Number class
//TODO: Check in binaryEuclidean the replacement of the max and min functions

//? Consider implementing a toString method to improve the erorr messages
class Integer: public Number<Integer> //?Does it also need to inherit from comparable?
{
    private:
        static const int digitsByBlock = 5;

        List<int> digitsInteger;

        // static void changeBase(int newBase, Integer& number);

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

        static int max_int(int x, int y)
        {
            if(x < y) return y;
            return x;
        }

        static int min_int(int y, int x)
        {
            if(x < y) return x;
            return y;
        }

        // O(log_10 (n))
        static int digits(long long x)
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

    public:
        Integer(): Number<Integer>() {}
        Integer(long long x): Number<Integer>()
        {
            sign = x >= 0;
            addDigit(sign? x: -x);
            Integer::cleanDigits(*this);
        }
        Integer(const Integer& toC) : Number<Integer>(toC.sign, toC.BASE), digitsInteger(toC.digitsInteger) {}
        //~Integer() {}
        
        int getBase() const
        {
            return BASE;
        }
        //***OPERATIONS***

        Integer add(const Integer& other) const override
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
            int length = Integer::max_int(numberSize(), other.numberSize());
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

        Integer subtract(const Integer& other) const override
        {
            if((*this) < other)
                return -(other - (*this));
            if(!other.sign)
                return *this + (-other);

            bool carry = 0;
            int maxSize = Integer::max_int(numberSize(), other.numberSize());
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

        Integer subtract(long long int x) const
        {
            return subtract(Integer(x));
        }

        Integer negate() const override
        {
            Integer toR(*(this));
            toR.sign = !toR.sign;
            return toR;
        }

        static Integer karatsuba(const Integer& num1, const Integer& num2)
        {
            if(num1.numberSize() <= 15 || num2.numberSize() <= 15)
                return conventionalForm(num1, num2);
            int upperSize = Integer::max_int(num1.numberSize(), num2.numberSize())/2;

            Integer uper1 = num1.partHigh(upperSize);
            Integer lower1 = num1.lowPart(upperSize);
            Integer upper2 = num2.partHigh(upperSize);
            Integer lower2 = num2.lowPart(upperSize);

            Integer U = karatsuba(uper1, upper2);
            Integer V = karatsuba(lower1, lower2);
            Integer W = karatsuba(uper1 + lower1, upper2 + lower2) -U -V;
            return multiplyByBase(V, 2*upperSize) + multiplyByBase(W, upperSize) + U;
        }

        Integer multiply(const Integer& other) const override
        {
            if(BASE != other.BASE) throw std::invalid_argument("Error");
            if(*this == 0 || other == 0) return Integer();
            Integer mult = Integer::karatsuba(*this, other);
            mult.sign = !(sign ^ other.sign);
            mult.BASE= BASE;
            Integer::cleanDigits(mult);
            return mult;
        }

        Integer divide(const Integer& other) const override
        {
            if (other == 0) throw std::invalid_argument("Division by zero");
            if (BASE != other.BASE) throw std::invalid_argument("Different bases");
            
            // Manejo rápido de casos especiales
            if (numberSize() < other.numberSize()) return 0;
            if (other == 1) return *this;

            if(other == 2)
                return this->divideBy2();

            Integer a = (this->sign) ? *this: -*this;
            const Integer b = (other.sign)? other: -other;

            const int m = a.numberSize() - b.numberSize();
            Integer quant;
            quant.setSize(m + 1);

            Integer currentRemainder;
            for (int j = m; j >= 0; --j) {
                currentRemainder = currentRemainder * BASE + a.digitAt(j);
                
                int q = Integer::estimateQuotient(currentRemainder, b);
                Integer help = b*q;
                while (help > currentRemainder) {
                    q--; help -= b;
                }
                
                currentRemainder = currentRemainder - help;
                quant.digitsInteger.replace(q, j); 
            }

            Integer::cleanDigits(quant);
            return quant;
        }
        
        static int estimateQuotient(const Integer& rem, const Integer& divisor) {
            const int n = divisor.numberSize();
            const long long top = rem.digitAt(n) * rem.BASE + rem.digitAt(n-1);
            return Integer::min_int(top / divisor.digitAt(n-1), rem.BASE-1);
        }

        Integer modulo(const Integer& other) 
        {
            //? Could also be this->add((this->divide(other)).multiply(other).negate());
            return *this - (*this/other)*other;
        }
        
        Integer power(Integer exp) const override
        {
            if (exp < Integer(0))
                throw std::invalid_argument("Exponent must be non-negative");

            Integer base(*this);
            Integer result = 1;
            while (exp > 0)
            {
                if (exp.digitsInteger[0]%2  == 1)
                    result = result * base;

                base = base * base;
                exp = exp.divideBy2();
            }

            return result;
        }

        //***COMPARISONS***

        void assign(const Integer& other) override
        {
            if (this == &other)
            {
                return;
            }
            digitsInteger = other.digitsInteger;
            sign = other.sign;
            BASE = other.BASE;
        }

        bool eq(const Integer& other) const override
        {
            return other.sign == sign &&
                    other.BASE == BASE &&
                    other.digitsInteger == digitsInteger;
        }

        bool lt(const Integer& other) const override
        {
            if(sign == 0 && other.sign == 1) return true;
            else if(sign == 1 && other.sign == 0) return false;
            else if(sign == 1 && other.sign == 1)
            {
                //*This case does take into account when both numbers are equal
                int length = Integer::max_int(this->numberSize(), other.numberSize());
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
                return (-other).lt(-(*this)); //!May be wrong
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

        void changeBase(int newBase, Integer& number)
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

        Integer divideBy2() const {
            Integer result;
            result.sign = this->sign;
            result.setSize(digitsInteger.size());

            int carry = 0;
            for (int i = (int)digitsInteger.size() - 1; i >= 0; --i) {
                long long current = carry * 100000LL + digitsInteger[i];  // base = 10^5
                result.digitsInteger.replace(current / 2, i);
                carry = current % 2;
            }

            Integer::cleanDigits(result);
            return result;
        }

        

        List<int> getList()
        {
            return List(digitsInteger);
        }

        static Integer multiplyByBase(const Integer& num, int times)
        {
            Integer result;
            for(int i = 0; i < times; i++)
                result.digitsInteger.add(0);
            result.addDigit(num);
            return result;
        }
};

#endif