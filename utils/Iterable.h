#pragma once

#include "Iterator.h"

/**
 * @brief Defines the Iterable interface template
 * 
 * Its main goal is to define the methods any derived classes should implement
 * (`begin()` and `end()`) to be compatible with range-based for loops.
 * 
 * @tparam U The type of elements contained in the iterable collection
 */
template <typename U>
class Iterable
{
    public:
        virtual Iterator<U> begin() const = 0;
        virtual Iterator<U> end() const = 0;
};