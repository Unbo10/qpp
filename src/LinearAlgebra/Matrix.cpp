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

Matrix operator*(const Rational& number, const Matrix& matrix)
{
    if(number == 0) return Matrix(matrix.rows(), matrix.columns());
    Matrix result(matrix);
    if(number == 1) return result;

    for(int i = 0; i < result.rows(); i++)
        result[i] = number*result[i];
    return result;
}

Matrix operator*(const Matrix& m1, const Matrix& m2)
{
    if (m1.columns() != m2.rows())
        throw std::invalid_argument("Multiplication undefined for matrices with incompatible dimensions");

    int rows = m1.rows();
    int cols = m2.columns();
    int inner = m1.columns();

    Matrix result(rows, cols);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            Rational sum = 0;
            for (int k = 0; k < inner; ++k)
            {
                sum = sum + m1[i][k] * m2[k][j];
            }
            result[i][j] = sum;
        }
    }
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

Matrix Matrix::identity(int n)
{
    Matrix result(n ,n);
    Rational uno(1, 1);

    for(int i = 0; i < n; i++)
        result[i][i] = uno;
    
    return result;
}

Matrix Matrix::transpose(const Matrix& matrix)
{
    int rows = matrix.rows(), columns = matrix.columns();
    Matrix result(columns, rows);

    for(int i =  0; i < columns; i ++)
        for(int j = 0; j < rows; j++)
            result[i][j] = matrix[j][i];

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

void printWithoutBrackets(const Matrix& m1)
{
    for(Vector x: m1)
    {
        for(const Rational& number: x)
            std::cout << number << " ";
        std::cout << "\n";
    }
}

void printWithoutBracketsAndFractionForm(const Matrix& m1)
{
    for(Vector x: m1)
    {
        for(const Rational& number: x)
        {
            showFraction(number);
            std:: cout << " ";
        }
        std::cout << "\n";
    }
}