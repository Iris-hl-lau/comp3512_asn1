//
// Created by Iris L on 2018-10-09.
//

#include <cmath>
#include "matrix.hpp"


Matrix::Matrix() {
   /* matrix = new double*[0];
    matrix[0] = new double[0];*/
   matrix[0][0] = 0.0;
}

Matrix::Matrix(int n) {
    if(n <= 0) {
        throw "Parameters cannot be zero or negative.";
    }
    matrix[n][n];
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0.0;
        }
    }
}

Matrix::Matrix(int r, int c) {
    if(r <= 0 || c <= 0) {
        throw "Parameters cannot be zero or negative.";
    }
    matrix[r][c];
    for(int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            matrix[i][j] = 0.0;
        }
    }
}

Matrix::Matrix(double array[]) {
    if(sqrt(sizeof(matrix)/sizeof(matrix[0]))
        != sqrt(sizeof(matrix)/sizeof(matrix[0])) * sqrt(sizeof(matrix)/sizeof(matrix[0]))){
        throw "Array size is not a perfect square.";
    }
    int size = sqrt(sizeof(matrix)/sizeof(matrix[0]));
    int index;
    matrix[size][size];
    for(int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            index++;
            matrix[i][j] = array[index];
        }
    }
}

void Matrix::set_value(int r, int c, double value)const{
    if(r >= sizeof(matrix)/sizeof(matrix[0]) || c >= sizeof(matrix[0])/sizeof(matrix[0][0])) {
        throw "Index must not be negative or out of bounds.";
    }
    matrix[r][c] = value;
}

double Matrix::get_value(int r, int c)const{
    if(r >= sizeof(matrix)/sizeof(matrix[0]) || c >= sizeof(matrix[0])/sizeof(matrix[0][0])) {
        throw "Index must not be negative or out of bounds.";
    }
    return matrix[r][c];
}

void Matrix::clear(){
    int r = sizeof(matrix)/sizeof(matrix[0]);
    int c = sizeof(matrix[0])/sizeof(matrix[0][0]);
    for(int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            matrix[i][j] = 0.0;
        }
    }
}
Matrix::~Matrix() = default;

ostream& operator<<(ostream& os, Matrix& matrix){
    int r = sizeof(matrix.matrix)/sizeof(matrix.matrix[0]);
    int c = sizeof(matrix.matrix[0])/sizeof(matrix.matrix[0][0]);
    for(int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            os << matrix.matrix[i][j];
        }
        os << "\n";
    }
    return os;
}