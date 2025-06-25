#pragma once

/**
 * @brief Abstract base class that provides comparison operations.
 * 
 * This class serves as a base for objects that need to be comparable.
 * By implementing just the equality (==) and less-than (<) operators,
 * all of the remainding comparison operators (!=, >, <=, and >=.) are
 * implemented in the derived classes automatically:
 * 
 * @tparam T The type of the derived class implementing this interface.
 *           Using the Curiously Recurring Template Pattern (CRTP).
 */
template <typename T>
class Comparable
{
public:
    virtual bool operator==(const T& other) const = 0;
    virtual bool operator<(const T& other) const = 0;

    friend bool operator!=(const T& comp1, const T& comp2) {
        return !(comp1 == comp2);
    }

    friend bool operator>(const T& comp1, const T& comp2) {
        return comp2 < comp1;
    }

    friend bool operator<=(const T& comp1, const T& comp2) {
        return !(comp2 < comp1);
    }

    friend bool operator>=(const T& comp1, const T& comp2) {
        return !(comp1 < comp2);
    }

    virtual ~Comparable() = default;
};
