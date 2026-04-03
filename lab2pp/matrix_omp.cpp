#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>

using namespace std;

int main() {
    int n;
    cout << "Enter matrix size: ";
    cin >> n;

    int threads;
    cout << "Enter number of threads (1, 2, 4, 8): ";
    cin >> threads;

    omp_set_num_threads(threads);

    vector<vector<double>> A(n, vector<double>(n));
    vector<vector<double>> B(n, vector<double>(n));
    vector<vector<double>> C(n, vector<double>(n, 0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            A[i][j] = 1;
            B[i][j] = 2;
        }

    auto start = chrono::high_resolution_clock::now();

    
#pragma omp parallel for
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "Threads: " << threads << endl;
    cout << "Time: " << duration.count() << " sec" << endl;

    return 0;
}