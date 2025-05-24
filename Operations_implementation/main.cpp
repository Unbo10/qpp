#include <iostream>
#include "../Numbers/Integer.cpp"
#include "../Numbers/Number.cpp"
#include "../Numbers/Rational.cpp"
#include "../utils/OrderedList.cpp"

int main() {
    //*Ordered list
    // OrderedList<Integer> sorted;
    // Integer num = 15;
    // sorted.add(15);
    // sorted.add(2);
    // sorted.add(18);
    // sorted.add(16);

    // OrderedList<Integer>::cleanBlanckSpaces(sorted);
    // sorted.replace(12, 1);
    // std::cout << sorted;

    //*Operations
    Integer a(2), b(10);
    // a = b;
    a ^= b;
    std::cout << (a >= b) << "\n";
    std::cout << a << "\n";

    //!ISSUES FOUND
    //!19 divided by 10
    //!-10 modulo -2
    //!Power is taking too long
}