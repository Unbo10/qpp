#pragma once

#include "Iterator.h"

template <typename U>
class Iterable
{
    public:
        virtual Iterator<U> begin() const = 0;
        virtual Iterator<U> end() const = 0;
};