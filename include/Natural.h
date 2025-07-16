#pragma once

/*
    El objetivo de esta clase es optimazar el uso
    de los recursos de las clases Integer y Rational, usando
    lo que comunmente se conoce como unsigned int. Se hace
    la implementacion con la clase Natural, para abstraer la
    idea de un numero sin signo, que implementa las operaciones basicas. 


    La idea general es construir las clases Integer y Rational a partir de esta,
    para ello ofrecemos un numero natural de presicion arbitraria.
    */
   
   #include "../utils/List.h"
   #include "../utils/Comparable.h"
   
   class Natural: public Comparable<Natural>
   {
    protected:
        /*
        Se hace uso de lista de presicion arbitraria, 
        para guardar los digitos del numero en orden inverso,
        en base 100. La idea de esto es conseguir eficiencia, ya que
        numeros con una gran cantidad de digitos solo se guardaran con
        la mitad del espacio.
        */
        List<unsigned short> digits;
        /*
        Para ahorrar memoria, se limpian los espacios no fundamentales,
        es decir, lugares que no se usan a la derecha, o ceros a la derecha
        */
        static void cleanDigits(Natural& num);
        static void cleanDigits(Natural& num, int index);
        
        Natural(int x, int size): digits(size) 
        {
            for(int i = 0; i< size; i++)
                digits.add(0);
        }
        friend List<Natural> res(const Natural& num1, const Natural& num2, bool re);
        friend unsigned short stimateQuant(const Natural& num1, const Natural& num2);
        public:
        Natural(long long x);
        Natural(const Natural& other);
        Natural() {};
        bool operator<(const Natural& num) const;
        friend bool operator<(const long long num1, const Natural& num2);
        bool operator==(const Natural& num) const;
        void operator=(const Natural& num2);

        //***UTILS***

        /**
        * @brief Removes leading zeros starting from the `digit`s capacity.
        * 
        * Equivalent to calling
        * `cleanDigits(num, num.digits.getCapacity() - 1)`.
        * 
        * @param num The natural number to be cleaned.
        * @param index The starting position for the cleaning operation.
        */
        static void cleanDigits(Natural& num);
        /**
        * @brief Removes leading zeros starting from a specific index.
        * 
        * Cleans the number's representation starting from the given index,
        * removing unnecessary zeros to optimize memory usage.
        * 
        * @param num The natural number to be cleaned.
        * @param index The starting position for the cleaning operation.
        */
        static void cleanDigits(Natural& num, int index);
                
        //***UTILS FOR ARITHMETIC OPERATIONS***
        
        /**
         * @brief Subtracts two Natural numbers and returns the result as a List<Natural>.
         * 
         * This function performs the subtraction operation between two Natural numbers and returns
         * the result as a List<Natural>. If re is true, it may perform additional processing.
         * 
         * @param num1 The first Natural number (minuend).
         * @param num2 The second Natural number to subtract (subtrahend).
         * @param reorder Boolean flag that guarantees the smaller number is
         * subtracted from the greater.
         * @return List<Natural> The result of the subtraction as a List of Natural numbers
         */
        friend List<Natural> subtract(const Natural& num1, const Natural& num2, bool re);
        
        /**
         * @brief Estimates a trial quotient for division operations between
         * two Natural numbers.
         * 
         * This function provides a heuristic estimation of the quotient when
         * dividing num1 by num2. It is used internally by the division
         * algorithm to accelerate the division process, as described by
         * Lamagna in his book "Computer algebra concepts and techniques".
         * 
         * @param num1 The dividend (numerator)
         * @param num2 The divisor (denominator)
         * @return unsigned short The estimated trial quotient
         */
        friend unsigned short estimateTrialQuotient(const Natural& num1, const Natural& num2);

    public:

        //***CONSTRUCTORS***

        /**
         * @brief Default constructor for Natural.
         * 
         * Creates an empty Natural number with no digits initialized.
         */
        Natural() {};
        /**
         * @brief Constructs a Natural number from a non-negative long long
         * integer.
         * 
         * Initializes a Natural number with the value equivalent to the
         * provided long long integer. The number will be stored using the
         * internal base-100 representation.
         * 
         * @param x The non-negative long long integer value to convert to a
         * Natural number
         */
        Natural(long long x);
        /**
         * @brief Copy constructor for Natural.
         * 
         * The new Natural number will have the same digits as the provided
         * one.
         * 
         * @param other The Natural number to be copied
         */
        Natural(const Natural& other);
        
        //***COMPARISON OPERATIONS***
        
        /**
         * @brief Checks if this Natural number is less than another.
         * 
         * Compares this Natural number with the provided one to determine if
         * this is smaller. The comparison is done by, first, checking if they
         * both have the same number of digits (otherwise, one is automatically
         * bigger than the other). If they do, then a digit-by-digit comparison
         * follows, starting from the most significant digits.
         * 
         * @param num The Natural number to compare with
         * @return bool Returns true if this Natural number is less than the
         * provided one, false otherwise
         */
        bool operator<(const Natural& num) const;
        /**
         * @brief Checks if two Natural numbers are equal.
         * 
         * Compares this Natural number with the provided one to determine if
         * they have the same value. Two Natural numbers are equal if they have
         * the same number of digits and all corresponding digits are equal.
         * 
         * @param num The Natural number to compare with
         * @return bool Returns true if the Natural numbers are equal, false
         * otherwise
         */
        bool operator==(const Natural& num) const;

        //***ASSIGNING AND INDEX-ACCESSING OPERATIONS***
        
        /**
         * @brief Assignment operator for Natural numbers.
         * 
         * Copies the digits of the provided number to this one's.
         * 
         * @param num2 The Natural number whose value is to be assigned to
         * this one
         */
        void operator=(const Natural& num2);
        /**
         * @brief Access operator to retrieve a single digit of the number at
         * the specified index.
         *
         * @param index The position of the digit to access (0 is the least
         * significant digit)
         * @return unsigned short The digit at the specified index
         * @throws std::out_of_range If index is negative or exceeds the
         * number's size
         */
        unsigned short operator[](int index) const;

        //***ARITHMETIC OPERATIONS***

        /**
         * @brief Adds two Natural numbers and returns their sum.
         * 
         * This function performs addition of two Natural numbers using the
         * internal base-100 representation. The operation handles carrying
         * over digits when necessary.
         * 
         * At most, the sum will have `u + v + 1` digits, where `u` is `num1`'s
         * number (size) of digits and `v` is `num2`'s number (size) of digits.
         * The true size will be determined by the number of zeros at the end
         * of the operation (they will be cleaned using `cleanDigits`).
         * 
         * It follows Lamagna's addition algorithm.
         * 
         * @note Complexity is `O(u + 1) = O(n)`.
         * 
         * @param num1 The first Natural number to add
         * @param num2 The second Natural number to add
         * @return Natural The sum of the two Natural numbers
         */
        friend Natural operator+(const Natural& num1, const Natural& num2);
        friend Natural operator+(const Natural& num1, unsigned short num2);
        friend List<Natural> operator-(const Natural& num1, const Natural& num2);
        /**
         * @brief Multiplies two Natural numbers and returns their product.
         * 
         * This function performs multiplication of two Natural numbers using the
         * internal base-100 representation. The algorithm handles proper digit
         * alignment and carrying over during the multiplication process.
         *
         * If `num1` has `u` digits and `num2` has `v` digits, then the result
         * will have at most `u + v` digits.
         * 
         * @note Complexity is `O(uv) = O(n²)`
         * 
         * @param num1 The first Natural number to multiply
         * @param num2 The second Natural number to multiply
         * @return Natural The product of the two Natural numbers
         */
        friend Natural operator*(const Natural& num1, const Natural& num2);
        friend Natural operator*(const Natural& num1, unsigned short num2);
        friend Natural operator/(const Natural& num1, const Natural& num2);

        //***STREAM OPERATIONS***

        /**
         * @brief Output stream for a Natural number using its base-10
         * representation.
         * 
         * It is almos the same as printing the number's List of digits, just
         * that, in case one of them is smaller than 10, a leading zero is
         * added to make sure it is correctly outputted in base 10.
         * 
         * @param os The output stream to write to
         * @param num The Natural number to output
         * @return std::ostream& Reference to the modified output stream
         */
        friend std::ostream& operator<<(std::ostream& os, const Natural& num);

        /**
         * @brief Input stream for a Natural number using its base-10
         * representation.
         * 
         * Assumes the stream contains something that can be casted into a
         * `long long` type. It then divides it by 100 continously, storing
         * each division's remainder as a new digit of the Natural number.
         * 
         * @param is The input stream to read from
         * @param num The Natural number object to store the read value
         * @return std::istream& Reference to the input stream after reading
         */
        friend std::istream& operator>>(std::istream& is, Natural& num);

        static Natural divideBy2(const Natural& num);
        static Natural factorial(const Natural& num);
        void multiplyBy100() {digits.add(0, 0);}
        void multiplyBy10();
        //**Greater or equal */
        static int smallestGeqPowerOfBase(const int num, const int base);
        static Natural smallestGeqPowerOfBase(const Natural& num, const Natural& base);
        int size() const {return this->digits.size();}
        static Natural gcd(const Natural& num1, const Natural& num2);
        
        List<unsigned short> getList() const;
        int getNumOfDigits() const;
        void addDigit(unsigned short digit);
        double toDouble() const;
        explicit operator bool() const 
        {
            return this->operator[](0)%2;
        }
};