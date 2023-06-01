#include <mpi.h>
#include "utils.h"
using namespace std;

double partialNorm(int k, int N, double** A) {
    double s, norm = 0.0;
    for (int i = 0; i < k; ++i) {
        s = 0.0;
        for (int j = 0; j < N; ++j)
            s += fabs(A[i][j]);
        if (s > norm)
            norm = s;
    }
    return  norm;
}

int main (int argc, char *argv[]) {
    int rank, size, N = 8, master = 0, numRow;
    double **A, **p_A;

    double t0 = 0.0, tf = 0.0;
    
    // MPI initialization
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status stat;

    // number of rows per process
    int k = N / size;

    // Auxiliar arrays
    int *sendcounts, *displs;

    // Matrix A is generated in the master process
    if (rank == master) {
        // Initialize matrix A
        A = genSqMatrix(N);
        fillMatrix(N, A);
        printSqaureMatrix(N, A);

        // Create auxiliars
        sendcounts = createArray(size);
        displs = createArray(size);
        // Set auxiliar values
        for (int j = 0; j < size; j++) {
            // number of elements in partial matrix
            sendcounts[j] = k*N;
            // displacement value
            displs[j] = j*k*N;
        }
    }

    // Create matrix for the partial A
    p_A = genMatrix(k, N);

    // Scatters the matrix parts through all the processes
    MPI_Scatterv(&A[0][0], sendcounts, displs, MPI_DOUBLE, &p_A[0][0], k*N, MPI_DOUBLE, master, MPI_COMM_WORLD);
    
    cout << "Rank: " << rank << "\n";
    //printMatrix(k, N, p_A);

    // Calculate Norm
    double norm, local_norm = 0;
    local_norm = partialNorm(k, N, p_A);

    // Reduce all local norms into the global norm
    MPI_Reduce(&local_norm, &norm, 1, MPI_DOUBLE, MPI_MAX, master, MPI_COMM_WORLD);

    // Print the result
    if (rank == master) {
        cout << "\nResult = " << norm << endl;
    }

    // Free memory
    if (!rank) freeMatrix(A);
    freeMatrix(p_A);
    
    MPI_Finalize();
}