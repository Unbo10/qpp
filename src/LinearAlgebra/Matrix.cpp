#include "../../include/LinearAlgebra/Matrix.h"

//***UTIL METHODS***

Vector& Matrix::operator[](int row)
{
    return this->array[row];
}

const Vector& Matrix::operator[](int row) const
{
    return this->array[row];
}

Matrix Matrix::reshape(int rows, int cols) const
{
    if((rows == 0) || (cols == 0))
    {
        std::cout << "Warning: Asking for a matrix of 0 x n or n x 0. Returning a 1 x 1 empty matrix\n";
        return Matrix(1, 1);
    }

    if((rows < 0) || (cols < 0))
        throw std::invalid_argument("Rows and columns must be positive.");
    
    Matrix reshaped(*this);

    //*Trim rows
    if(rows < this->rows())
    {
        int rowsToRemove = this->rows() - rows;
        for(int i = 0; i < rowsToRemove; i++)
        {
            reshaped.array.pop(reshaped.array.getSize() - 1);
        }
    }
    //*Append cols - original.columns() zeros to each row (vector)
    else if(this->columns() < cols)
    {
        int zerosToAdd = cols - this->columns();
        for(Vector& vector : reshaped.array)
        {
            for(int i = 0; i < zerosToAdd; i++)
                vector.appendComponent(Rational(0));
        }
    }
    
    //*Trim columns
    if(cols < this->columns())
    {
        int colsToRemove = this->columns() - cols;
        std::cout << "Cols to remove" << colsToRemove << "\n";
        std::cout << reshaped << "\n";
        for(Vector& v : reshaped.array)
        {
            for(int i = 0; i < colsToRemove; i++)
            {
                v.removeComponent();
            }
        }
    }
    //*Append rows - original.rows() rows to the array of reshaped
    else if(this->rows() < rows){
        int newRows = rows - this->rows();
        std::cout << "New rows: " << newRows << "\n";
        for(int i = 0; i < newRows; i++){
            std::cout << i << "\n";
            Vector v(reshaped.columns()); // Create a new vector for each iteration
            reshaped.array.add(v);
        }
    }

    return reshaped;
}

//***MATRIX OPERATIONS***

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

Matrix Matrix::operator-() const
{
    Matrix negated(*this);
    for(Vector& v : negated.array)
        v = -v;

    return negated;
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
            for (int k = 0; k < inner; ++k)
                result[i][j] = result[i][j] + (m1[i][k] * m2[k][j]);

        }
    }
    return result;
}

//*Top-left -> Top-right -> Bottom-left -> Bottom-right
List<Matrix> Matrix::splitIn4()
{
    if((this->columns() % 2 != 0) || (this->rows() % 2 != 0) || (this->columns() != this->rows()))
    {
        std::cout << this->columns() << ", " << this->rows() << "\n";
        throw std::invalid_argument("Matrix isn't square and/or it has a number of rows and/or columns that are not divisible by 2");
    }

    List<Matrix> subMatrices(4);
    int halfSize = this->columns() / 2;
    for(int i = 0; i < 4; i++)
    {
        subMatrices.add(Matrix(halfSize, halfSize), i);
    }

    //*Travel rows
    for(int i = 0; i < halfSize; i++)
    {
        //*Travel columns
        for(int j = 0; j < halfSize; j++)
        {
            subMatrices[0].array[i][j] = this->array[i][j];
            subMatrices[1].array[i][j] = this->array[i][j + halfSize];
            subMatrices[2].array[i][j] = this->array[i + halfSize][j];
            subMatrices[3].array[i][j] = this->array[i + halfSize][j + halfSize];
        }
    }

    return subMatrices;
}

List<Matrix> Matrix::splitIn9()
{
    if((this->columns() % 3 != 0) || (this->rows() % 3 != 0) || (this->columns() != this->rows()))
    {
        std::cout << this->columns() << ", " << this->rows() << "\n";
        throw std::invalid_argument("Matrix isn't square and/or it has a number of rows and/or columns that are not divisible by 2");
    }

    List<Matrix> subMatrices(9);
    int thirdSize = this->columns() / 3;
    for(int i = 0; i < 9; i++)
    {
        subMatrices.add(Matrix(thirdSize, thirdSize), i);
    }

    //*Travel rows
    for(int i = 0; i < thirdSize; i++)
    {
        //*Travel columns
        for(int j = 0; j < thirdSize; j++)
        {
            subMatrices[0].array[i][j] = this->array[i][j];
            subMatrices[1].array[i][j] = this->array[i][j + thirdSize];
            subMatrices[2].array[i][j] = this->array[i][j + 2*thirdSize];
            
            subMatrices[3].array[i][j] = this->array[i + thirdSize][j];
            subMatrices[4].array[i][j] = this->array[i + thirdSize][j + thirdSize];
            subMatrices[5].array[i][j] = this->array[i + thirdSize][j + 2*thirdSize];
            
            subMatrices[6].array[i][j] = this->array[i + 2*thirdSize][j];
            subMatrices[7].array[i][j] = this->array[i + 2*thirdSize][j + thirdSize];
            subMatrices[8].array[i][j] = this->array[i + 2*thirdSize][j + 2*thirdSize];
        }
    }

    return subMatrices;
}

List<Matrix> Matrix::strassenSubmatrices(const List<Matrix>& m1SubM, const List<Matrix>& m2SubM)
{
    //* [[A0, A1],    [[B0, B1],
    //*  [A2, A3]]     [B2, B3]]

    List<Matrix> subMatrices(7);
    int size = m1SubM[0].columns();
    for(int i = 0; i < 7; i++)
    {
        subMatrices.add(Matrix(size, size));
    }

    //*M1 = A0*(B1-B3)
    subMatrices[0] = strassenMm(m1SubM[0], (m2SubM[1] - m2SubM[3]));
    //*M2 = (A0+A1)*B3
    subMatrices[1] = strassenMm((m1SubM[0] + m1SubM[1]), m2SubM[3]);
    //*M3 = (A2+A3)*B0
    subMatrices[2] = strassenMm((m1SubM[2] + m1SubM[3]), m2SubM[0]);
    //*M4 = A3*(B2-B0)
    subMatrices[3] = strassenMm(m1SubM[3], (m2SubM[2] - m2SubM[0]));
    //*M5 = (A0+A3)*(B0+B3)
    subMatrices[4] = strassenMm((m1SubM[0] + m1SubM[3]), (m2SubM[0] + m2SubM[3]));
    //*M6 = (A1-A3)*(B2+B3)
    subMatrices[5] = strassenMm((m1SubM[1] - m1SubM[3]), (m2SubM[2] + m2SubM[3]));
    //*M7 = (A0-A2)*(B0+B1)
    subMatrices[6] = strassenMm((m1SubM[0] - m1SubM[2]), (m2SubM[0] + m2SubM[1]));
    
    return subMatrices;
}

List<Matrix> Matrix::ladermanSubmatrices(const List<Matrix>& m1SubM, const List<Matrix>& m2SubM)
{
    //* [[A0, A1, A2],    [[B0, B1, B2],
    //*  [A3, A4, A5],     [B3, B4, B5]
    //*  [A6, A7, A8]],    [B6, B7, B8]]

    List<Matrix> subMatrices(23);
    int size = m1SubM[0].columns();
    for(int i = 0; i < 23; i++)
    {
        subMatrices.add(Matrix(size, size));
    }

    //*M1  = (A0 + A1 + A2 - A3 - A4 - A7 - A8) * B4
    subMatrices[0] = ladermanMm((m1SubM[0] + m1SubM[1] + m1SubM[2] - m1SubM[3] - m1SubM[4] - m1SubM[7] - m1SubM[8]), m2SubM[4]);
    
    //*M2  = (A0 - A3) * (-B1 + B4)
    subMatrices[1] = ladermanMm((m1SubM[0] - m1SubM[3]), (-m2SubM[1] + m2SubM[4]));
    
    //*M3  = A4 * (-B0 + B1 + B3 - B4 - B5 + B8)
    subMatrices[2] = ladermanMm(m1SubM[4], (-m2SubM[0] + m2SubM[1] + m2SubM[3] - m2SubM[4] - m2SubM[5] + m2SubM[8]));
    
    //*M4  = (-A0 + A3 + A4) * (B0 - B1 + B4)
    subMatrices[3] = ladermanMm((-m1SubM[0] + m1SubM[3] + m1SubM[4]), (m2SubM[0] - m2SubM[1] + m2SubM[4]));
    
    //*M5  = (A3 + A4) * (-B0 + B1)
    subMatrices[4] = ladermanMm((m1SubM[3] + m1SubM[4]), (-m2SubM[0] + m2SubM[1]));
    
    //*M6  = A0 * B0
    subMatrices[5] = ladermanMm(m1SubM[0], m2SubM[0]);
    
    //*M7  = (-A0 + A6 + A7) * (B0 - B2 + B5)
    subMatrices[6] = ladermanMm((-m1SubM[0] + m1SubM[6] + m1SubM[7]), (m2SubM[0] - m2SubM[2] + m2SubM[5]));
    
    //*M8  = (-A0 + A6) * (B0 - B5)
    subMatrices[7] = ladermanMm((-m1SubM[0] + m1SubM[6]), (m2SubM[0] - m2SubM[5]));
    
    //*M9  = (A6 + A7) * (-B0 + B2)
    subMatrices[8] = ladermanMm((m1SubM[6] + m1SubM[7]), (-m2SubM[0] + m2SubM[2]));
    
    //*M10 = (A0 + A1 + A2 - A4 - A5 - A6 - A7) * B6
    subMatrices[9] = ladermanMm((m1SubM[0] + m1SubM[1] + m1SubM[2] - m1SubM[4] - m1SubM[5] - m1SubM[6] - m1SubM[7]), m2SubM[6]);
    
    //*M11 = A7 * (-B0 + B2 + B3 - B4 - B5 - B6 + B7)
    subMatrices[10] = ladermanMm(m1SubM[7], (-m2SubM[0] + m2SubM[2] + m2SubM[3] - m2SubM[4] - m2SubM[5] - m2SubM[6] + m2SubM[7]));
    
    //*M12 = (-A2 + A7 + A8) * (B4 + B6 - B7)
    subMatrices[11] = ladermanMm((-m1SubM[2] + m1SubM[7] + m1SubM[8]), (m2SubM[4] + m2SubM[6] - m2SubM[7]));
    
    //*M13 = (A2 - A8) * (B4 - B7)
    subMatrices[12] = ladermanMm((m1SubM[2] - m1SubM[8]), (m2SubM[4] - m2SubM[7]));
    
    //*M14 = A2 * B6
    subMatrices[13] = ladermanMm(m1SubM[2], m2SubM[6]);
    
    //*M15 = (A7 + A8) * (-B6 + B7)
    subMatrices[14] = ladermanMm((m1SubM[7] + m1SubM[8]), (-m2SubM[6] + m2SubM[7]));
    
    //*M16 = (-A2 + A4 + A5) * (B5 + B6 - B8)
    subMatrices[15] = ladermanMm((-m1SubM[2] + m1SubM[4] + m1SubM[5]), (m2SubM[5] + m2SubM[6] - m2SubM[8]));
    
    //*M17 = (A2 - A5) * (B5 - B8)
    subMatrices[16] = ladermanMm((m1SubM[2] - m1SubM[5]), (m2SubM[5] - m2SubM[8]));
    
    //*M18 = (A4 + A5) * (-B6 + B8)
    subMatrices[17] = ladermanMm((m1SubM[4] + m1SubM[5]), (-m2SubM[6] + m2SubM[8]));
    
    //*M19 = A1 * B3
    subMatrices[18] = ladermanMm(m1SubM[1], m2SubM[3]);
    
    //*M20 = A5 * B7
    subMatrices[19] = ladermanMm(m1SubM[5], m2SubM[7]);
    
    //*M21 = A3 * B2
    subMatrices[20] = ladermanMm(m1SubM[3], m2SubM[2]);
    
    //*M22 = A6 * B1
    subMatrices[21] = ladermanMm(m1SubM[6], m2SubM[1]);
    
    //*M23 = A8 * B8
    subMatrices[22] = ladermanMm(m1SubM[8], m2SubM[8]);

    return subMatrices;
}

Matrix Matrix::strassenMm(const Matrix& matrix1, const Matrix& matrix2)
{
    //! Reshape could have a boolean to indicate it is already a power of 2 (which happens right after the first iteration)
    //!Must check still if the input is compatible

    if(matrix1.columns() != matrix2.rows())
        throw std::invalid_argument("Multiplication undefined for matrices with incompatible dimensions (the number of columns of the first one must be equal to the number of rows of the second one)");
    else if((matrix1.columns() < 1) || (matrix1.rows() < 1) || (matrix2.columns() < 0) || (matrix2.rows() < 1))
        throw std::invalid_argument("At least one of the matrix has no rows and/or columns");
    //*In case both are 2 x 2 matrices
    if((matrix1.rows() == 2) && (matrix1.columns() == 2) && (matrix2.rows() == 2) && (matrix2.columns() == 2))
        return matrix1 * matrix2;
    //*In case at least one of the two is a scalar
    else if(((matrix1.rows() == 1) && (matrix1.columns() == 1)) || ((matrix2.rows() == 1) || (matrix2.columns())))
        return matrix1 * matrix2;
    
    //*Reshaping to be square and have a size that is a power of 2
    int greatestCols = std::max(matrix1.columns(), matrix2.columns());
    int newSize = Natural::smallestGeqPowerOfBase(greatestCols, 2);
    // std::cout << "new size: " << newSize << "\n";
    // std::cout << "Matrix 1:\n";
    // std::cout << matrix1 << "\n";
    // std::cout << "Matrix 2:\n";
    // std::cout << matrix2 << "\n";
    // std::cout << "Reshaping...\n";
    Matrix m1(matrix1);
    m1 = m1.reshape(newSize, newSize);
    // std::cout << "Matrix 1:\n";
    // std::cout << m1 << "\n";
    Matrix m2(matrix2);
    m2 = m2.reshape(newSize, newSize);
    // std::cout << "Matrix 2:\n";
    // std::cout << m2 << "\n";

    //*Split in 4
    List<Matrix> m1SubMatrices = m1.splitIn4();
    List<Matrix> m2SubMatrices = m2.splitIn4();

    //*Get Strassen submatrices
    List<Matrix> subMatrices = strassenSubmatrices(m1SubMatrices, m2SubMatrices);

    //*Fit the resulting matrices
    Matrix mm(newSize, newSize);
    //*C0 = M4 + M3 - M1 + M5
    Matrix C0 = subMatrices[4] + subMatrices[3] - subMatrices[1] + subMatrices[5];
    //*C1 = M0 + M1
    Matrix C1 = subMatrices[0] + subMatrices[1];
    //*C2 = M2 + M3
    Matrix C2 = subMatrices[2] + subMatrices[3];
    //*C3 = M4 + M0 - M2 - M6
    Matrix C3 = subMatrices[4] + subMatrices[0] - subMatrices[2] - subMatrices[6];
    
    for (int i = 0; i < newSize/2; i++) {
        for (int j = 0; j < newSize/2; j++) {
            mm[i][j] = C0[i][j];
            mm[i][j + newSize/2] = C1[i][j];
            mm[i + newSize/2][j] = C2[i][j];
            mm[i + newSize/2][j + newSize/2] = C3[i][j];
        }
    }

    mm = mm.reshape(matrix1.rows(), matrix2.columns());

    return mm;
}

Matrix Matrix::ladermanMm(const Matrix& matrix1, const Matrix& matrix2)
{
    if(matrix1.columns() != matrix2.rows())
        throw std::invalid_argument("Multiplication undefined for matrices with incompatible dimensions (the number of columns of the first one must be equal to the number of rows of the second one)");

    if(matrix1.columns() != matrix2.rows())
        throw std::invalid_argument("Multiplication undefined for matrices with incompatible dimensions (the number of columns of the first one must be equal to the number of rows of the second one)");
    else if((matrix1.columns() < 1) || (matrix1.rows() < 1) || (matrix2.columns() < 0) || (matrix2.rows() < 1))
        throw std::invalid_argument("At least one of the matrix has no rows and/or columns");
    //*In case at least one of the two is a scalar
    else if(((matrix1.rows() == 1) && (matrix1.columns() == 1)) || ((matrix2.rows() == 1) || (matrix2.columns())))
        return matrix1 * matrix2;

    //*Reshaping to be square and have a size that is a power of 3
    int greatestCols = std::max(matrix1.columns(), matrix2.columns());
    int newSize = Natural::smallestGeqPowerOfBase(greatestCols, 3);
    // std::cout << "new size: " << newSize << "\n";
    // std::cout << "Matrix 1:\n";
    // std::cout << matrix1 << "\n";
    // std::cout << "Matrix 2:\n";
    // std::cout << matrix2 << "\n";
    // std::cout << "Reshaping...\n";
    Matrix m1(matrix1);
    m1 = m1.reshape(newSize, newSize);
    // std::cout << "Matrix 1:\n";
    // std::cout << m1 << "\n";
    Matrix m2(matrix2);
    m2 = m2.reshape(newSize, newSize);
    // std::cout << "Matrix 2:\n";
    // std::cout << m2 << "\n";

    //*Split in 9
    List<Matrix> m1SubMatrices = m1.splitIn9();
    List<Matrix> m2SubMatrices = m2.splitIn9();

    //*Get the aiding submatrices according to Larsen's algorithm
    List<Matrix> subMatrices = Matrix::ladermanSubmatrices(m1SubMatrices, m2SubMatrices);

    //*Calculate the resulting matrix
    //*C1 = M6 + M14 + M19
    Matrix C1 = subMatrices[5] + subMatrices[13] + subMatrices[18];
    //*C2 = M1 + M4 + M5 + M6 + M12 + M14 + M15
    Matrix C2 = subMatrices[0] + subMatrices[3] + subMatrices[4] + subMatrices[5] + subMatrices[11] + subMatrices[13] + subMatrices[14];
    //*C3 = M6 + M7 + M9 + M10 + M14 + M16 + M18
    Matrix C3 = subMatrices[5] + subMatrices[6] + subMatrices[8] + subMatrices[9] + subMatrices[13] + subMatrices[15] + subMatrices[17];
    //*C4 = M2 + M3 + M4 + M6 + M14 + M16 + M17
    Matrix C4 = subMatrices[1] + subMatrices[2] + subMatrices[3] + subMatrices[5] + subMatrices[13] + subMatrices[15] + subMatrices[16];
    //*C5 = M2 + M4 + M5 + M6 + M20
    Matrix C5 = subMatrices[1] + subMatrices[3] + subMatrices[4] + subMatrices[5] + subMatrices[19];
    //*C6 = M14 + M16 + M17 + M18 + M21
    Matrix C6 = subMatrices[13] + subMatrices[15] + subMatrices[16] + subMatrices[17] + subMatrices[20];
    //*C7 = M6 + M7 + M8 + M11 + M12 + M13 + M14
    Matrix C7 = subMatrices[5] + subMatrices[6] + subMatrices[7] + subMatrices[10] + subMatrices[11] + subMatrices[12] + subMatrices[13];
    //*C8 = M12 + M13 + M14 + M15 + M22
    Matrix C8 = subMatrices[11] + subMatrices[12] + subMatrices[13] + subMatrices[14] + subMatrices[21];
    //*C9 = M6 + M7 + M8 + M9 + M23
    Matrix C9 = subMatrices[5] + subMatrices[6] + subMatrices[7] + subMatrices[8] + subMatrices[22];

    //*Fit the matrices in the result of the multiplication
    Matrix mm(newSize, newSize);
    int thirdSize = newSize / 2;
    for(int i = 0; i < thirdSize; i++)
    {
        //*Travel columns
        for(int j = 0; j < thirdSize; j++)
        {
            mm.array[i][j] = C1.array[i][j];
            mm.array[i][j + thirdSize] = C2.array[i][j];
            mm.array[i][j + 2*thirdSize] = C3.array[i][j];
            
            mm.array[i + thirdSize][j] = C4.array[i][j];
            mm.array[i + thirdSize][j + thirdSize] = C5.array[i][j];
            mm.array[i + thirdSize][j + 2*thirdSize] = C6.array[i][j];
            
            mm.array[i + 2*thirdSize][j] = C7.array[i][j];
            mm.array[i + 2*thirdSize][j + thirdSize] = C8.array[i][j];
            mm.array[i + 2*thirdSize][j + 2*thirdSize] = C9.array[i][j];
        }
    }

    mm = mm.reshape(matrix1.rows(), matrix2.columns());

    return mm;
}

Matrix operator^(const Matrix& m1, const Natural& number)
{
    if(m1.rows() != m1.columns())
        throw std::invalid_argument("This matrix can't be used to do a power");
        
    Natural exp(number);
    Matrix base(m1);
    Matrix result = Matrix::identity(m1.rows());

    while(exp > 0)
    {
        if(exp[0]%2 == 1)
            result = result*base;

        base = base*base;
        exp = Natural::divideBy2(exp);
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

Matrix Matrix::inverse(const Matrix& matrix)
{
    if(matrix.rows() != matrix.columns())
        throw std::invalid_argument("A matrix must be square to have inverse");

    Matrix result(matrix), inden = Matrix::identity(matrix.rows());
    
    int rows = result.rows();
    int columns = result.columns();
    int currentRow = 0;

    for(int i = 0; i < columns; i++)
    {
        int toFindNoCero = currentRow;
        while(toFindNoCero < rows && result[toFindNoCero][i] == 0)
            toFindNoCero++;

        if(toFindNoCero == rows) 
            throw std::invalid_argument("This matrix don't have a inverse, have a column of ceros");

        if(toFindNoCero != currentRow)
        {
            Vector temp = result[toFindNoCero];
            result[toFindNoCero] = result[currentRow];
            result[currentRow] = temp;
            temp = inden[toFindNoCero];
            inden[toFindNoCero] = inden[currentRow];
            inden[currentRow] = temp;
        }
        
        for(int j = currentRow + 1; j < rows; j++)
        {
            Rational factor = result[j][i]/ result[currentRow][i];
            if(factor != 0) 
            {
                result[j] = result[j] - factor * result[currentRow];

                inden[j] = inden[j] - factor * inden[currentRow];
            }
                
        }

        currentRow++;
    }
            
    for(int i = columns - 1; i >= 0; i--)
    {
        Rational pivot = result[i][i];
        if (pivot == 0)
            throw std::invalid_argument("This matrix don't have a inverse, the determinant is cero");
        
        result[i] = result[i] / pivot;
        inden[i] = inden[i] / pivot;

        for(int j = 0; j < i; j++)
        {
            Rational factor = result[j][i];
            result[j] = result[j] - factor * result[i];
            inden[j] = inden[j] - factor * inden[i];
        }
    }

    return inden;
}

Rational Matrix::det(const Matrix& matrix)
{
    int rows = matrix.rows();
    int columns = matrix.columns();

    if(rows != columns)
        throw std::invalid_argument("This matrix don't be square");

    Matrix result(matrix);
    Rational det = 1;
    
    bool sign = true;
    int currentRow = 0;

    for(int i = 0; i < columns; i++)
    {
        int toFindNoCero = currentRow;
        while(toFindNoCero < rows && result[toFindNoCero][i] == 0)
            toFindNoCero++;

        if(toFindNoCero == rows) 
            return 0;

        if(toFindNoCero != currentRow)
        {
            Vector temp = result[toFindNoCero];
            result[toFindNoCero] = result[currentRow];
            result[currentRow] = temp;
            sign = !sign;
        }
        
        for(int j = currentRow + 1; j < rows; j++)
        {
            Rational factor = result[j][i]/ result[currentRow][i];
            if(factor != 0) 
                result[j] = result[j] - factor * result[currentRow];
        }
        det = det * result[i][i];

        currentRow++;
    }

    if(!sign)
        det.setSign(!det.getSign());

    return det;
}

//***COMPARISON OPERATIONS***

bool operator==(const Matrix& m1, const Matrix& m2)
{
    if((m1.columns() != m2.columns()) || (m1.rows() != m2.rows()))
        return false;
    
    for(int i = 0; i < m1.rows(); i++)
    {
        if(m1.array[i] != m2.array[i])
            return false;
    }

    return true;
}

//***USE CASES***

Rational Matrix::fibonnacci(const Natural& num)
{
    if(num == 0 || num == 1)
        return num;

    Matrix fibonnaciMatrix(2, 2);

    fibonnaciMatrix[0][0] = 1;
    fibonnaciMatrix[0][1] = 1;
    fibonnaciMatrix[1][0] = 1;

    return ((fibonnaciMatrix^num)[1][0]);
}

std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
    int rows = m.rows();
    os << "[";
    for(int i = 0; i < rows; i++)
        os << m[i] << ((i != rows - 1)? ",\n" : "");
    os << "]";

    return os;
}

std::istream& operator>>(std::istream& is, Matrix& m)
{
    m.array.clear();
    int rows;
    is >> rows;

    is.ignore(); //*Ignore newline after entering rows

    Vector v;
    for(int i = 0; i < rows; i++)
    {
        std::string line;
        std::getline(is, line);

        std::istringstream iss(line);
        Vector v;
        iss >> v; //*Each line is read as a vector
              
        m.array.add(v, i); 
    }

    return is;
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