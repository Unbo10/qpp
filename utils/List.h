#pragma once

#include <iostream>
#include <initializer_list>

#include "Iterator.h"
#include "Iterable.h"

/**
 * @brief A dynamic array-based list implementation that provides common list
 * operations.
 * 
 * It is a generic container that implements a dynamic array which resizes by
 * a factor of 1.4.
 * 
 * The class supports common operations like adding, removing, and replacing
 * elements. The List also implements expected functionality such as copy
 * construction, assignment operations, and equality comparisons.
 * 
 * Additionally, ir provides iterator support (via inheriting from Iterable),
 * enabling it to be used in range-based for loops for convenient traversal.
 * It also includes functionality for list concatenation.
 * 
 * @tparam U The type of elements stored in the list
 * 
 * @note The list implements the Iterable interface for iteration support
 */
template <typename U>
class List : public Iterable<U>
{
    protected:
        static const int DEFAULT_INITIAL_CAPACITY = 10;
        static constexpr double DEFAULT_RESIZE = 1.6;

        U* array;
        /**
         * @brief Maximum capacity of the array.
         */
        int capacity;
        /**
         * @brief Number of elements in the array (A.K.A. size).
         */
        int length;

        /**
         * @brief Relengths the internal array to increase its capacity.
         * 
         * @note Does so by a factor of 1.4
         */
        void resize()
        {
            int NEW_CAPACITY;
            if(capacity == 1)
                NEW_CAPACITY = 2;
            else
                NEW_CAPACITY = capacity*DEFAULT_RESIZE;
            U* help = array;
            array = new U[NEW_CAPACITY];

            for(int i = 0; i < length; i++)
                array[i] = help[i];

            delete[] help;
            capacity = NEW_CAPACITY;
        }

            public:
        //***CONSTRUCTORS AND DESTRUCTOR***

        /**
         * @brief Default constructor
         * 
         * Constructs a List with a capacity of 10 elements.
         */
        List() : List(DEFAULT_INITIAL_CAPACITY) {}

        /**
         * @brief Constructs a new List with the specified initial capacity.
         * 
         * @param INITIAL_CAPACITY The initial capacity of the list.
         * 
         * @details This constructor creates a new list with a pre-allocated
         * array of capacity 10. The length of the list is initially set to 0.
         */
        List(int INITIAL_CAPACITY)
        {
            array = new U[INITIAL_CAPACITY];
            capacity = INITIAL_CAPACITY;
            length = 0;
        }

        /**
         * @brief Copy constructor for creating a new list from another list.
         * 
         * Constructs a new list by copying all elements from another list
         * of potentially different type U where U is implicitly convertible to
         * T.
         * 
         * @tparam U Type of elements in the source list (must be convertible
         * to T).
         * @param another The source list to copy from.
         * 
         * @note This constructor first allocates memory for the new list using
         * the length of the source list, then copies each element
         * individually.
         */
        List(const List<U>& another)
        {
            capacity = another.capacity;
            length = another.length;
            array = new U[capacity];
            for(int i = 0; i < length; i++)
                array[i] = another.array[i];
        }

        /**
         * @brief Initializer list constructor. Constructs a List from a list
         * of values.
         * 
         * @param values The initializer array-like containing elements of type
         * U to initialize the List with.
         * 
         * Creates a List with length equal to the number of elements in the
         * initializer list. If the initializer list is empty, the capacity is
         * set to 10. Otherwise, the capacity is set equal to the length of
         * `values`.
         */
        List(std::initializer_list<U> values)
        {
            length = values.size();
            capacity = length > 0 ? length : DEFAULT_INITIAL_CAPACITY;
            array = new U[capacity];
            int i = 0;
            for (const U& val : values)
                array[i++] = val;
        }

        ~List() 
        {
            delete[] array;
        }

        //***SINGLE-ELEMENT OPERATIONS***

        /**
         * @brief Inserts an item at a specified index in the list.
         *
         * The function inserts the given item at the specified index and
         * shifts all elements at positions greater than or equal to index
         * one position to the right. If `length == capacity`, it will be 
         * resized before inserting the new item.
         *
         * @param item The item to be inserted.
         * @param index The position at which to insert the item. Must be
         * between 0 and length (inclusive).
         * 
         * @note If the index is out of bounds, it exits the method and returns
         * nothing.
         */
        void add(const U& item, int index)
        {
            if(index < 0 || index > length)
                return;
            
            if(length == capacity) 
            {
                // std::cout << "Enter aaaaa\n";
                resize();
            }

            for(int i = length; i > index; i--)
                array[i] = array[i-1];
            
            array[index] = item;
            length++;
        }

        /**
         * @brief Adds an item to the end of the list.
         * 
         * This is a convinience method that calls `add(const U&, int index)`
         * and is equivalent to `add(item, length)`.
         * 
         * @param item The item to be added.
         */
        void add(const U& item)
        {
            add(item, length);
        }

        void add(U& item)
        {
            add(item, length);
        }

        /**
         * @brief Replaces an item at a specified index in the list.
         * 
         * @tparam U The type of the item to be replaced.
         * @param item The new item to replace with.
         * @param index The position where the replacement should occur.
         * @throws `std::invalid_argument` If the index is out of bounds
         * (negative or >= length).
         */
        void replace(const U& item, int index)
        {
            if(length <= index || index < 0)
                throw std::invalid_argument("Index out bound");

            array[index] = item;
        }

        /**
         * @brief Removes and returns the element at the specified index from
         * the list.
         * 
         * This method removes an element at the given index from the list,
         * shifts all subsequent elements one position to the left to fill
         * the gap, and returns the removed element.
         * 
         * @param index The index of the element to be removed.
         * @return U The element that was removed from the list.
         * @throws `std::out_of_range` If the index is negative, greater than
         * or equal to the length, or if the list is empty.
         */
        U pop(int index)
        {
            if(length <= index || index < 0 || length == 0)
                throw std::out_of_range("Index out of bounds");

            U item = array[index];
            for(int i = index; i < length - 1; i++)
                array[i] = array[i+1];

            length--;
            return item;
        }

        /**
         * @brief Remove and return the first element from the list.
         * 
         * Convinience method that calls `pop(int index)` and is equivalent to
         * `pop(0)`.
         *
         * @return U The first element of the list that was removed.
         * @throws `std::out_of_range` If the list is empty.
         */
        U pop()
        {
            return pop(0);
        }

        //***GETTERS***

        /**
         * @return bool True if the list has no elements stored. False
         * otherwise.
         */
        bool isEmpty()
        {
            return length == 0;
        }

        /**
         * @return int length of the list (number of elements).
         */
        int size() const
        {
            return length;
        }

        /**
         * @return int size of the list (current number of elements or occupied
         * spaces in the list).
         */
        int getSize() const
        {
            return length;
        }

        /**
         * @return int Capacity of the list (maximum number of elements without
         * resizing).
         */
        int getCapacity() const 
        {
            return capacity;
        }

        /**
         * @return U The array-like object with which the list was implemented.
         */
        U* getArray() const
        {
            return array;
        }

        //***UTIL METHODS***

        /**
         * @brief Clears the list and resets it to its default state (no
         * elements stored and default capacity, 10).
         * 
         * Equivalent to calling `clear(10)`.
         */
        void clear()
        {
            this->clear(DEFAULT_INITIAL_CAPACITY);
        }
        
        /**
         * @brief Clears (empties) the list and sets its capacity to a given
         * one.
         * 
         * This method deallocates the current array, sets the length to zero,
         * allocates a new array with the default initial length, and updates
         * the capacity to the default initial length.
         * 
         * @param newCapacity int new capacity of the array
         */
        void clear(int newCapacity)
        {
            delete[] array;
            length = 0;
            array = new U[newCapacity];
            capacity = newCapacity;
        }
        
        void invert()
        {
            for(int i = 0; i < length/2; i++)
            {
                U aux;
                aux = array[i];
                array[i] = array[length - i - 1];
                array[length - i - 1] = aux;
            }
        }
        
        //***OTHER OPERATIONS***

        /**
         * @brief Concatenates two lists into a new list.
         * 
         * This static method creates a new list by combining elements from two
         * input lists. Elements are added in order, first from `l1` and then
         * from `l2`.
         * 
         * @tparam M Type of elements stored in the lists.
         * @param l1 First list to concatenate.
         * @param l2 Second list to concatenate.
         * @return List<M> A new list containing all elements from `l1`
         * followed by all elements from `l2`.
         */
        template <typename M>
        static List<M> concatenate(const List<M> l1, const List<M> l2)
        {
            List<M> concatenatedL;
            for(M item: l1)
                concatenatedL.add(item);
            for(M item: l2)
                concatenatedL.add(item);
            return concatenatedL;
        }

        /**
         * @brief Equality operator for List objects
         * 
         * Compares two lists element by element. Two lists are considered
         * equal if they have the same length and all corresponding elements
         * are equal.
         * 
         * @tparam U The type of elements in the lists.
         * @param l1 First list to compare.
         * @param l2 Second list to compare.
         * @return true If both lists have the same length and all elements are
         * equal. False otherwise.
         */
        friend bool operator==(const List<U> l1, const List<U> l2)
        {
            if(l1.getSize() != l2.getSize()) return false;

            for(int i = 0; i < l1.getSize(); i++)
                if(l1[i] != l2[i]) return false;

            return true;
        }

        /**
         * @brief Accesses an element at the specified index in the list.
         * 
         * This operator provides read and write access to an element in the
         * list. It performs bound checking to ensure the index is valid.
         * 
         * @param index The index of the element to access, must be between 0
         * and length-1.
         * @return U& A reference to the element at the specified index.
         * @throws std::invalid_argument If the index is out of bounds
         * (negative or >= length).
         */
        const U& operator[](int index) const
        {
            if (index < 0 || index >= length) {
                throw std::invalid_argument("Index out of the range, entro");
            }

            return this->array[index];
        }

        U& operator[](int index)
        {
            if (index < 0 || index >= length) {
                throw std::invalid_argument("Index out of the range, entro");
            }

            return this->array[index]; 
        }

        /**
         * @brief Copy assignment operator for the List class
         * 
         * Deallocates the current array, copies all elements from another
         * List, and adjusts the capacity and length accordingly.
         * 
         * @tparam U The type of elements in the List
         * @param another The List to copy from
         * @return List<U>& Reference to the current List after assignment
         */
        List<U>& operator=(const List<U>& another)
        {
            if (this == &another) // Self-assignment check
                return *this;
                
            delete[] array;
            capacity = another.capacity;
            length = another.length;
            array = new U[capacity];
            for (int i = 0; i < length; i++)
                array[i] = another.array[i];

            return *this;
        }

        /**
         * @brief Overloads the output stream operator for List objects.
         * 
         * Prints the List contents in the format `[elem1, elem2, ..., elemN]`.
         * 
         * @param os The output stream to write to
         * @param list The List object to be printed
         * @return std::ostream& Reference to the output stream after writing
         */
        friend std::ostream& operator<<(std::ostream& os, const List& list)
        {
            os << "[";
            for(int i = 0; i < list.length; i++)
            {
                os << list.array[i];
                if(i != list.length - 1)
                    os << ", ";
            }
            os << "]";
            return os;
        }
        
        //***ITERATOR INITIALIZATIONS***

        Iterator<U> begin() const { return Iterator<U>(array); }
        Iterator<U> end() const { return Iterator<U>(array + length); }
};