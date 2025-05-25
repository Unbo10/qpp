#ifndef COMPARABLE_H
#define COMPARABLE_H

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

#endif
