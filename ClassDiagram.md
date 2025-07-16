# Class diagram

```mermaid
classDiagram
    %% Abstract base classes and interfaces
    class Number~T~ {
        <<abstract>>
        -bool sign
        +getSign() bool
        +setSign(bool) void
        +operator+(T) T*
        +operator-(T) T
        +operator*(T) T
        +operator/(T) T
    }
    
    class Comparable~T~ {
        <<interface>>
        +operator==(T) bool*
        +operator<(T) bool*
        +operator!=(T) bool
        +operator>(T) bool
        +operator<=(T) bool
        +operator>=(T) bool
    }
    
    class Iterable~T~ {
        <<interface>>
        +begin() Iterator~T~
        +end() Iterator~T~
    }
    
    %% Core numeric classes
    class Natural {
        -List~unsigned short~ digits
        +Natural(long long)
        +Natural(Natural&)
        +operator+(Natural) Natural
        +operator-(Natural) List~Natural~
        +operator*(Natural) Natural
        +operator/(Natural) Natural
        +operator[](int) unsigned short
        +operator<(Natural) bool
        +operator==(Natural) bool
        +size() int
        +getNumOfDigits() int
        +gcd(Natural, Natural) Natural$
        +divideBy2(Natural) Natural$
        +multiplyBy10() void
        +splitIn4(Natural) List~Natural~$
        +toomCook4(Natural, Natural) Natural$
        +smallestGeqPowerOfBase(Natural, Natural) Natural$
        +cleanDigits(Natural) void$
    }
    
    class Integer {
        -Natural absolutePart
        -bool sign
        +Integer(long long)
        +Integer(Natural, bool)
        +Integer(Integer&)
        +operator+(Integer) Integer
        +operator-(Integer) Integer
        +operator*(Integer) Integer
        +operator/(Integer) Integer
        +operator^(Integer) Integer
        +operator[](int) unsigned short
        +operator<(Integer) bool
        +operator==(Integer) bool
        +getAbsolutePart() Natural
        +getSign() bool
        +setSign(bool) void
        +getNumOfDigits() int
        +gcd(Integer, Integer) Natural$
        +splitIn4(Integer) List~Natural~$
        +toomCook4(Integer, Integer) Integer$
    }
    
    class Rational {
        -Natural numerator
        -Natural denominator
        -bool sign
        +decimalPoints int$
        +Rational()
        +Rational(Integer, Integer)
        +Rational(Integer)
        +Rational(Natural)
        +Rational(double)
        +Rational(string)
        +Rational(Rational&)
        +operator+(Rational) Rational
        +operator-(Rational) Rational
        +operator*(Rational) Rational
        +operator/(Rational) Rational
        +operator^(Rational) Rational
        +operator<(Rational) bool
        +operator==(Rational) bool
        +toDouble() double
        +multiplyInverse() Rational
        +abs() Rational
        +invert() Rational
        +getNumerator() Integer
        +getDenominator() Integer
        +simplify() void
    }
    
    %% Linear algebra classes
    class Vector {
        -List~Rational~ components
        +Vector(int)
        +Vector(Vector&)
        +Vector(List~Rational~)
        +operator+(Vector) Vector
        +operator-(Vector) Vector
        +operator-() Vector
        +operator*(Vector) Rational
        +operator[](int) Rational&
        +operator==(Vector) bool
        +operator!=(Vector) bool
        +size() int
        +dimension() int
        +appendComponent(Rational) void
        +removeComponent() void
        +clear() void
        +replace(Rational, int) void
        +projectionIn(Vector) Vector
        +norm(Vector) Rational$
    }
    
    class Matrix {
        -List~Vector~ array
        +Matrix(int, int)
        +Matrix(Matrix&)
        +Matrix(Vector&)
        +operator+(Matrix) Matrix
        +operator-(Matrix) Matrix
        +operator*(Matrix) Matrix
        +operator[](int) Vector&
        +operator==(Matrix) bool
        +rows() int
        +columns() int
        +reshape(int, int) Matrix
        +splitIn4() List~Matrix~
        +splitIn9() List~Matrix~
        +strassenSubmatrices(List~Matrix~, List~Matrix~) List~Matrix~$
        +ladermanSubmatrices(List~Matrix~, List~Matrix~) List~Matrix~$
        +strassenMm(Matrix, Matrix) Matrix$
        +ladermanMm(Matrix, Matrix) Matrix$
        +scalonadeForm(Matrix) Matrix$
        +identity(int) Matrix$
        +transpose(Matrix) Matrix$
        +inverse(Matrix) Matrix$
        +det(Matrix) Rational$
        +fibonnacci(Natural) Rational$
    }
    
    %% Utility classes
    class List~T~ {
        -T* array
        -int capacity
        -int length
        -DEFAULT_INITIAL_CAPACITY int$
        -DEFAULT_RESIZE double$
        +List()
        +List(int)
        +List(List~T~&)
        +List(initializer_list~T~)
        +add(T) void
        +add(T, int) void
        +pop() T
        +pop(int) T
        +replace(T, int) void
        +operator[](int) T&
        +operator=(List~T~) List~T~&
        +operator==(List~T~) bool
        +size() int
        +getSize() int
        +getCapacity() int
        +getArray() T*
        +isEmpty() bool
        +clear() void
        +clear(int) void
        +invert() void
        +concatenate(List~T~, List~T~) List~T~$
        -resize() void
    }
    
    class Iterator~T~ {
        -T* current
        +Iterator(T*)
        +operator*() T&
        +operator->() T*
        +operator++() Iterator~T~&
        +operator++(int) Iterator~T~
        +operator==(Iterator~T~) bool
        +operator!=(Iterator~T~) bool
    }
    
    %% Inheritance relationships (is-a)
    Number~Rational~ <|-- Rational : inherits
    Number~Integer~ <|-- Integer : inherits
    Comparable~Natural~ <|.. Natural : implements
    Comparable~Integer~ <|.. Integer : implements
    Comparable~Rational~ <|.. Rational : implements
    Iterable~Rational~ <|.. Vector : implements
    Iterable~Vector~ <|.. Matrix : implements
    Iterable~T~ <|.. List : implements
    
    %% Composition relationships (has-a)
    Integer *-- Natural : has absolutePart
    Rational *-- Natural : has numerator
    Rational *-- Natural : has denominator
    Vector *-- List : has components
    Matrix *-- List : has array
    Natural *-- List : has digits
    
    %% Template instantiations
    List~Rational~ ..> Rational : parameterized with
    List~Vector~ ..> Vector : parameterized with
    List~"unsigned short"~ ..> Natural : parameterized with
    List~Natural~ ..> Natural : parameterized with
    List~Integer~ ..> Integer : parameterized with
    List~Matrix~ ..> Matrix : parameterized with
    
    %% Usage dependencies
    Vector ..> Rational : uses
    Matrix ..> Vector : uses
    Matrix ..> Rational : uses
    Integer ..> Natural : uses
    Rational ..> Integer : uses
    Rational ..> Natural : uses
    
    %% Friend function relationships
    Vector ..> Matrix : friend operations
    Natural ..> Integer : friend operations
    Integer ..> Rational : friend operations
    
    %% Static method dependencies
    Matrix ..> Natural : static methods use
    Integer ..> Natural : static methods use
    Natural ..> Natural : static methods use
```

## Class Relationships Explanation

### Inheritance Hierarchy (is-a)
- **Integer** and **Rational** inherit from **Number<T>** abstract base class
- **Natural**, **Integer**, **Rational** implement **Comparable<T>** interface
- **Vector**, **Matrix**, **List<T>** implement **Iterable<T>** interface

### Composition Relationships (has-a)
- **Integer** has a **Natural** (absolutePart) for magnitude
- **Rational** has two **Natural** objects (numerator, denominator)
- **Natural** has a **List<unsigned short>** (digits) for storage
- **Vector** has a **List<Rational>** (components) for elements
- **Matrix** has a **List<Vector>** (array) for rows

### Template Specializations
- **List<T>** is specialized for various types:
  - `List<Rational>` for Vector components
  - `List<Vector>` for Matrix rows
  - `List<unsigned short>` for Natural digits
  - `List<Natural>` and `List<Integer>` for algorithm results
  - `List<Matrix>` for matrix decomposition algorithms

### Design Patterns
1. **Template Pattern**: List<T> and Number<T> are generic containers/interfaces
2. **Composition Pattern**: Complex types built from simpler ones
3. **CRTP (Curiously Recurring Template Pattern)**: Used in Comparable<T> and Number<T>
4. **Iterator Pattern**: All containers provide begin()/end() for range-based loops
5. **Static Factory Methods**: Matrix provides static methods for special matrices
6. **Friend Functions**: Extensive use of friend operators for natural syntax

### Algorithm Implementations
- **Strassen** and **Laderman** algorithms for fast matrix multiplication
- **Toom-Cook 4-way** algorithm for fast integer multiplication
- **GCD algorithms** for Natural and Integer types
- **Matrix operations**: transpose, inverse, determinant, identity creation

### Stream Support
All major classes support iostream operations with overloaded `<<` and `>>` operators for easy input/output.

