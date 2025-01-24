#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
using namespace std;

// Funkcja zamieniająca kropkę na przecinek
string replaceDot(double value, int precision) {
    string str = to_string(value);
    size_t dot_pos = str.find('.');
    if (dot_pos != string::npos) {
        str[dot_pos] = ','; // Zamiana '.' na ','
    }
    return str.substr(0, dot_pos + 1 + precision);
}

// funkcja rozwiązująca problem brzegowy
pair<vector<double>, vector<double>> solve_bvp(int N) {
    vector<double> x(N);
    for (int i = 0; i < N; ++i) {
        x[i] = 2.0 * i / (N - 1);
    }
    double dx = x[1] - x[0];

    vector<double> u(N, 0.0);
    auto E = [](double x) { return x <= 1.0 ? 2.0 : 6.0; };

    vector<vector<double>> A(N, vector<double>(N, 0.0));
    vector<double> b(N, 0.0);

    u[N-1] = 3.0;

    for (int i = 1; i < N-1; ++i) {
        double x_mid_left = (x[i] + x[i-1]) / 2.0;
        double x_mid_right = (x[i] + x[i+1]) / 2.0;
        double E_left = E(x_mid_left);
        double E_right = E(x_mid_right);

        A[i][i-1] = E_left / (dx * dx);
        A[i][i] = -(E_left + E_right) / (dx * dx);
        A[i][i+1] = E_right / (dx * dx);

        b[i] = 1000.0 * sin(M_PI * x[i]);
    }

    A[0][0] = -1.0/dx + 2.0;
    A[0][1] = 1.0/dx;
    b[0] = 10.0;

    for (int i = 1; i < N; ++i) {
        double factor = A[i][i-1] / A[i-1][i-1];
        A[i][i] -= factor * A[i-1][i];
        b[i] -= factor * b[i-1];
    }

    for (int i = N-2; i >= 0; --i) {
        u[i] = (b[i] - A[i][i+1] * u[i+1]) / A[i][i];
    }

    return {x, u};
}

int main() {
    int N = 100;
    auto [x, u] = solve_bvp(N);
    ofstream output_file("results.xls");
    if (output_file.is_open()) {
        output_file << "x\tu_i" << endl; 
        for (int i = 0; i < N; ++i) {
            output_file << replaceDot(x[i], 6) << "\t" << replaceDot(u[i], 6) << endl;
        }
        output_file.close();
        cout << "\nWyniki zostaly zapisane do pliku results.xls\n";
    } else {
        cerr << "Blad: Nie mozna otworzyc pliku results.xls\n";
    }
    return 0;
}