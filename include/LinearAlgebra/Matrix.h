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
            for(int i = 0; i < rows; i++)
                array.add(Vector(columns));
        }

        Matrix(const Matrix& other): array(other.rows())
        {
            int rows = this->rows();
            for(int i = 0; i < rows; i++)
                array.add(other[i]);
        }

        Vector& operator[](int row);
        const Vector& operator[](int row) const;
        int columns() const {return array[0].size();}
        int rows() const {return array.size();}

        friend Matrix operator+(const Matrix& m1, const Matrix& m2);
        friend Matrix operator-(const Matrix& m1, const Matrix& m2);
        static Matrix scalonadeForm(const Matrix& m1);

        Iterator<Vector> begin() const {return array.begin();}
        Iterator<Vector> end() const {return array.end();}

        friend std::ostream& operator<<(std::ostream& os, const Matrix& m1);
};


#endif