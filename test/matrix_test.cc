#include <iostream>
#include <random>

#include "matrix.h"

using namespace std;
typedef Matrix2D<double> matD;

int main(){
    // Random number generator
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(1, 10);

    // Matrix array initialization
    int row1 = 3; int col1 = 3;
    int row2 = 3; int col2 = 3;
    int size1 = row1 * col1;
    int size2 = row2 * col2;
    double* mat1 = new double[size1];
    double* mat2 = new double[size2];
    
    // Assigning values
    for (int i = 0 ; i < size1 ; i++){
        mat1[i] = dis(gen)/10.0;
    }
    for (int i = 0 ; i < size2 ; i++){
        mat2[i] = dis(gen)/10.0;
    }

    // Matrix2D class instances
    matD matrix1(row1, col1, mat1);
    cout << "Matrix 1" << endl;
    cout << matrix1 << endl;
    
    matD matrix2(row2, col2, mat2);
    cout << "Matrix 2" << endl;
    cout << matrix2 << endl;
    
    // Matrix multiplication
    matD matrix3 = matrix1 * matrix2;
    cout << "Matrix 3" << endl;
    cout << matrix3 << endl;
    
    // Scalar multiplication
    double scalar = 10.0;
    matrix3 = scalar*matrix3;
    cout << "Matrix 3 after left scalar multiplication" << endl;
    cout << matrix3 << endl;
    
    matrix2 = matrix2*scalar;
    cout << "Matrix 2 after right scalar multiplication" << endl;
    cout << matrix2 << endl;
    
    // Matrix addition
    matD matrix4 = matrix1 + matrix2;
    cout << "Matrix 4 is matrix addition of Matrix 1 and 2" << endl;
    cout << matrix4 << endl;

    // Free memory
    delete[] mat1;
    delete[] mat2;

    return 0;
}