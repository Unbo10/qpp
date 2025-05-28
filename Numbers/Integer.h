#pragma once

#include <iostream>
#include "../utils/List.h"
#include "Number.h"

class Integer : public Number<Integer> {
private:
    static const int digitsByBlock = 5;
    List<int> digitsInteger;

    //***NON-STATIC HELPER METHODS***
    void addDigit(long long newDigit);
    void addDigit(const Integer& newDigit);
    void forceAdd(long long newDigit);
    void setSize(int newSize);
    int digitAt(int index) const;
    int operator[](int index) const;

    //***STATIC HELPER METHODS***
    static void cleanDigits(Integer& num);
    static int digits(long long x);
    static int max_int(int x, int y);
    static int min_int(int x, int y);
    static int getNumOfDigits(long long x);

    //***PARTITION METHODS FOR ALGORITHMS***
    Integer getHighPart(int index) const;
    Integer getLowPart(int index) const;

    //***MULTIPLICATION ALGORITHMS***
    static Integer multiplyConventional(const Integer& num1, const Integer& num2);
    static Integer multiplyKaratsuba(const Integer& num1, const Integer& num2);
    
    //***DIVISION HELPER***
    static int estimateQuotient(const Integer& rem, const Integer& divisor);

public:
    //***CONSTRUCTORS***
    Integer();
    Integer(long long x);
    Integer(const Integer& toC);
    ~Integer();

    //***COMPARISON OPERATORS***
    
    bool operator==(const Integer& other) const override;
    friend bool operator==(const int int_num, const Integer& num);
    friend bool operator==(const Integer& num, const int int_num);
    
    friend bool operator!=(const Integer& num1, const int num2);
    friend bool operator!=(const int num1, const Integer& num2);
    
    bool operator<(const Integer& other) const override;
    bool operator<(const int int_num);
    friend bool operator<(int int_num1, const Integer& num2);

    friend bool operator<=(const int int_num, const Integer& num);
    friend bool operator<=(const Integer& num, const int int_num);
    
    friend bool operator>(const int int_num1, const Integer& num2);
    friend bool operator>(const Integer& num1, const int int_num2);
    
    friend bool operator>=(const int int_num1, const Integer& num2);
    friend bool operator>=(const Integer& num1, const int int_num2);

    //***ARITHMETIC OPERATORS***
    Integer operator+(const Integer& other) const override;
    friend Integer operator+(int num1, const Integer& num2);
    friend Integer operator+(const Integer& num1, int num2);

    Integer operator-(const Integer& other) const override;
    friend Integer operator-(int num1, Integer& num2);
    friend Integer operator-(Integer& num1, int num2);
    Integer operator-() const override;

    Integer operator*(const Integer& other) const override;
    friend Integer operator*(int num1, const Integer& num2);
    friend Integer operator*(const Integer& num1, int num2);

    Integer operator/(const Integer& other) const override;
    friend Integer operator/(int num1, const Integer& num2);
    friend Integer operator/(const Integer& num1, int num2);

    Integer operator%(const Integer& other) const;
    friend Integer operator%(int num1, const Integer& num2);
    friend Integer operator%(const Integer& num1, int num2);

    Integer operator^(const Integer& other) const override;
    
    Integer operator=(const Integer& other) override;
    Integer operator=(const long long num_int);

    //***NON-STATIC UTILITY METHODS***
    Integer divideBy2() const;
    Integer multiplyByDigit(int x) const;
    
    //***STATIC UTILITY METHODS***
    static Integer abs(const Integer& r);
    static Integer divideRecursively(const Integer& num1, const Integer& num2);
    static Integer multiplyByBase(const Integer& num, int times);
    static Integer binaryEcludian(Integer n1, Integer n2);
    static List<Integer> extendEuclidean(const Integer& num1, const Integer& num2);
    
    //***BASE CONVERSION***
    void changeBase(int newBase, Integer& number);

    //***STREAM OPERATORS***
    friend std::ostream& operator<<(std::ostream& os, const Integer& number);
    friend std::istream& operator>>(std::istream& is, Integer& num);
    
    //***GETTERS***
    int getBase() const;
    int getNumberSize() const;
    List<int> getList();
    bool isEven() const;
};