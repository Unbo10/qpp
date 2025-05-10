#ifndef ITERATOR_H
#define ITERATOR_H

template <typename U>
class Iterator
{
    private:
        U* ptr;
    public:
        Iterator(U* p) : ptr(p) {}

        U& operator*() const { return *ptr; }

        Iterator& operator++() 
        {
            ptr++;
            return *this;
        }

        bool operator!=(const Iterator& other) const
        {
            return ptr != other.ptr;
        }
};

#endif