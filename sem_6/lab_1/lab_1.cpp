#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using std::vector;
using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;

class LinearSystemSolver {
public:
    LinearSystemSolver(vector<double>& A, vector<double>& B)
        : A(A), B(B), N(A.size()) {}

    void solve(vector<double>& y) {
        forwardElimination();
        backwardSubstitution(y);
    }

private:
    vector<double>& A;
    vector<double>& B;
    int N;

    void forwardElimination() {
        for (int i = 0; i < N - 1; ++i) {
            double m = B[i] / A[i];
            A[i + 1] -= m * A[i];
            B[i + 1] -= m * B[i];
        }
    }

    void backwardSubstitution(vector<double>& y) {
        y[N] = B[N - 1] / A[N - 1];

        for (int i = N - 2; i >= 0; --i) {
            y[i + 1] = (B[i] - A[i] * y[N]) / A[i];
        }
    }
};

class EquationSolver {
public:
    EquationSolver(int N, double x_start, double x_end, double a, double b)
        : N(N), x_start(x_start), x_end(x_end), a(a), b(b), h((x_end - x_start) / N) {
        y.resize(N + 1, 0.0);
        A.resize(N - 1, 0.0);
        B.resize(N - 1, 0.0);
    }

    void solve() {
        fillMatrix();
        LinearSystemSolver solver(A, B);
        solver.solve(y);
    }

    void printResults() const {
        cout << fixed << setprecision(6);
        for (int i = 0; i <= N; ++i) {
            double x_i = x_start + i * h;
            cout << "x = " << x_i << ", y = " << y[i] << endl;
        }
    }

private:
    int N;
    double x_start, x_end, a, b, h;
    vector<double> y, A, B;

    void fillMatrix() {
        for (int i = 1; i < N; ++i) {
            double x_i = x_start + i * h;

            A[i - 1] = -2 * a / (h * h) - (1 + b * x_i * x_i);

            if (i > 1) {
                B[i - 1] += a / (h * h);
            }

            if (i < N - 1) {
                B[i - 1] += a / (h * h);
            }

            B[i - 1] += 1;
        }
    }
};

int main() {
    const short k = 11;
    double a = sin(k);
    double b = cos(k);
    int N = 100;
    double x_start = -1, x_end = 1;

    EquationSolver solver(N, x_start, x_end, a, b);
    solver.solve();
    solver.printResults();

    return 0;
}