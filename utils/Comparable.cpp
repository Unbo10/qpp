#ifndef COMPARABLE_H
#define COMPARABLE_H

template <typename T>
class Comparable
{
    public:
        virtual bool eq(const T& other) const = 0;
        virtual bool lt(const T& other) const = 0;
        bool leq(const T& other) 
        {
            return lt(other) || eq(other);
        }
        
        bool gt(const T& other) const
        {
            return other.lt(*this);
        }

        bool geq(const T& other) const
        {
            return other.leq(*this);
        }

        friend bool operator==(const T& first, const T& second) {
            return first.eq(second);
        }

        friend bool operator!=(const T& first, const T& second) {
            return !(first.eq(second));
        }

        friend bool operator<(const T& first, const T& second) {
            return first.lt(second);
        }

        friend bool operator>(const T& first, const T& second) {
            return second.lt(first);
        }

        friend bool operator<=(const T& first, const T& second) {
            return first.leq(second);
        }

        friend bool operator>=(const T& first, const T& second) {
            return second.leq(first);
        }

        ~Comparable() = default; 
};


#endif