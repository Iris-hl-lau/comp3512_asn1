//
// Created by Iris L on 2018-10-09.
//

#pragma once
#include <iostream>
using namespace std;
class Matrix
{
protected:
    double** matrix;
public:
    Matrix();
    Matrix(int n);
    Matrix(int r, int c);
    Matrix(double array[]);
    void set_value(int r, int c, double value)const;
    double get_value(int r, int c)const;
    void clear();
    ~Matrix();
    friend ostream& operator<<(ostream& os, Matrix& matrix);
};