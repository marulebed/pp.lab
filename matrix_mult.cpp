#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

int main() {
    ifstream f1("A.txt");
    ifstream f2("B.txt");

    int n;
    f1 >> n;
    f2 >> n;

    vector<vector<double>> A(n, vector<double>(n));
    vector<vector<double>> B(n, vector<double>(n));
    vector<vector<double>> C(n, vector<double>(n, 0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            f1 >> A[i][j];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            f2 >> B[i][j];

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> duration = end - start;

    ofstream out("result.txt");

    out << n << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            out << C[i][j] << " ";
        out << endl;
    }

    cout << "Matrix size: " << n << "x" << n << endl;
    cout << "Operations: " << n * n * n << endl;
    cout << "Time: " << duration.count() << " seconds" << endl;

    return 0;
}