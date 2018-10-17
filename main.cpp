#include <iostream>
#include "matrix.cpp"
#include <fstream>

int main() {
    ifstream read_file;
    read_file.open("connectivity.txt");
    double array[1024];
    double num;
    int index = 0;
    double p = 0.85;
    double teleport = 1 - p;
    matrix temp;

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
    matrix g(array, index + 1);

    //Calculating importance for matrix g
    for (int i = 0; i < g.get_c(); i++) {
        double sum = 0;
        //Calculating sum of column
        for (int j = 0; j < g.get_r(); j++) {
            sum += g.get_value(j, i);
        }
        //Scaling column
        for (int k = 0; k < g.get_r(); k++) {
            double value = g.get_value(k, i);
            if(sum != 0) {
                g.set_value(k, i, value / sum);
            } else {
                sum = 1;
                g.set_value(k, i, value / sum);
            }
        }
    }

    //Create matrix of n * n
    matrix q(g.get_r());
    q++; //all values of matrix q are incremented by 1.0

    //Calculating importance for matrix q
    for (int i = 0; i < q.get_c(); i++) {
        double sum = 0;
        for (int j = 0; j < q.get_r(); j++) {
            sum += q.get_value(j, i);
        }
        for (int k = 0; k < q.get_r(); k++) {
            double value = q.get_value(k, i);
            if(sum != 0) {
                q.set_value(k, i, value / sum);
            } else {
                sum = 1;
                q.set_value(k, i, value / sum);
            }
        }
    }

    //Probability click links.
    for (int i = 0; i < g.get_r(); i++) {
        for (int j = 0; j < g.get_c(); j++) {
            g.set_value(i, j, g.get_value(i, j) * p);
        }
    }

    //Probability teleporrt.
    for (int i = 0; i < q.get_r(); i++) {
        for (int j = 0; j < q.get_c(); j++) {
            q.set_value(i, j, q.get_value(i, j) * teleport);
        }
    }

    //Transition matrix.
    matrix m = g + q;

    //Matrix rank.
    matrix rank(m.get_r(), 1);

    //Converging result
    do {
        temp = rank;
        rank = m * rank;
    } while(rank != temp);

    //Calculating sum of rank column
    double sum = 0;
    for (int j = 0; j < rank.get_r(); j++) {
        sum += rank.get_value(j, 0);
    }
    //Scaling rank column
    for (int k = 0; k < rank.get_r(); k++) {
        double value = rank.get_value(k, 0);
        if(sum != 0) {
            rank.set_value(k, 0, value / sum);
        } else {
            sum = 1;
            rank.set_value(k, 0, value / sum);
        }
    }

    cout << "Page A: " << rank.get_value(0,0) * 100 << "%" << endl;
    cout << "Page B: " <<  rank.get_value(1,0) * 100 << "%" << endl;
    cout << "Page C: " <<  rank.get_value(2,0) * 100 << "%" << endl;
    cout << "Page D: " <<  rank.get_value(3,0) * 100 << "%" << endl;

    return 0;
}