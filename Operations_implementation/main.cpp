#include <iostream>
#include "../Numbers/Integer.cpp"
#include "../Numbers/Number.cpp"
#include "../Numbers/Rational.cpp"
#include "../utils/OrdenerList.cpp"

int main() {
    OrdenerList<Integer> sorted;
    Integer num = 15;
    sorted.add(15);
    sorted.add(2);
    sorted.add(18);
    sorted.add(16);

    OrdenerList<Integer>::cleanBlanckSpaces(sorted);
    sorted.replace(12, 1);
    std::cout << sorted;
}