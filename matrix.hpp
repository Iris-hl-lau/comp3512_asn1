//
// Created by Iris L on 2018-10-09.
//

#pragma once
#include <iostream>
using namespace std;

//Declaring class matrix.
class matrix {
protected:
    int r;
    int c;
    int size;
    double** my_matrix;
public:
    matrix();
    explicit matrix(int n);
    matrix(int r, int c);
    explicit matrix(double array[], int n);
    void set_value(int r, int c, double value)const;
    double get_value(int r, int c)const;
    void clear();
    matrix(const matrix& m); //Needed for swapping
    ~matrix();
    friend ostream& operator<<(ostream& os, matrix& m);
    friend bool operator==(const matrix& lhs, const matrix& rhs);
    friend bool operator!=(const matrix& lhs, const matrix& rhs);
    matrix& operator++();
    const matrix operator++(int);
    matrix& operator--();
    const matrix operator--(int);
    friend void swap(matrix& first, matrix& second); //Needed for the assignment operator
    matrix& operator=(matrix m); //Uses the copy and swap idiom
    matrix& operator+=(const matrix& rhs);
    friend matrix operator+(matrix lhs, const matrix& rhs);
    matrix& operator-=(const matrix& rhs);
    friend matrix operator-(matrix lhs, const matrix& rhs);
    matrix& operator*=(const matrix& rhs);
    friend matrix operator*(matrix lhs, const matrix& rhs);
    int get_r();
    int get_c();
    int get_size();
    double** get_my_matrix();
};