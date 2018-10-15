//
// Created by Iris L on 2018-10-09.
//

#pragma once
#include <iostream>
using namespace std;

//Declaring class Matrix.
class Matrix {
protected:
    int r;
    int c;
    int size;
    double** matrix;
public:
    Matrix();
    explicit Matrix(int n);
    Matrix(int r, int c);
    explicit Matrix(double array[]);
    void set_value(int r, int c, double value)const;
    double get_value(int r, int c)const;
    void clear();
    Matrix(const Matrix& m); //Needed for swapping
    ~Matrix();
    friend ostream& operator<<(ostream& os, Matrix& m);
    friend bool operator==(const Matrix& lhs, const Matrix& rhs);
    friend bool operator!=(const Matrix& lhs, const Matrix& rhs);
    Matrix& operator++();
    const Matrix operator++(int);
    Matrix& operator--();
    const Matrix operator--(int);
    friend void swap(Matrix& first, Matrix& second); //Needed for the assignment operator
    Matrix& operator=(Matrix m); //Uses the copy and swap idiom
    Matrix& operator+=(const Matrix& rhs);
    friend Matrix operator+(Matrix lhs, const Matrix& rhs);
    Matrix& operator-=(const Matrix& rhs);
    friend Matrix operator-(Matrix lhs, const Matrix& rhs);
    Matrix& operator*=(const Matrix& rhs);
    friend Matrix operator*(Matrix lhs, const Matrix& rhs);
};