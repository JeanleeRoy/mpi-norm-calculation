#include <omp.h>
#include <iostream>

using namespace std;

int main() {
    int ic, i, n = 1000000;
    #pragma omp parallel private (ic) saherd
    {
        ic = 0;
        #pragma omp for 
        for (i = 0; i < n; i++) {
            ic += 1;
        }
        #pragma omp critical
        {
            i += ic;
        } 
    }
    printf("Contador = %d\n", ic);
    return (0);
}