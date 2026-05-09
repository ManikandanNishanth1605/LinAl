#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

template <class T>
class Matrix2D
{
public:
    // Constructors
    Matrix2D();                                             // Zero matrix of size (1 x 1)
    Matrix2D(size_t rows, size_t cols);                     // Zero matrix of size (rows, cols)
    Matrix2D(size_t rows, size_t cols, const T *row_major); // For a given row-major flattened matrix, class instance is created
    Matrix2D(const Matrix2D<T> &matrix);                    // Copy constructor
    // Destructor
    ~Matrix2D();
    // Operator overload
    Matrix2D<T> &operator=(const Matrix2D<T> &matrix);      // Copy assignment operator
    T &operator()(size_t i, size_t j); // Fetches value at index (i,j)
    template <class U>
    friend std::ostream &operator<<(std::ostream &os, const Matrix2D<U> &mat); // String overload
    template <class U>
    friend Matrix2D<U> operator+(const Matrix2D<U> &matL, const Matrix2D<U> &matR); // Matrix Addition
    template <class U>
    friend Matrix2D<U> operator*(const Matrix2D<U> &matL, const U &scalar); // Scalar Multiplication
    template <class U>
    friend Matrix2D<U> operator*(const U &scalar, const Matrix2D<U> &matR); // Scalar Multiplication
    template <class U>
    friend Matrix2D<U> operator*(const Matrix2D<U> &matL, const Matrix2D<U> &matR); // Matrix Multiplication
    
    // Member functions
    T getValue(size_t i, size_t j);                                                 // Gets value at index (i,j)
    size_t getRows();                                                               // Gets number of rows
    size_t getCols();                                                               // Gets number of cols
    size_t getSize();                                                               // Gets the size
    bool setValue(size_t i, size_t j, T elementValue);                              // Sets value at index(i,j) to elementValue

private:
    // Class variables
    size_t mRows, mCols, mSize; // Number of rows, cols and size of the matrix
    T *mData;                   // Contains matrix data
};

////////////////////////////--Constructors--//////////////////////////////////

template <class T>
Matrix2D<T>::Matrix2D()
{
    mRows = 1;
    mCols = 1;
    mSize = mRows * mCols;
    mData = new T[mSize];
    mData[0] = 0.0;
}

template <class T>
Matrix2D<T>::Matrix2D(size_t rows, size_t cols)
{
    mRows = rows;
    mCols = cols;
    mSize = mRows * mCols;
    mData = new T[mSize];
    for (size_t i = 0; i < mSize; i++)
    {
        mData[i] = 0.0;
    }
}

template <class T>
Matrix2D<T>::Matrix2D(size_t rows, size_t cols, const T *row_major)
{
    mRows = rows;
    mCols = cols;
    mSize = mRows * mCols;
    mData = new T[mSize];
    for (size_t i = 0; i < mSize; i++)
    {
        mData[i] = row_major[i];
    }
}

template <class T>
Matrix2D<T>::Matrix2D(const Matrix2D<T> &matrix)
{
    mRows = matrix.mRows;
    mCols = matrix.mCols;
    mSize = mRows * mCols;
    mData = new T[mSize];
    for (size_t i = 0; i < mSize; i++)
    {
        mData[i] = matrix.mData[i];
    }
}

////////////////////////////--Destructor--//////////////////////////////////

template <class T>
Matrix2D<T>::~Matrix2D()
{
    if (mData != nullptr)
    {
        delete[] mData;
        mData = nullptr;
    }
}

////////////////////////////--Operator Overloads--//////////////////////////////////

// Copy Assignment Operator
template <class T>
Matrix2D<T> &Matrix2D<T>::operator=(const Matrix2D<T> &matrix)
{
    // Check for self-assignment
    if (this == &matrix)
    {
        return *this;
    }
    // Delete old data
    if (mData != nullptr)
    {
        delete[] mData;
    }
    // Copy member variables
    mRows = matrix.mRows;
    mCols = matrix.mCols;
    mSize = mRows * mCols;
    // Allocate and copy data
    mData = new T[mSize];
    for (size_t i = 0; i < mSize; i++)
    {
        mData[i] = matrix.mData[i];
    }
    return *this;
}

// Indexing
template <class T>
T &Matrix2D<T>::operator()(size_t i, size_t j)
{
    return mData[j + i * mCols];
}

template <class T>
std::ostream &operator<<(std::ostream &os, const Matrix2D<T> &mat)
{
    size_t rows = mat.mRows;
    size_t cols = mat.mCols;
    size_t size = mat.mSize;
    for (size_t i = 0; i < mat.mRows; i++)
    {
        for (size_t j = 0; j < mat.mCols; j++)
        {
            os << mat.mData[j + i * mat.mCols] << " ";
        }
        os << "\n";
    }
    return os;
}

// Matrix addition
template <class T>
Matrix2D<T> operator+(const Matrix2D<T> &matL, const Matrix2D<T> &matR)
{
    if ((matL.mRows != matR.mRows) || (matL.mCols != matR.mCols))
    {
        throw std::runtime_error("Size incompatible. Addition not possible.");
    }
    size_t rows = matL.mRows;
    size_t cols = matL.mCols;
    size_t size = matL.mSize;
    T *resultArray = new T[size];
    for (size_t i = 0; i < matL.mSize; i++)
    {
        resultArray[i] = matL.mData[i] + matR.mData[i];
    }
    Matrix2D<T> resultMat(rows, cols, resultArray);
    delete[] resultArray;
    resultArray = nullptr;
    return resultMat;
}

// Scalar multiplication
template <class T>
Matrix2D<T> operator*(const Matrix2D<T> &matL, const T &scalar)
{
    size_t rows = matL.mRows;
    size_t cols = matL.mCols;
    size_t size = matL.mSize;
    T *resultArray = new T[size];
    for (size_t i = 0; i < matL.mSize; i++)
    {
        resultArray[i] = scalar * matL.mData[i];
    }
    Matrix2D<T> resultMat(rows, cols, resultArray);
    delete[] resultArray;
    resultArray = nullptr;
    return resultMat;
}

// Scalar multiplication
template <class T>
Matrix2D<T> operator*(const T &scalar, const Matrix2D<T> &matR)
{
    size_t rows = matR.mRows;
    size_t cols = matR.mCols;
    size_t size = matR.mSize;
    T *resultArray = new T[size];
    for (size_t i = 0; i < matR.mSize; i++)
    {
        resultArray[i] = scalar * matR.mData[i];
    }
    Matrix2D<T> resultMat(rows, cols, resultArray);
    delete[] resultArray;
    resultArray = nullptr;
    return resultMat;
}

// Matrix multiplication
template <class T>
Matrix2D<T> operator*(const Matrix2D<T> &matL, const Matrix2D<T> &matR)
{
    if (matL.mCols != matR.mRows)
    {
        throw std::runtime_error("Size incompatible. Addition not possible.");
    }
    size_t rrows = matL.mRows;
    size_t rcols = matR.mCols;
    size_t size = rrows * rcols;
    size_t temp = matL.mCols;
    T *resultArray = new T[size];
    for (size_t i = 0; i < rrows; i++)
    {
        for (size_t j = 0; j < rcols; j++)
        {
            size_t resInd = j + i * rcols; // (i,j) for result
            resultArray[resInd] = 0;
            for (size_t k = 0; k < temp; k++)
            {
                size_t lInd = k + i * matL.mCols; // (i,k) for matL
                size_t rInd = j + k * matR.mCols; // (k,j) for matR
                resultArray[resInd] += matL.mData[lInd] * matR.mData[rInd];
            }
        }
    }
    Matrix2D<T> resultMat(rrows, rcols, resultArray);
    delete[] resultArray;
    resultArray = nullptr;
    return resultMat;
}

////////////////////////////--Member Functions--//////////////////////////////////

template <class T>
size_t Matrix2D<T>::getRows()
{
    return mRows;
}

template <class T>
size_t Matrix2D<T>::getCols()
{
    return mCols;
}

template <class T>
size_t Matrix2D<T>::getSize()
{
    return mSize;
}

#endif