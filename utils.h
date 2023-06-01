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

void **createMatrix(int rows, int cols, int size) {
    void **p= (void **) malloc(rows*cols*size + rows*sizeof(void *));
    char *c=  (char*) (p+rows);
    for(int i = 0; i < rows; ++i)
        p[i]= (void *) (c+i*cols*size);
    return p;
}

double** genSqMatrix(int N) {
    return (double**) createMatrix(N, N, sizeof(double));
}

double** genMatrix(int rows, int cols) {
    return (double**) createMatrix(rows, cols, sizeof(double));
}

int* createArray(int N) {
    int* a = (int*)malloc(N * sizeof(int));
    return a;
}

void fillMatrix(int N, double** A) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
        A[i][j] = i;
    }
}

void printMatrix(int rows, int cols, double** A) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            cout << A[i][j] << " ";
        cout << endl;
    }
}

void printSqaureMatrix(int N, double** A) {
    printMatrix(N, N, A);
}

void freeMatrix(double** A) {
    //free((void *)A[0]);
    free((void *)A);
}

void deleteMatrix(int rows, double** A) {
    for (int i = 0; i < rows; i++) {
        delete[] A[i];
    }
    delete[] A;
}

#endif //UTILS_H