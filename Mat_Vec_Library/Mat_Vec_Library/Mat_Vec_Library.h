#pragma once
#ifndef MAT_VEC_LIBRARY
#define MAT_VEC_LIBRARY

#include <stdio.h>
#include <fstream> // for file access
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <cmath>
#include <winnt.h>

using namespace std;
using std::vector;
using std::tuple;

class Matrix {
  
private:
    unsigned m_rowSize;
    unsigned m_colSize;
    vector<vector<double> > m_matrix;
    static float m,k,l,e,t;
public:
    Matrix(unsigned rowSize, unsigned colSize, float initial);
    Matrix(const char*); ///if from txt file
    Matrix(const Matrix&);
    ~Matrix();

    // Matrix Operations
    Matrix operator+(Matrix&);
    Matrix operator-(Matrix&);
    Matrix operator*(Matrix&);
    Matrix transpose();

    void matrix_x_vector(int y[m], float x[k][l], float A[e][t]); /// x is the multiplication matrix, y is the multiplication vetor, A is the resulted matrix. 
    void vector_x_matrix(int y[m], float x[k][l], float A[e][t]);
   
    // Scalar Operations
    Matrix operator+(float);
    Matrix operator-(float);
    Matrix operator*(float);
    Matrix operator/(float);

    // Aesthetic Methods
    double& operator()(const unsigned&, const unsigned&);
    void print() const; /// you might need to delete this
    unsigned getRows() const;
    unsigned getCols() const;

    // Power Iteration
    tuple<Matrix, double, int> powerIter(unsigned, double);

    // Deflation
    Matrix deflation(Matrix&, double&);
};

class vectorClass {

    // arr is the integer pointer 
  // which stores the address of our vector 
    int* arr;

    // capacity is the total storage 
    // capacity of the vector 
    int capacity;

    // current is the number of elements 
    // currently present in the vector 
    float current;


public:
    // Default constructor to initialise 
    // an initial capacity of 1 element and 
    // allocating storage using dynamic allocation 
    vectorClass()
    {
        arr = new int[1];
        capacity = 1;
        current = 0;
    }
    // Function to add an element at the last 
    void push(float data);
    // function to add element at any index 
    void push(float data, int index);
    // function to extract element at any index 
    int get(int index);
    // function to delete last element 
    void pop();
    // function to get size of the vector 
    int size();
    // function to get capacity of the vector 
    int getcapacity();
    // function to print array elements 
    void print();
};
#endif 
