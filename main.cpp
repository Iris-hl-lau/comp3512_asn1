#include <iostream>
#include "matrix.cpp"
#include <fstream>

int main() {
    ifstream read_file;
    read_file.open("connectivity.txt");
    double array[1024];
    double num;
    int index = 0;

    //Read connectivity.txt into an array of doubles.
    if(read_file.is_open()){
        while(!read_file.eof()){
            read_file >> num;
            array[index] = num;
            index++;
        }
    }
    read_file.close();

    //Create a matrix with matrix class constructor
    matrix m(array, index + 1);

    for (int i = 0; i < m.get_c(); i++) {
        double sum;
        for (int j = 0; j < m.get_r(); j++) {
            sum += m.get_value(i, j);
        }
        for (int k = 0; k < m.get_r(); k++) {
            double value = m.get_value(i, k);
            m.set_value(i, k, m.get_value(i, k) / sum);
        }
    }

    return 0;
}