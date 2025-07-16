#pragma once

/**
 * @class Iterator
 * @brief An iterator class template for traversing sequences of elements.
 * 
 * This class implements a forward iterator with the minimum required
 * operations for use with STL algorithms and range-based for loops.
 * 
 * @tparam U Type of elements being iterated over
 */
template <typename U>
class Iterator
{
    private:
        /** @brief Pointer to the current element */
        U* ptr;
    public:
        /**
         * @brief Construct an iterator pointing to a specific element
         * @param p Pointer to the element
         */
        Iterator(U* p) : ptr(p) {}

        /**
         * @brief Dereference operator to access the element
         * @return Reference to the current element
         */
        U& operator*() const { return *ptr; }

        /**
         * @brief Pre-increment operator to advance the iterator
         * @return Reference to this iterator after advancement
         */
        Iterator& operator++() 
        {
            ptr++;
            return *this;
        }

        /**
         * @brief Inequality comparison operator
         * @param other Iterator to compare against
         * @return true if iterators point to different elements, false otherwise
         */
        bool operator!=(const Iterator& other) const
        {
            return ptr != other.ptr;
        }
};
