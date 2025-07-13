#pragma once

#include "Vector.h"

/*
    En esta clase se hace uso de una doble lista para guardar una matriz,
    mas exactamente, una lista de la ya definida clase Vector, se guarda haciendo uso
    de que cada vector representa una fila.
*/

class Matrix: public Iterable<Vector>
{
    private:
        List<Vector> array;
        
    public:
        //***CONSTRUCTORS***

        Matrix(int rows, int columns): array(rows)
        {
            if(rows <= 0 || columns <= 0)
                throw std::invalid_argument("Invalid size to initialize a matrix. If you're trying to create a vector or scalar, use the appropriate class instead.");

            for(int i = 0; i < rows; i++)
                array.add(Vector(columns));
        }

        Matrix(): Matrix(2, 2) {}

        Matrix(const Matrix& other): array(other.rows())
        {
            //!No need for it since rows depends on the array size and by
            //!adding all the elements, row will increase
            // int rows = other.rows();

            for(int i = 0; i < other.rows(); i++)
                array.add(other.array[i]);     
        }

        Matrix(const Vector& array): Matrix(array.size(), 1)
        {
            for(int i = 0; i < array.size(); i++)
                this->operator[](i)[0] = array[i];
        }
        
        //***UTIL METHODS AND ATTRIBUTES***

        Vector& operator[](int row);
        const Vector& operator[](int row) const;
        int columns() const {return array.size() > 0 ? array[0].size() : 0;}
        int rows() const {return array.size();}
        Matrix reshape(int rows, int cols) const;

        //***MATRIX OPERATIONS***
        
        friend Matrix operator+(const Matrix& m1, const Matrix& m2);
        friend Matrix operator-(const Matrix& m1, const Matrix& m2);
        friend Matrix operator*(const Rational& number, const Matrix& matrix);
        friend Matrix operator*(const Matrix& m1, const Matrix& m2);
        List<Matrix> splitIn4();
        static List<Matrix> strassenSubmatrices(const List<Matrix>& m1SubM, const List<Matrix>& m2SubM);
        static Matrix strassenMm(const Matrix& m1, const Matrix& m2);
        friend Matrix operator^(const Matrix& m1, const Natural& number);
        static Matrix scalonadeForm(const Matrix& m1);
        static Matrix identity(int n);
        static Matrix transpose(const Matrix& matrix);
        static Matrix inverse(const Matrix& matrix);
        static Rational det(const Matrix& matrix);

        //***USE CASES***
        /*
            Este es un ejemplo de uso de la clase 
            matrix
        */
        static Rational fibonnacci(const Natural& num)
        {
            if(num == 0 || num == 1)
                return num;

            Matrix fibonnaciMatrix(2, 2);

            fibonnaciMatrix[0][0] = 1;
            fibonnaciMatrix[0][1] = 1;
            fibonnaciMatrix[1][0] = 1;

            return ((fibonnaciMatrix^num)[1][0]);
        }

        //***RANGE-BASED ITERATION COMPATIBILITY***
        Iterator<Vector> begin() const {return array.begin();}
        Iterator<Vector> end() const {return array.end();}

        //***STREAM OPERATIONS***
        friend std::ostream& operator<<(std::ostream& os, const Matrix& m1);
        friend std::istream& operator>>(std::istream& is, Matrix& m);
        friend void printWithoutBrackets(const Matrix& m1);
        friend void printWithoutBracketsAndFractionForm(const Matrix& m1);
};