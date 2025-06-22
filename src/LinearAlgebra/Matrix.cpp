#include "../../include/LinearAlgebra/Matrix.h"

Vector& Matrix::operator[](int row)
{
    return this->array[row];
}

const Vector& Matrix::operator[](int row) const
{
    return this->array[row];
}

Matrix operator+(const Matrix& m1, const Matrix& m2)
{
    if(m1.rows() != m2.rows())
        throw std::invalid_argument("The size of the rows must be the same");
    if(m1.columns() != m2.columns())
        throw std::invalid_argument("The size of the columns must be the same");

    Matrix result(m1.rows(), m2.columns());

    for(int i = 0; i < result.rows(); i++)
        result[i] = m1[i]+m2[i];

    return result;
}

Matrix operator-(const Matrix& m1, const Matrix& m2)
{
    if(m1.rows() != m2.rows())
        throw std::invalid_argument("The size of the rows must be the same");
    if(m1.columns() != m2.columns())
        throw std::invalid_argument("The size of the columns must be the same");

    Matrix result(m1.rows(), m2.columns());

    for(int i = 0; i < result.rows(); i++)
        result[i] = m1[i]-m2[i];

    return result;
}


Matrix Matrix::scalonadeForm(const Matrix& m1)
{
    Matrix result(m1);
    
    int rows = result.rows();
    int columns = result.columns();
    int currentRow = 0;

    for(int i = 0; i < columns; i++)
    {
        int toFindNoCero = currentRow;
        while(toFindNoCero < rows && result[toFindNoCero][i] == 0)
            toFindNoCero++;

        if(toFindNoCero == rows) continue;
        if(toFindNoCero != currentRow)
        {
            Vector temp = result[toFindNoCero];
            result[toFindNoCero] = result[currentRow];
            result[currentRow] = temp;
        }
        
        for(int j = currentRow + 1; j < rows; j++)
        {
            Rational factor = result[j][i]/ result[currentRow][i];
            if(factor != 0) 
                result[j] = result[j] - factor * result[currentRow];
        }

        currentRow++;
    }

    return result;
}


std::ostream& operator<<(std::ostream& os, const Matrix& m1)
{
    int rows = m1.rows();
    os << "[";
    for(int i = 0; i < rows; i++)
        os << m1[i] << ((i != rows - 1)? ",\n" : "");
    os << "]";

    return os;
}