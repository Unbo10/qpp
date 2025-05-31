#pragma once

#include "../utils/List.h"
#include "../utils/Comparable.h"

template <typename T>
class OrderedList: public List<T>
{
    public: 
        //*To make sure the elements inside the list are comparable, and can
        //*therefore be ordered, a constraint is enforced on the template
        static_assert(std::is_base_of_v<Comparable<T>, T>, "T must be comparable");

        //***CONSTRUCTORS***

        /**
         * @brief Default constructor.
         * 
         * Initializes an empty ordered list of capacity 10 by invoking the
         * base List<T> constructor.
         */
        OrderedList(): List<T>() {}

        /**
         * @brief Constructs an ordered list with a specified initial capacity.
         * 
         * This constructor initializes an ordered list with a given capacity
         * for elements. It delegates to the base List<T> constructor, passing
         * the initial size parameter.
         * 
         * @param INITIAL_CAPACITY The initial capacity of the ordered list.
         */
        OrderedList(int INITIAL_CAPACITY) : List<T>(INITIAL_CAPACITY) {}

        /**
         * @brief Copy constructor.
         *
         * Constructs a new ordered list by copying the elements of another
         * one.
         * 
         * @tparam T The type of elements stored in the list.
         * @param list The ordered list to copy from.
         */
        OrderedList(const OrderedList<T>& list)
        {
            this->length = list.length;
            this->capacity = list.length;
            this->array = new T[this->capacity];

            for(T item: list)
                List<T>::add(item);
        }

        /**
         * @brief Finds the index where a given item is stored or where it
         * should be inserted to preserve order in the list.
         *  
         * This method uses binary search to efficiently locate the position of
         * an item in the ordered list. If the item exists in the list, its
         * index is returned. Otherwise, the index where it should be inserted
         * to maintain order is returned.
         * 
         * @param item The item to search for in the ordered list.
         * @return int The index where the item is found, or the index where it
         * should be inserted.
         */
        int findIndex(const T& item)
        {
            int upper = this->length -1;
            int lower = 0;
            int middle = 0;

            while(lower <= upper)
            {
                middle = (lower+upper)/2;
                T mid = (*this)[middle];

                if(item == mid) return middle;
                if(item < mid) upper = middle-1;
                else lower = middle+1;
            }

            return lower;
        }

        /**
         * @brief Adds a new item to the ordered list, maintaining the order.
         * 
         * This method finds the appropriate index where the new item should be
         * inserted to maintain the ordered state of the list, and then adds
         * the item at that position.
         * 
         * @param newItem The item to be added to the ordered list.
         */
        void add(const T& newItem)
        {
            int index = this->findIndex(newItem);
            List<T>::add(newItem, index);
        }

        /**
         * @brief Add a new item to the ordered list at the specified index
         * only if adding the element at that index maintains the order in the
         * list.
         * 
         * This function attempts to add a new item at the given index, but will
         * only do so if it preserves the ordering property of the list based on
         * the comparability of type T.
         * 
         * @param newItem The item to be added to the list
         * @param index The position at which to add the item (0-based indexing)
         * @throws std::invalid_argument If the index is out of bounds (negative or greater than length)
         */
        void add(const T& newItem, int index)
        {
            if(index > this->length || index < 0)
                throw std::invalid_argument("Index out of bounds");

            if(index == this->length)
            {
                if ((*this)[index-1] < newItem || newItem == (*this)[index-1])
                {
                    List<T>::add(newItem, index);
                    return;
                }
            }

            if(index == 0)
            {
                if(newItem == (*this)[index-1] || newItem < (*this)[index-1])
                {
                    List<T>::add(newItem, 0);
                    return;
                }
            }

            T next = (*this)[index], prev = (*this)[index-1];
            if((prev < newItem || prev == newItem) && (newItem < next || next == newItem))
                List<T>::add(newItem, index);                
        }

        /**
         * @brief Replaces the element at the specified index with the provided
         * item, maintaining the ordered nature of the list.
         * 
         * This method replaces an element in the ordered list while ensuring
         * that the list remains ordered. The replacement is only performed if
         * the new item would maintain the order.
         * 
         * @param item The item to replace the existing element with.
         * @param index The position of the element to be replaced.
         * @throws std::invalid_argument If the provided index is out of
         * bounds.
         * @note If replacement would violate the ordering constraint, the
         * operation is silently aborted.
         */
        void replace(const T& item, int index)
        {
            if(index >= this->length || index < 0)
                throw std::invalid_argument("Index out of bounds");
            
            if(this->length == 1) 
            {
                List<T>::replace(item, index);
                return;
            }

            if(index == this->length - 1)
            {
                T prev = (*this)[index - 1];
                if(prev < item || prev == item)
                    List<T>::replace(item, index);
                return;
            }

            if(index == 0)
            {
                T next = (*this)[1];
                if(item < next || next == item)
                    List<T>::replace(item, index);
                return;
            }

            T prev = (*this)[index-1], next = (*this)[index+1];
            if((prev < item || prev == item) && (item < next || next == item))
                List<T>::replace(item, index);
        }

        /**
         * @brief Trims excess capacity in the OrderedList by resizing the
         * array to match its length.
         * 
         * This function creates a new array with size equal to the list's current length,
         * copies all elements from the original array to the new array, and then replaces
         * the original array with the new one. This effectively removes any unused capacity
         * in the list, optimizing memory usage. If the list's capacity is already equal to
         * its length, the function does nothing.
         * 
         * @tparam T The type of elements stored in the OrderedList
         * @param list The OrderedList to trim
         */
        static void trimEmptySpaces(OrderedList<T>& list)
        {
            if(list.capacity == list.length)
                return;
            
            T* newArray = new T[list.length];
            for (int i = 0; i < list.length; ++i)
                newArray[i] = list.array[i];

            delete[] list.array;
            list.array = newArray;
            list.capacity = list.length;
        }
};