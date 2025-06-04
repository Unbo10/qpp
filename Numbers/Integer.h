#pragma once

#include <iostream>
#include "../utils/List.h"
#include "Number.h"

class Integer: public Number<Integer>
{
    private:
        static const int digitsByBlock = 5;

        List<int> digitsInteger;

        void setSize(int newSize);

        void addDigit(long long newDigit);

        void addDigit(const Integer& newDigit);

        int digitAt(int index) const;

        //*Only to access the index (for now)
        int operator[](int index) const;

        int numberSize() const;

        void forceAdd(long long newDigit);

        static int max_int(int x, int y);

        static int min_int(int y, int x);

        static int digits(long long x);

        static void cleanDigits(Integer& num);

        Integer partHigh(int index) const;

        Integer lowPart(int index) const;

        static Integer conventionalForm(const Integer& num1, const Integer& num2);

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

        //***COMPARISONS***
        bool operator<(const Integer& other) const override;

        friend bool operator<(int int_num1, const Integer& num2);
        
        int getBase() const;

        //***OPERATIONS***

        Integer operator+(const Integer& other) const override;
        
        friend Integer operator+(int num1, const Integer& num2);

        friend Integer operator+(const Integer& num1, int num2);

        Integer operator-(const Integer& other) const override;

        friend Integer operator-(int num1, Integer& num2);

        friend Integer operator-(Integer& num1, int num2);

        Integer operator-() const override;

        static Integer karatsuba(const Integer& num1, const Integer& num2);

        Integer operator*(const Integer& other) const override;

        friend Integer operator*(int num1, const Integer& num2);

        friend Integer operator*(const Integer& num1, int num2);

        Integer operator/(const Integer& other) const override;

        static int estimateQuotient(const Integer& rem, const Integer& divisor);

        friend Integer operator/(int num1, const Integer& num2);

        friend Integer operator/(const Integer& num1, int num2);

        Integer operator%(const Integer& other) const;

        friend Integer operator%(int num1, const Integer& num2);

        friend Integer operator%(const Integer& num1, int num2);
    
        Integer operator^(const Integer& other) const override;

        //***COMPARISONS***

        Integer operator=(const Integer& other) override;

        Integer operator=(const long long num_int);

        bool operator==(const Integer& other) const override;

        friend bool operator==(const int int_num, const Integer& num);

        friend bool operator==(const Integer& num, const int int_num);

        friend bool operator<=(const int int_num, const Integer& num);

        friend bool operator<=(const Integer& num, const int int_num);

        friend bool operator!=(const Integer& num1, const int num2);

        friend bool operator!=(const int num1, const Integer& num2);

        friend bool operator>(const int int_num1, const Integer& num2);

        friend bool operator>(const Integer& num1, const int int_num2);

        friend bool operator>=(const int int_num1, const Integer& num2);

        friend bool operator>=(const Integer& num1, const int int_num2);

        static Integer abs(const Integer& r);

        static List<Integer> extendEuclidean(const Integer& num1, const Integer& num2);

        static Integer binaryEuclidean(Integer n1, Integer n2);

        void changeBase(int newBase, Integer& number);

        friend std::ostream& operator<<(std::ostream& os, const Integer& number);

        friend std::istream& operator>>(std::istream& is, Integer& num);

        Integer divideBy2() const; 
        
        Integer multiplyByDigit(int x) const;
        
        bool isEven() const;

        List<int> getList() const;

        bool getSign() const;

        void setSign(bool sign);

        static Integer multiplyByBase(const Integer& num, int times);

        static Integer recursiveDivision(const Integer& num1, const Integer& num2);
};