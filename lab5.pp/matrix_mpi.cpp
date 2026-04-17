#include <mpi.h>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int N = 2000; 

    vector<double> A(N * N), B(N * N), C(N * N, 0);

    if (rank == 0) {
        for (int i = 0; i < N * N; i++) {
            A[i] = rand() % 10;
            B[i] = rand() % 10;
        }
    }

    MPI_Bcast(B.data(), N * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    int rows = N / size;
    vector<double> local_A(rows * N);
    vector<double> local_C(rows * N, 0);

    MPI_Scatter(A.data(), rows * N, MPI_DOUBLE,
        local_A.data(), rows * N, MPI_DOUBLE,
        0, MPI_COMM_WORLD);

    double start = MPI_Wtime();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                local_C[i * N + j] += local_A[i * N + k] * B[k * N + j];
            }
        }
    }

    double end = MPI_Wtime();

    MPI_Gather(local_C.data(), rows * N, MPI_DOUBLE,
        C.data(), rows * N, MPI_DOUBLE,
        0, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "Time: " << end - start << " sec" << endl;
    }

    MPI_Finalize();
    return 0;
}