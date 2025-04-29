#include <iostream>
#include <Windows.h>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

// ������ ������� ��� �������� 2
double exact_solution(double x) {
    return (pow(x, 3) / 2.0) - (x / 2.0);
}

// ������ ����� ����������������� ��������� y' = f(x,y)
double f(double x, double y) {
    return (y / x) + pow(x, 2);
}

// ������������ ����� ������
vector<double> euler_method(double x0, double y0, double b, int N) {
    double h = (b - x0) / N;
    vector<double> x(N + 1), y(N + 1);
    x[0] = x0;
    y[0] = y0;

    for (int i = 1; i <= N; ++i) {
        x[i] = x[i - 1] + h;
        y[i] = y[i - 1] + h * f(x[i - 1], y[i - 1]);
    }

    return y;
}

// ���������������� ����� ������ 1 (���������-���������)
vector<double> modified_euler1(double x0, double y0, double b, int N) {
    double h = (b - x0) / N;
    vector<double> x(N + 1), y(N + 1);
    x[0] = x0;
    y[0] = y0;

    for (int i = 1; i <= N; ++i) {
        x[i] = x[i - 1] + h;
        // ���� ��������
        double y_pred = y[i - 1] + h * f(x[i - 1], y[i - 1]);
        // ���� ���������
        y[i] = y[i - 1] + h * 0.5 * (f(x[i - 1], y[i - 1]) + f(x[i], y_pred));
    }

    return y;
}

// ���������������� ����� ������ 2 (������� �����)
vector<double> modified_euler2(double x0, double y0, double b, int N) {
    double h = (b - x0) / N;
    vector<double> x(N + 1), y(N + 1);
    x[0] = x0;
    y[0] = y0;

    for (int i = 1; i <= N; ++i) {
        x[i] = x[i - 1] + h;
        // ���������� ����������� � ������� �����
        double k1 = f(x[i - 1], y[i - 1]);
        double k2 = f(x[i - 1] + h / 2, y[i - 1] + (h / 2) * k1);
        y[i] = y[i - 1] + h * k2;
    }

    return y;
}

// ���������� ������������������� ����������
double calculate_error(const vector<double>& x, const vector<double>& y_num, double (*exact)(double)) {
    double sum = 0.0;
    int n = x.size();

    for (int i = 0; i < n; ++i) {
        double diff = y_num[i] - exact(x[i]);
        sum += diff * diff;
    }

    return sum;
}

int main() {
    SetConsoleOutputCP(1251);

    double x0 = 1.0;    // ��������� �����
    double y0 = 0.0;    // ��������� �������� y(x0)
    double b = 5.0;     // �������� �����

    vector<int> N_values = { 8, 16, 32, 64 };

    cout << "������������������ ���������� ��� ��������� �������\n";
    cout << "------------------------------------------------------------\n";
    cout << "|   N  |  ������������  | ���������������� 1 | ���������������� 2 |\n";
    cout << "------------------------------------------------------------\n";

    for (int N : N_values) {
        // ������� ����� �� x
        vector<double> x(N + 1);
        double h = (b - x0) / N;
        for (int i = 0; i <= N; ++i) {
            x[i] = x0 + i * h;
        }

        // ��������� ������� ������� ��������
        vector<double> y_euler = euler_method(x0, y0, b, N);
        vector<double> y_mod1 = modified_euler1(x0, y0, b, N);
        vector<double> y_mod2 = modified_euler2(x0, y0, b, N);

        // ��������� ������
        double error_euler = calculate_error(x, y_euler, exact_solution);
        double error_mod1 = calculate_error(x, y_mod1, exact_solution);
        double error_mod2 = calculate_error(x, y_mod2, exact_solution);

        cout << "| " << setw(4) << N << " | "
            << setw(14) << scientific << setprecision(4) << error_euler << " | "
            << setw(18) << error_mod1 << " | "
            << setw(18) << error_mod2 << " |\n";
    }

    cout << "------------------------------------------------------------\n";

    return 0;
}