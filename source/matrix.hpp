#ifndef MATRIX
#define MATRIX


#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include<random>
#include<numeric>

using namespace std;


class Matrix {
private:
    vector<vector<double>> matrix_;
public:
    //matrix ctor for a homogeneous matrix (all element are equal)
    Matrix() {};
    Matrix(int n, double d) {
        vector<vector<double>> v1;
        for (int i = 0; i < n; i++)
        {
            vector<double> v2;
            for (int j = 0; j < n; j++)
            {
                v2.push_back(d);
            }
            v1.push_back(v2);
        }
        matrix_ = v1;
    }
    //print matrix 
    void print()
    {
        for (auto it = matrix_.begin(); it != matrix_.end(); it++)
        {
            for (auto it1 = (*it).begin(); it1 != (*it).end(); it1++)
            {
                std::cout << *it1 << ", ";
            }
            std::cout << '\n';
        }
    }
    //getter for the ij element
    double get(int i, int j) const
    {
        return (matrix_[i][j]);
    }
    //setter for the ij element
    double& set(int i, int j)
    {
        return (matrix_[i][j]);
    }
    void set(int i, int j, double element)
    {
        matrix_[i][j] = element;
    }
    //size of the matrix
    int size() const {
        return matrix_.size();
    }

    std::vector<double> getRow(int i) {
        return matrix_[i];
    }

    std::vector<std::vector<double>> getVector() {
        return matrix_;
    }
};





#endif