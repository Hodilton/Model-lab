#include "./Matrix/include/Matrix.h"
using namespace matrix;

#include <Windows.h>
#include <string>
#include <map>
#include <functional>
#include <cmath>

const double NEWTON_EPS = 1e-8;
const double ITERATION_EPS = 1e-6;
const double DESCENT_EPS = 1e-6;
const double SOLUTION_CHECK_EPS = 1e-5;

// Структура для хранения решения
struct SolutionResult {
    Matrix<double> solution;
    size_t iterations;
    bool success;
    std::string message;
};

using SolverFunction = std::function<SolutionResult(
    Matrix<double>&, double, int)>;

// Вариант 2
struct Function {
    static double f1(double x1, double x2) {
        return std::cos(x1 - 1) + x2 - 0.5;
    }

    static double f2(double x1, double x2) {
        return std::sin(x1) + 2 * x2 - 2;
    }

    static double df1dx1(double x1, double x2) {
        return -std::sin(x1 - 1);
    }

    static double df1dx2(double x1, double x2) {
        return 1.0;
    }

    static double df2dx1(double x1, double x2) {
        return std::cos(x1);
    }

    static double df2dx2(double x1, double x2) {
        return 2.0;
    }
};

// Функция для проверки решения
bool checkSolution(Matrix<double>& solution) {
    double f1 = Function::f1(solution(0, 0), solution(1, 0));
    double f2 = Function::f2(solution(0, 0), solution(1, 0));
    return (std::abs(f1) < SOLUTION_CHECK_EPS)
        && (std::abs(f2) < SOLUTION_CHECK_EPS);
}

SolutionResult newtonMethod(Matrix<double> x0, double eps, size_t maxIter = 1000) {
    Matrix<double> x1(2, 1);
    Matrix<double> f(2, 1);
    Matrix<double> J(2, 2);

    size_t iter = 0;
    while (iter < maxIter) {
        // Вычисляем вектор функций и матрицу Якоби
        f(0, 0) = Function::f1(x0(0, 0), x0(1, 0));
        f(1, 0) = Function::f2(x0(0, 0), x0(1, 0));

        J(0, 0) = Function::df1dx1(x0(0, 0), x0(1, 0));
        J(0, 1) = Function::df1dx2(x0(0, 0), x0(1, 0));
        J(1, 0) = Function::df2dx1(x0(0, 0), x0(1, 0));
        J(1, 1) = Function::df2dx2(x0(0, 0), x0(1, 0));

        // Проверка на вырожденность Якобиана
        if (std::fabs(J.math->determinant()) < eps) {
            return { x0, iter, false, "Якобиан имеет нулевой детерминант." };
        }

        Matrix<double> J_inv = J.math->inverse();
        x1 = x0 - J_inv * f;

        // Проверка условия сходимости
        if ((std::fabs(x1(0, 0) - x0(0, 0)) < eps &&
            (std::fabs(x1(1, 0) - x0(1, 0)) < eps)))
        {
            if (checkSolution(x1)) {
                return { x1, iter + 1, true, "" };
            }
            return { x1, iter + 1, false, "Метод сошелся, но решение не удовлетворяет системе." };
        }

        x0 = x1;
        iter++;
    }

    return { x0, iter, false, "Достигнуто максимальное число итераций." };
}

SolutionResult simpleIterationMethod(Matrix<double> x0, double eps, size_t maxIter = 1000) {
    Matrix<double> x1(2, 1);
    size_t iter = 0;

    while (iter < maxIter) {
        // Итерационное преобразование
        //x1(0, 0) = x0(0, 0) - 0.1 * Function::f1(x0(0, 0), x0(1, 0));
        //x1(1, 0) = x0(1, 0) - 0.1 * Function::f2(x0(0, 0), x0(1, 0));
        x1(0, 0) = acos(0.5 - x0(1, 0)) + 1;
        x1(1, 0) = (2.0 - sin(x0(0, 0))) / 2.0;

        // Проверка условия сходимости
        if ((std::fabs(x1(0, 0) - x0(0, 0)) < eps &&
            (std::fabs(x1(1, 0) - x0(1, 0)) < eps)))
        {
            if (checkSolution(x1)) {
                return { x1, iter + 1, true, "" };
            }
            return { x1, iter + 1, false, "Метод сошелся, но решение не удовлетворяет системе" };
        }

        x0 = x1;
        iter++;
    }

    return { x0, iter, false, "Достигнуто максимальное число итераций" };
}

// Вспомогательные функции для метода наискорейшего спуска
// Ф(x1, x2) = f(x1)^2 + f(x2)^2 = 0
double F(double x1, double x2) {
    double f1 = Function::f1(x1, x2);
    double f2 = Function::f2(x1, x2);
    return f1 * f1 + f2 * f2;
}

// Вычисляем градиент функции
Matrix<double> grad(double x1, double x2) {
    double f1 = Function::f1(x1, x2);
    double f2 = Function::f2(x1, x2);

    double df1dx1 = Function::df1dx1(x1, x2);
    double df1dx2 = Function::df1dx2(x1, x2);
    double df2dx1 = Function::df2dx1(x1, x2);
    double df2dx2 = Function::df2dx2(x1, x2);

    Matrix<double> grad(2, 1);
    grad(0, 0) = 2 * f1 * df1dx1 + 2 * f2 * df2dx1;
    grad(1, 0) = 2 * f1 * df1dx2 + 2 * f2 * df2dx2;

    return grad;
}

/*
Метод lineSearch реализует поиск оптимального шага (α) для метода наискорейшего спуска,
  используя условие Армихо (одно из условий достаточного убывания).
    1. Начинаем с начального значения шага alpha = 1.0
    2. На каждой итерации проверяем, выполняется ли условие:
        F(x - α∇F) ≤ F(x) - c·α·||∇F||²
            где:
                F - целевая функция (сумма квадратов невязок)
                c - константа (обычно 0.1-0.5)
                ∇F - градиент функции F

    Если условие не выполняется, уменьшает шаг: alpha *= rho (где rho обычно 0.5-0.9)
    Возвращает первый шаг α, удовлетворяющий условию
*/
double lineSearch(const Matrix<double>& x, const Matrix<double>& grad) {
    double alpha = 1.0; // / начальный шаг
    double c = 0.5; // параметр условия Армихо (0 < c < 1)
    double rho = 0.9; // коэффициент уменьшения шага (0 < rho < 1)
    double F_current = F(x(0, 0), x(1, 0));
    // Норма градиента в квадрате (сумма квадратов элементов)
    double grad_norm_sq = grad(0, 0) * grad(0, 0) + grad(1, 0) * grad(1, 0);

    while (true) {
        Matrix<double> x_new(2, 1);
        x_new(0, 0) = x(0, 0) - alpha * grad(0, 0);
        x_new(1, 0) = x(1, 0) - alpha * grad(1, 0);

        double F_new = F(x_new(0, 0), x_new(1, 0));

        // Проверка условия достаточного убывания
        if (F_new <= F_current - c * alpha * grad_norm_sq) {
            return alpha;
        }

        // Уменьшаем шаг, если условие не выполняется
        alpha *= rho;

        if (alpha < 1e-10) {
            return alpha;
        }
    }
}

// Метод наискорейшего спуска
SolutionResult steepestDescentMethod(Matrix<double> x0, double eps, size_t maxIter = 1000) {
    Matrix<double> x1(2, 1);
    Matrix<double> gradF(2, 1);
    size_t iter = 0;

    while (iter < maxIter) {
        gradF = grad(x0(0, 0), x0(1, 0));
        double alpha = lineSearch(x0, gradF);

        x1(0, 0) = x0(0, 0) - alpha * gradF(0, 0);
        x1(1, 0) = x0(1, 0) - alpha * gradF(1, 0);

        // Проверка условия сходимости
        if (std::fabs(x1(0, 0) - x0(0, 0)) < eps &&
            std::fabs(x1(1, 0) - x0(1, 0)) < eps) {
            if (checkSolution(x1)) {
                return { x1, ++iter, true, "" };
            }
            return { x1, ++iter, false, "Метод сошелся, но решение не удовлетворяет системе" };
        }

        x0 = x1;
        iter++;
    }

    return { x0, iter, false, "Достигнуто максимальное число итераций" };
}

void solve(const std::string& methodName, SolverFunction solver, Matrix<double>& x0, double eps) {
    std::cout << "--- " << methodName << " ---\n";
    std::cout << "Начальное приближение: (" << x0(0, 0) << ", " << x0(1, 0) << ")\n";

    SolutionResult result = solver(x0, eps, 1000);

    if (result.success) {
        std::cout << "Решение найдено за " << result.iterations << " итераций:\n";
        std::cout << "x1 = " << result.solution(0, 0) << "\n";
        std::cout << "x2 = " << result.solution(1, 0) << "\n";
    }
    else {
        std::cout << "Ошибка: " << result.message << "\n";
        std::cout << "Последнее приближение: (" << result.solution(0, 0)
            << ", " << result.solution(1, 0) << ")\n";
        std::cout << "Итераций: " << result.iterations << "\n";
    }

    // Проверка решения
    double f1 = Function::f1(result.solution(0, 0), result.solution(1, 0));
    double f2 = Function::f2(result.solution(0, 0), result.solution(1, 0));
    std::cout << "Проверка решения: " 
        << "f1 "
        << ((std::abs(f1) < SOLUTION_CHECK_EPS) ? " = 0, " : "≠ 0, ")
        << "f2 "
        << ((std::abs(f1) < SOLUTION_CHECK_EPS) ? " = 0" : "≠ 0")
        << "\n\n";
}

int main() {
    SetConsoleOutputCP(1251);
    double eps = 1e-7;

    // Определяем начальные приближения для разных корней
    Matrix<double> x0_newton1(2, 1); x0_newton1(0, 0) = -3.0; x0_newton1(1, 0) = 1.0;
    Matrix<double> x0_newton2(2, 1); x0_newton2(0, 0) = -2.0; x0_newton2(1, 0) = 1.5;

    Matrix<double> x0_iter1(2, 1); x0_iter1(0, 0) = -3.0; x0_iter1(1, 0) = 1.0;
    Matrix<double> x0_iter2(2, 1); x0_iter2(0, 0) = -2.0; x0_iter2(1, 0) = 1.5;
    //Matrix<double> x0_iter2(2, 1); x0_iter2(0, 0) = 2.0; x0_iter2(1, 0) = 4.0;

    Matrix<double> x0_descent1(2, 1); x0_descent1(0, 0) = -3.0; x0_descent1(1, 0) = 1.0;
    Matrix<double> x0_descent2(2, 1); x0_descent2(0, 0) = -2.0; x0_descent2(1, 0) = 1.5;

    solve("Метод Ньютона (корень 1)", newtonMethod, x0_newton1, eps);
    solve("Метод Ньютона (корень 2)", newtonMethod, x0_newton2, eps);

    solve("Метод простой итерации (корень 1)", simpleIterationMethod, x0_iter1, eps);
    solve("Метод простой итерации (корень 2)", simpleIterationMethod, x0_iter2, eps);

    solve("Метод наискорейшего спуска (корень 1)", steepestDescentMethod, x0_descent1, eps);
    solve("Метод наискорейшего спуска (корень 2)", steepestDescentMethod, x0_descent2, eps);

    return 0;
}