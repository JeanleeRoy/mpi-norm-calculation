#include <mpi.h>
#include "utils.h"
using namespace std;

double partialNorm(int k, int N, double** A) {
    double s, norm;
    norm = fabs(A[0][0]);
    for(int i = 0; i < k; ++i) {
        s = 0.0;
        for(int j = 0; j < N; ++j)
            s += fabs(A[i][j]);
            if(s > norm)
                norm=s; 
    }
    return  norm;
}

int main (int argc, char *argv[]) {
    int rank, size, numRow;
    int N = 8;
    int master = 0;
    double t0 = 0.0, tf = 0.0;
    
    // Declare matrix A
    double **A;
     
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status stat; // 'stat' variable MPI with status info
    
    // number of rows per process
    int k = N / size;

    if (rank == master) {
        // Initialize A
        A = genSquareMatrix(N);
        fillMatrix(N, A);
        printSqaureMatrix(N, A);
        
        // send k rows to each process
        for (int proc = 1; proc < size; proc++) {   // O(n * (n/P) * P) ~ O(n^2)
            for (int row = 0; row < k; row++) {
                numRow = (proc * k) + row;
                // Send row to the process
                MPI_Send(&A[numRow][0], N, MPI_DOUBLE, proc, 0, MPI_COMM_WORLD);
            }
        }
        // Do partial norm for master rows
        double norm = partialNorm(k, N, A); // O(n * (n/P)) ~ O(n^2/P)
        double pnorm;
        // Receive partial results
        for (int proc = 1; proc < size; proc++) {   // O(P* n/P) ~  O(n) 
            for (int row = 0; row < k; row++) {
                MPI_Recv(&pnorm, 1, MPI_DOUBLE, proc, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                if (pnorm > norm) norm = pnorm;
            }
        }
        // Show Result
        cout << "\nResult: " << norm << endl;

        // Free Memory
        deleteMatrix(N, A);
    }
    
    // Other process
    else { 
        // Initialize
        A = generateDimension(k, N);

        // Receive k rows from master
        for (int i = 0; i < k; i++) {  // O(n/P * n) ~ O(n^2/P)
            cout << "Rank: " << rank << " recibiendo fila numero: " << (rank * k) + i << "\n";
            MPI_Recv(&A[i][0], N, MPI_DOUBLE, master, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);   // receive row
        }
        //printMatrix(k, N, A); 
        
        // Do partial norm
        double pNorm = partialNorm(k, N, A);    // O(n/P * n) ~ O(n^2/P)
        
        // Send partial norm to master process
        for (int row = 0; row < k; k++) {    // O(n/P)
            MPI_Send(&pNorm, 1, MPI_DOUBLE, master, 0, MPI_COMM_WORLD);
        }

        deleteMatrix(k, A);
    }
    
    MPI_Finalize();
}