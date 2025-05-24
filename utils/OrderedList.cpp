#ifndef ORDERED_LIST
#define ORDERED_LIST
#include "../utils/List.cpp"
#include "../utils/Comparable.cpp"

template <typename T>
class OrderedList: public List<T>
{
    public: 
        static_assert(std::is_base_of_v<Comparable<T>, T>, "T must be comparable");
        OrderedList(int INITIAL_SIZE) : List<T>(INITIAL_SIZE) {}
        OrderedList() {}
        OrderedList(const OrderedList<T>& list)
        {
            this->length = list.length;
            this->capacity = list.length;
            this->array = new T[this->capacity];

            for(T item: list)
                List<T>::add(item);
        }

        int findIndex(const T& item)
        {
            int upper = this->length -1;
            int lower = 0;
            int middle = 0;

            while(lower <= upper)
            {
                middle = (lower+upper)/2;
                T mid = (*this)[middle];
                if(item == mid)
                    return middle;
                if(item < mid)
                    upper = middle-1;
                else lower = middle+1;
            }

            return lower;
        }

        void add(const T& newItem)
        {
            int index = this->findIndex(newItem);
            List<T>::add(newItem, index);
        }

        void add(const T& newItem, int index)
        {
            if(index > this->length || index < 0)
                throw std::invalid_argument("Invlaid index to add");

            if(index == this->length && ((*this)[index-1] < newItem || newItem == (*this)[index-1]))
            {
                List<T>::add(newItem, index);
                return;
            }

            if(index == 0 && (newItem == (*this)[index-1] || newItem < (*this)[index-1]))
            {
                List<T>::add(newItem, 0);
                return;
            }

            T next = (*this)[index], prev = (*this)[index-1];
            if((prev < newItem || prev == newItem) && (newItem < next || next == newItem))
                List<T>::add(newItem, index);                
        }

        void replace(const T& item, int index)
        {
            if(index >= this->length || index < 0)
                throw std::invalid_argument("Invlaid index to replace");
            
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

        static void cleanBlanckSpaces(OrderedList<T>& list)
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


#endif 