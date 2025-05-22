#ifndef ITERABLE_H
#define ITERABLE_H
#include "Iterator.cpp"

template <typename U>
class Iterable
{
    public:
        virtual Iterator<U> begin() const = 0;
        virtual Iterator<U> end() const = 0;
};

#endif