#include <iostream>
#include <random>

#include "matrix.h"

using namespace std;
typedef Matrix2D<double> matD;


void printMatrix(double* mat, int row, int col){
    int index = 0;
    for (int i = 0 ; i < row ; i++){
        for (int j = 0 ; j < col ; j++){
            index = j + i * col;
            cout << mat[index] << " ";
        }
        cout << endl;
    }
}

int main(){
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(1, 10);

    int row1 = 3; int col1 = 3;
    int row2 = 3; int col2 = 3;
    int size1 = row1 * col1;
    int size2 = row2 * col2;
    double* mat1 = new double[size1];
    double* mat2 = new double[size2];
    
    for (int i = 0 ; i < size1 ; i++){
        mat1[i] = dis(gen)/10.0;
    }
    for (int i = 0 ; i < size2 ; i++){
        mat2[i] = dis(gen)/10.0;
    }

    matD matrix1(row1, col1, mat1);
    matD matrix2(row2, col2, mat2);
    matD matrix3 = matrix1 * matrix2;
    
    
    // Log
    cout << "Matrix 1" << endl;
    cout << matrix1 << endl;
    cout << "Matrix 2" << endl;
    cout << matrix2 << endl;
    cout << "Matrix 3" << endl;
    cout << matrix3 << endl;
    
    double scalar = 10.0;
    matrix3 = scalar*matrix3;
    cout << "Matrix 3 after left scalar multiplication" << endl;
    cout << matrix3 << endl;
    
    matrix2 = matrix2*scalar;
    cout << "Matrix 2 after right scalar multiplication" << endl;
    cout << matrix2 << endl;
    
    Matrix2D<double> matrix4 = matrix1 + matrix2;
    cout << "Matrix 4" << endl;
    cout << matrix4 << endl;

    // Free memory
    delete[] mat1;
    delete[] mat2;

    return 0;
}