#pragma once
#ifndef MATRIX_H
#define MATRIX_H

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
            int rows = other.rows();

            for(int i = 0; i < rows; i++)
                array.add(other.array[i]);     
        }

        Vector& operator[](int row);
        const Vector& operator[](int row) const;
        int columns() const {return array[0].size();}
        int rows() const {return array.size();}

        friend Matrix operator+(const Matrix& m1, const Matrix& m2);
        friend Matrix operator-(const Matrix& m1, const Matrix& m2);
        friend Matrix operator*(const Rational& number, const Matrix& matrix);
        friend Matrix operator*(const Matrix& m1, const Matrix& m2);
        friend Matrix operator^(const Matrix& m1, const Natural& number);
        static Matrix scalonadeForm(const Matrix& m1);
        static Matrix identity(int n);
        static Matrix transpose(const Matrix& matrix);
        static Matrix inverse(const Matrix& matrix);
        static Rational det(const Matrix& matrix);

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

        Iterator<Vector> begin() const {return array.begin();}
        Iterator<Vector> end() const {return array.end();}

        friend std::ostream& operator<<(std::ostream& os, const Matrix& m1);
        friend void printWithoutBrackets(const Matrix& m1);
        friend void printWithoutBracketsAndFractionForm(const Matrix& m1);
};


#endif