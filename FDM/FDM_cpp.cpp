#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
using namespace std;

// Funkcja zamieniająca kropkę na przecinek w liczbie zmiennoprzecinkowej
string replaceDot(double value, int precision) {
    string str = to_string(value); // Konwersja liczby na string
    size_t dot_pos = str.find('.'); // Znajdowanie pozycji kropki
    if (dot_pos != string::npos) {
        str[dot_pos] = ','; // Zamiana kropki na przecinek
    }
    // Ograniczenie liczby miejsc po przecinku
    return str.substr(0, dot_pos + 1 + precision);
}

// Funkcja definiująca funkcję E(x)
auto E = [](double x) {
    if (x <= 1.0) {
        return 2.0; // Wartość E(x) dla x <= 1.0
    } else {
        return 10.0 * (2.1 - x); // Wartość E(x) dla x > 1.0
    }
};

// Funkcja generująca siatkę punktów x
vector<double> generateGrid(int N) {
    vector<double> x(N);
    for (int i = 0; i < N; ++i) {
        x[i] = 2.0 * i / (N - 1); // Równomierne rozmieszczenie punktów
    }
    return x;
}

// Funkcja inicjalizująca macierz A i wektor b
void initializeSystem(vector<vector<double>>& A, vector<double>& b, int N, const vector<double>& x, double dx) {
    for (int i = 1; i < N - 1; ++i) {
        double x_mid_left = (x[i] + x[i - 1]) / 2.0; // Środek między x[i-1] a x[i]
        double x_mid_right = (x[i] + x[i + 1]) / 2.0; // Środek między x[i] a x[i+1]
        double E_left = E(x_mid_left); // Wartość E w środku lewego przedziału
        double E_right = E(x_mid_right); // Wartość E w środku prawego przedziału

        // Wypełnianie macierzy A i wektora b
        A[i][i - 1] = E_left / (dx * dx);
        A[i][i] = -(E_left + E_right) / (dx * dx);
        A[i][i + 1] = E_right / (dx * dx);
        b[i] = 1000.0 * sin(M_PI * x[i]); // Źródło termiczne
    }

    // Warunek brzegowy na lewym końcu
    A[0][0] = -1.0 / dx + 2.0;
    A[0][1] = 1.0 / dx;
    b[0] = 20.0;
}

// Funkcja rozwiązująca układ równań liniowych metodą eliminacji Gaussa
vector<double> solveLinearSystem(vector<vector<double>>& A, vector<double>& b, int N) {
    // Eliminacja w przód
    for (int i = 1; i < N; ++i) {
        double factor = A[i][i - 1] / A[i - 1][i - 1];
        A[i][i] -= factor * A[i - 1][i];
        b[i] -= factor * b[i - 1];
    }

    // Podstawienie wstecz
    vector<double> u(N, 0.0);
    u[N - 1] = 20.0; // Warunek brzegowy na prawym końcu
    for (int i = N - 2; i >= 0; --i) {
        u[i] = (b[i] - A[i][i + 1] * u[i + 1]) / A[i][i];
    }

    return u;
}

// Funkcja rozwiązująca problem brzegowy
pair<vector<double>, vector<double>> solve_bvp(int N) {
    vector<double> x = generateGrid(N); // Generowanie siatki
    double dx = x[1] - x[0]; // Krok siatki

    vector<vector<double>> A(N, vector<double>(N, 0.0)); // Macierz A
    vector<double> b(N, 0.0); // Wektor b

    initializeSystem(A, b, N, x, dx); // Inicjalizacja układu równań
    vector<double> u = solveLinearSystem(A, b, N); // Rozwiązanie układu

    return {x, u};
}

// Funkcja zapisująca wyniki do pliku
void saveResultsToFile(const vector<double>& x, const vector<double>& u, const string& filename) {
    ofstream output_file(filename);
    if (output_file.is_open()) {
        output_file << "x\tu_i" << endl; // Nagłówek pliku
        for (int i = 0; i < x.size(); ++i) {
            output_file << replaceDot(x[i], 6) << "\t" << replaceDot(u[i], 6) << endl; // Zapis danych
        }
        output_file.close();
        cout << "\nWyniki zostaly zapisane do pliku " << filename << "\n";
    } else {
        cerr << "Blad: Nie mozna otworzyc pliku " << filename << "\n";
    }
}

int main() {
    int N = 100; // Liczba punktów siatki
    auto [x, u] = solve_bvp(N); // Rozwiązanie problemu brzegowego
    saveResultsToFile(x, u, "results.xls"); // Zapis wyników do pliku
    return 0;
}