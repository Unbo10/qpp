#ifndef COMPARABLE_H
#define COMPARABLE_H

template <typename T>
class Comparable
{
    public:
        virtual bool operator<(const T& another) const = 0;
        virtual bool operator==(const T& another) const = 0;
        virtual ~Comparable() = default; 
};


#endif