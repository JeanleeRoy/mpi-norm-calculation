#include "utils.h"

const int N = 8;

double  infNorm(double** A) {
    int i,j;
    double s, norm;
    norm=fabs(A[0][0]);
    for(int i=0; i<N; i++) {
        s=0.0;
        for (int j=0; j<N; j++)
            s+=fabs(A[i][j]);
            if(s>norm)
                norm=s; 
    }
    return  norm;
}

int main() {
    cout << "Gen matrix\n";
    double** A;
    A = genSqMatrix(N);
    //printSqaureMatrix(N, A);
    cout << "Fill matrix\n";
    fillMatrix(N, A);
    cout << "Print matrix\n";
    printSqaureMatrix(N, A);

    cout << "\nResult: " << infNorm(A) << endl;

    freeMatrix(A);
}