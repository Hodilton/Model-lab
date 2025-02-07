#include "./Matrix/Matrix.h"

#include <iostream>
#include <Windows.h>

constexpr double EPSILON = 1e-8;

bool hasConverged(const std::vector<double>& prevState, const std::vector<double>& currentState, double epsilon) {
    double diff = 0.0;
    for (size_t i = 0; i < prevState.size(); ++i) {
        diff += std::abs(currentState[i] - prevState[i]);
    } return diff < epsilon;
}

int main() {
    SetConsoleOutputCP(1251);

    matrix::Matrix<double> matrix({
        {0.1, 0.1, 0.8},
        {0, 0.3, 0.7},
        {0.6, 0.2, 0.2}
        });

    std::cout << "Матрица: \n" << matrix << std::endl;

    std::vector<double> initialState = { 0.7, 0.2, 0.1 };

    std::cout << "Начальное состояние: ";
    for (double x : initialState) {
        std::cout << x << " ";
    } std::cout << std::endl << std::endl;

    matrix::Matrix<double> currentMatrix = matrix;
    std::vector<double> currentState = initialState;

    unsigned int steps = 0;
    while (true) {
        ++steps;

        currentMatrix *= matrix;

        std::vector<double> nextState(matrix.getRows(), 0.0);
        for (unsigned int i = 0; i < matrix.getRows(); ++i) {
            for (unsigned int j = 0; j < matrix.getCols(); ++j) {
                nextState[i] += currentState[j] * matrix(j, i);
            }
        }

        if (hasConverged(currentState, nextState, EPSILON)) {
            currentState = nextState;
            break;
        }

        currentState = nextState;

        std::cout << "Step " << steps << " : ";
        for (double x : currentState) {
            std::cout << x << " ";
        } std::cout << std::endl;
    }

    std::cout << "\nРешение уравнения дя стационарного состояния: ";
    for (double prob : currentState) {
        std::cout << prob << " ";
    } std::cout << std::endl;

    return 0;
}