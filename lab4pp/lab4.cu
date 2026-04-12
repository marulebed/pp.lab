#include <iostream>
#include <vector>
#include <cuda_runtime.h>

using namespace std;


global void multiply(double* A, double* B, double* C, int N) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < N && col < N) {
        double sum = 0;
        for (int k = 0; k < N; k++) {
            sum += A[row * N + k] * B[k * N + col];
        }
        C[row * N + col] = sum;
    }
}

int main() {
    int N = 400;

    vector<double> A(N * N), B(N * N), C(N * N);

    for (int i = 0; i < N * N; i++) {
        A[i] = rand() % 10;
        B[i] = rand() % 10;
    }

    double *d_A, *d_B, *d_C;

    cudaMalloc(&d_A, N * N * sizeof(double));
    cudaMalloc(&d_B, N * N * sizeof(double));
    cudaMalloc(&d_C, N * N * sizeof(double));

    cudaMemcpy(d_A, A.data(), N * N * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B.data(), N * N * sizeof(double), cudaMemcpyHostToDevice);

    dim3 block(16, 16);
    dim3 grid((N + 15) / 16, (N + 15) / 16);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);

    multiply<<<grid, block>>>(d_A, d_B, d_C, N);

    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);

    cudaMemcpy(C.data(), d_C, N * N * sizeof(double), cudaMemcpyDeviceToHost);

    cout << "Time: " << milliseconds << " ms" << endl;

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}