#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <clocale>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    ifstream fin("input/input.txt");
    if (!fin.is_open()) {
        cerr << "Ошибка: не удалось открыть файл input/input.txt для чтения." << endl;
        return 1;
    }

    ofstream fout("output/solution.txt");
    if (!fout.is_open()) {
        cerr << "Ошибка: не удалось открыть файл output/solution.txt для записи." << endl;
        return 1;
    }

    int N;
    fin >> N;

    vector<vector<double>> A(N, vector<double>(N + 1));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j <= N; ++j)
            fin >> A[i][j];

    fin.close();

    for (int k = 0; k < N; k++) {
        int maxRow = k;
        for (int i = k + 1; i < N; i++) {
            if (fabs(A[i][k]) > fabs(A[maxRow][k])) {
                maxRow = i;
            }
        }
        for (int j = 0; j <= N; j++) {
            swap(A[k][j], A[maxRow][j]);
        }
        if (fabs(A[k][k]) < 1e-12) {
            fout << "Матрица вырождена или почти вырождена!" << endl;
            return 1;
        }
        for (int i = k + 1; i < N; i++) {
            double factor = A[i][k] / A[k][k];
            for (int j = k; j <= N; j++) {
                A[i][j] -= factor * A[k][j];
            }
        }
    }

    vector<double> x(N);
    for (int i = N - 1; i >= 0; i--) {
        x[i] = A[i][N];
        for (int j = i + 1; j < N; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }

    fout << fixed << setprecision(6);
    fout << "Решение системы:" << endl;
    for (int i = 0; i < N; ++i) {
        fout << "x" << i + 1 << " = " << x[i] << endl;
    }

    fout.close();
    cout << "Решение записано в файл output/solution.txt" << endl;

    return 0;
}