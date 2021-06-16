#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <iostream>
using namespace std;

double** generateDimension(int rows, int cols) {
    if (rows < 1) return nullptr; 
    double** A = new double*[rows];
    for (int i = 0; i < rows; i++) {
        A[i] = new double[cols];
    }
    return A;
}

double** genSquareMatrix(int N) {
    return generateDimension(N, N);
}

void fillMatrix(int N, double** A) {
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++)
        A[i][j] = i;
    }
}

void printMatrix(int rows, int cols, double** A) {
    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}

void printSqaureMatrix(int N, double** A) {
    printMatrix(N, N, A);
}

void deleteMatrix(int rows, double** A) {
    for (int i = 0; i < rows; i++) {
        delete A[i];
    }
    delete[] A;
}

#endif //UTILS_H