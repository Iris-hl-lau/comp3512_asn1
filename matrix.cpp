//
// Created by Iris L on 2018-10-09.
//

#include <cmath>
#include "matrix.hpp"

//Defining class Matrix.

/*Default constructor of Matrix.*/
Matrix::Matrix() {
    r = 0;
    c = 0;
    matrix = new double*[r];
    matrix[0] = new double[c];
    matrix[0][0] = 0.0;
}

/*Constructor of Matrix that creates a matrix of n rows and n columns.*/
Matrix::Matrix(int n) {
    if(n <= 0) {
        throw "Parameters cannot be zero or negative.";
    }
    r = n;
    c = n;
    size = 1;
    matrix = new double*[r];
    matrix[0] = new double[c];
    for(int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            matrix[i][j] = 0.0;
        }
    }
}

/*Constructor of Matrix that creates a matrix of r rows and c columns.*/
Matrix::Matrix(int r, int c) {
    if(r <= 0 || c <= 0) {
        throw "Parameters cannot be zero or negative.";
    }
    this->r = r;
    this->c = c;
    size = r * c;
    matrix = new double*[this->r];
    matrix[0] = new double[this->c];
    for(int i = 0; i < this->r; i++) {
        for (int j = 0; j < this->c; j++) {
            matrix[i][j] = 0.0;
        }
    }
}

/*Constructor of Matrix that takes an 1D array; if the number of elements is a perfect
 * square, it creates a relative matrix.*/
Matrix::Matrix(double array[]) {
    int array_size = ((int)sizeof(array)) / sizeof(array[0]);
    int array_sqrt = (int)sqrt((int)sizeof(array) / sizeof(array[0]));
    if(array_size != array_sqrt * array_sqrt){
        throw "Array size is not a perfect square.";
    }

    int index = 0;
    r = array_sqrt;
    c = array_sqrt;
    size = array_size;
    matrix = new double*[r];
    matrix[0] = new double[c];
    for(int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            matrix[i][j] = array[index];
            index++;
        }
    }
}

/*Sets the value in row r and column c of a matrix.*/
void Matrix::set_value(int r, int c, double value)const{
    if(r >= this->r || c >= this->c) {
        throw "Index must not be negative or out of bounds.";
    }
    matrix[r][c] = value;
}

/*Gets the value in row r and column c of a matrix.*/
double Matrix::get_value(int r, int c)const{
    if(r >= this->r || c >= this->c) {
        throw "Index must not be negative or out of bounds.";
    }
    return matrix[r][c];
}

/*Sets all values in a matrix to 0.0.*/
void Matrix::clear(){
    for(int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            set_value(r, c, 0.0);
        }
    }
}

/*Copy constructor of Matrix that copies values of matrix.*/
Matrix::Matrix(const Matrix& matrix_cpy) : r(matrix_cpy.r),
c(matrix_cpy.c), size(matrix_cpy.size) {
    matrix = new double*[r];
    matrix[0] = new double[c];
    for(int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            set_value(i, j, matrix_cpy.matrix[i][j]);
        }
    }
}

/*Matrix destructor.*/
Matrix::~Matrix(){
    delete[] matrix;
}

/*Overloaded output operator.*/
ostream& operator<<(ostream& os, Matrix& m){
    for(int i = 0; i < m.r; i++) {
        for (int j = 0; j < m.c; j++) {
            os << m.get_value(i,j);
        }
        os << "\n";
    }
    return os;
}

/*Overloaded actual comparison operator for matrices that are equal.*/
bool operator==(const Matrix& lhs, const Matrix& rhs){
    double tolerance = 0.05;

    if((lhs.r).equals(rhs.r) && (lhs.c).equals(rhs.c)) {
        for(int i = 0; i < lhs.r; i++) {
            for (int j = 0; j < lhs.c; j++) {
                double difference = abs(lhs.matrix[i][j] - rhs.matrix[i][j]);
                if(difference > tolerance) {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

/*Overloaded actual comparison operator for matrices that are not equal.
 * (non-member function)*/
bool operator!=(const Matrix& lhs, const Matrix& rhs){
    return !operator==(lhs, rhs);
}

/*Overloaded actual increment operator (prefix)
 * that increments values of a matrix by 1.0.*/
Matrix& Matrix::operator++() {
    for(int i = 0; i < this->r; i++) {
        for (int j = 0; j < this->c; j++) {
            set_value(i, j, this->matrix[i][j] += 1.0);
        }
    }
    return *this;
}

/*Overloaded actual increment operator (postfix)
 * that increments values of a matrix by 1.0.*/
const Matrix Matrix::operator++(int){
    Matrix tmp(*this);
    operator++();
    return tmp;
}

/*Overloaded actual decrement operator (prefix)
 * that decrements values of a matrix by 1.0.*/
Matrix& Matrix::operator--(){
    for(int i = 0; i < this->r; i++) {
        for (int j = 0; j < this->c; j++) {
            set_value(i, j, this->matrix[i][j] -= 1.0);
        }
    }
    return *this;
}

/*Overloaded actual decrement operator (postfix)
 * that decrements values of a matrix by 1.0.*/
const Matrix Matrix::operator--(int){
    Matrix tmp(*this);
    operator--();
    return tmp;
}

/*Swaps the instance values of two matrices. (Non-member function)*/
void swap(Matrix& first, Matrix& second) {
    using std::swap;
    swap(first.size, second.size);
    swap(first.r, second.r);
    swap(first.c, second.c);
    swap(first.matrix, second.matrix);
}

/*Overloaded assignment operator.*/
Matrix& Matrix::operator=(Matrix m){
    swap(*this, m);
    return *this;
}

/*Overloaded addition assignment operator.*/
Matrix& Matrix::operator+=(const Matrix& rhs){
    if((this->r).equals(rhs.r) && (this->c).equals(rhs.c)) {
        for(int i = 0; i < this->r; i++) {
            for (int j = 0; j < this->c; j++) {
                this->matrix[i][j] += rhs.matrix[i][j];
            }
        }
    } else {
        throw "Matrices must have the same number of rows and columns.";
    }
    return *this;
}

/*Overloaded addition operator. (Non-member function)*/
Matrix operator+(Matrix lhs, const Matrix& rhs) {
    lhs += rhs;
    return lhs;
}

/*Overloaded subtraction assignment operator.*/
Matrix& Matrix::operator-=(const Matrix& rhs){
    if((this->r).equals(rhs.r) && (this->c).equals(rhs.c)) {
        for(int i = 0; i < this->r; i++) {
            for (int j = 0; j < this->c; j++) {
                this->matrix[i][j] -= rhs.matrix[i][j];
            }
        }
    } else {
        throw "Matrices must have the same number of rows and columns.";
    }
    return *this;
}

/*Overloaded subtraction operator. (Non-member function)*/
Matrix operator-(Matrix lhs, const Matrix& rhs){
    lhs -= rhs;
    return lhs;
}


/*Overloaded multiplication assignment operator.*/
Matrix& Matrix::operator*=(const Matrix& rhs){
    if((this->c).equals(rhs.r)) {
        Matrix tmp(this->r, rhs.c);
        for(int i = 0; i < this->r; i++) {
            for (int j = 0; j < rhs.c; j++) {
                for (int k = 0; k < this->c; k++) {
                    tmp.matrix[i][j] += this->matrix[i][k] * rhs.matrix[k][j];
                }
            }
        }
        this->matrix = tmp.matrix;
    } else {
        throw "Number of columns in the first matrix must "
              "match the number of columns of the second matrix.";
    }
    return *this;
}


/*Overloaded multiplication operator. (Non-member function)*/
Matrix operator*(Matrix lhs, const Matrix& rhs){
    lhs *= rhs;
    return lhs;
}