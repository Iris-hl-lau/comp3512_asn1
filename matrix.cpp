//
// Created by Iris L on 2018-10-09.
//

#include <cmath>
#include "matrix.hpp"

//Defining class matrix.

/*Default constructor of matrix.*/
matrix::matrix() {
    r = 0;
    c = 0;
    my_matrix = new double*[r];
    my_matrix[0] = new double[c];
    clear();
}

/*Constructor of matrix that creates a matrix of n rows and n columns.*/
matrix::matrix(int n) {
    if(n <= 0) {
        throw invalid_argument("Parameters cannot be zero or negative.");
    }
    r = n;
    c = n;
    size = 1;
    my_matrix = new double*[r];
    my_matrix[0] = new double[c];
    clear();
}

/*Constructor of matrix that creates a matrix of r rows and c columns.*/
matrix::matrix(int r, int c) {
    if(r <= 0 || c <= 0) {
        throw invalid_argument("Parameters cannot be zero or negative.");
    }
    this->r = r;
    this->c = c;
    size = r * c;
    my_matrix = new double*[this->r];
    my_matrix[0] = new double[this->c];
    clear();
}

/*Constructor of matrix that takes an 1D array; if the number of elements is a perfect
 * square, it creates a relative matrix.*/
matrix::matrix(double array[], int n) {
    int array_sqrt = (int)sqrt(n);
    if(n != array_sqrt * array_sqrt){
        throw invalid_argument("Array size is not a perfect square.");
    }

    int index = 0;
    r = array_sqrt;
    c = array_sqrt;
    size = n;
    my_matrix = new double*[r];
    my_matrix[0] = new double[c];
    for(int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            my_matrix[i][j] = array[index];
            index++;
        }
    }
}

/*Sets the value in row r and column c of a matrix.*/
void matrix::set_value(int r, int c, double value)const{
    if(r >= this->r || c >= this->c) {
        throw invalid_argument("Index must not be negative or out of bounds.");
    }
    my_matrix[r][c] = value;
}

/*Gets the value in row r and column c of a matrix.*/
double matrix::get_value(int r, int c)const{
    if(r >= this->r || c >= this->c) {
        throw invalid_argument("Index must not be negative or out of bounds.");
    }
    return my_matrix[r][c];
}

/*Sets all values in a matrix to 0.0.*/
void matrix::clear(){
    for(int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            set_value(r, c, 0.0);
        }
    }
}

/*Copy constructor of matrix that copies values of matrix.*/
matrix::matrix(const matrix& matrix_cpy) : r(matrix_cpy.r),
c(matrix_cpy.c), size(matrix_cpy.size) {
    my_matrix = new double*[r];
    my_matrix[0] = new double[c];
    for(int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            set_value(i, j, matrix_cpy.my_matrix[i][j]);
        }
    }
}

/*matrix destructor.*/
matrix::~matrix(){
    delete[] my_matrix;
}

/*Overloaded output operator.*/
ostream& operator<<(ostream& os, matrix& m){
    for(int i = 0; i < m.r; i++) {
        for (int j = 0; j < m.c; j++) {
            os << m.get_value(i,j);
        }
        os << "\n";
    }
    return os;
}

/*Overloaded actual comparison operator for matrices that are equal.*/
bool operator==(const matrix& lhs, const matrix& rhs){
    double tolerance = 0.05;

    if(lhs.r == rhs.r && lhs.c == rhs.c) {
        for(int i = 0; i < lhs.r; i++) {
            for (int j = 0; j < lhs.c; j++) {
                double difference = abs(lhs.my_matrix[i][j] - rhs.my_matrix[i][j]);
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
bool operator!=(const matrix& lhs, const matrix& rhs){
    return !operator==(lhs, rhs);
}

/*Overloaded actual increment operator (prefix)
 * that increments values of a matrix by 1.0.*/
matrix& matrix::operator++() {
    for(int i = 0; i < this->r; i++) {
        for (int j = 0; j < this->c; j++) {
            set_value(i, j, this->my_matrix[i][j] += 1.0);
        }
    }
    return *this;
}

/*Overloaded actual increment operator (postfix)
 * that increments values of a matrix by 1.0.*/
const matrix matrix::operator++(int){
    matrix tmp(*this);
    operator++();
    return tmp;
}

/*Overloaded actual decrement operator (prefix)
 * that decrements values of a matrix by 1.0.*/
matrix& matrix::operator--(){
    for(int i = 0; i < this->r; i++) {
        for (int j = 0; j < this->c; j++) {
            set_value(i, j, this->my_matrix[i][j] -= 1.0);
        }
    }
    return *this;
}

/*Overloaded actual decrement operator (postfix)
 * that decrements values of a matrix by 1.0.*/
const matrix matrix::operator--(int){
    matrix tmp(*this);
    operator--();
    return tmp;
}

/*Swaps the instance values of two matrices. (Non-member function)*/
void swap(matrix& first, matrix& second) {
    using std::swap;
    swap(first.size, second.size);
    swap(first.r, second.r);
    swap(first.c, second.c);
    swap(first.my_matrix, second.my_matrix);
}

/*Overloaded assignment operator.*/
matrix& matrix::operator=(matrix m){
    swap(*this, m);
    return *this;
}

/*Overloaded addition assignment operator.*/
matrix& matrix::operator+=(const matrix& rhs){
    if(this->r == rhs.r && this->c == rhs.c) {
        for(int i = 0; i < this->r; i++) {
            for (int j = 0; j < this->c; j++) {
                this->my_matrix[i][j] += rhs.my_matrix[i][j];
            }
        }
    } else {
        throw invalid_argument("Matrices must have the same number of rows and columns.");
    }
    return *this;
}

/*Overloaded addition operator. (Non-member function)*/
matrix operator+(matrix lhs, const matrix& rhs) {
    lhs += rhs;
    return lhs;
}

/*Overloaded subtraction assignment operator.*/
matrix& matrix::operator-=(const matrix& rhs){
    if(this->r == rhs.r && this->c == rhs.c) {
        for(int i = 0; i < this->r; i++) {
            for (int j = 0; j < this->c; j++) {
                this->my_matrix[i][j] -= rhs.my_matrix[i][j];
            }
        }
    } else {
        throw invalid_argument("Matrices must have the same number of rows and columns.");
    }
    return *this;
}

/*Overloaded subtraction operator. (Non-member function)*/
matrix operator-(matrix lhs, const matrix& rhs){
    lhs -= rhs;
    return lhs;
}


/*Overloaded multiplication assignment operator.*/
matrix& matrix::operator*=(const matrix& rhs){
    if(this->c == rhs.r) {
        matrix tmp(this->r, rhs.c);
        for(int i = 0; i < this->r; i++) {
            for (int j = 0; j < rhs.c; j++) {
                for (int k = 0; k < this->c; k++) {
                    tmp.my_matrix[i][j] += this->my_matrix[i][k] * rhs.my_matrix[k][j];
                }
            }
        }
        this->my_matrix = tmp.my_matrix;
    } else {
        throw invalid_argument("Number of columns in the first matrix must "
              "match the number of columns of the second matrix.");
    }
    return *this;
}


/*Overloaded multiplication operator. (Non-member function)*/
matrix operator*(matrix lhs, const matrix& rhs){
    lhs *= rhs;
    return lhs;
}

/*Accessor for rows.*/
int matrix::get_r() {
    return r;
}

/*Accessor for columns.*/
int matrix::get_c() {
    return c;
}
