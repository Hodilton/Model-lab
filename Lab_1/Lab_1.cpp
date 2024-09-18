#include <iostream>
#include <unordered_set>
#include <functional>
#include <cmath>
#include <string>

#include "./task_1/Solution_1.h"

const double dx = 1e-6;

// Интерфейс для методов нахождения корней
class RootFindingMethod {
public:
    virtual std::unordered_set<double> findRoots(std::function<double(double)> f, double a, double b) const = 0;
    virtual ~RootFindingMethod() = default;
};

// Метод Ньютона
class NewtonMethod : public RootFindingMethod {
public:
    std::unordered_set<double> findRoots(std::function<double(double)> f, double a, double b) const override {
        std::unordered_set<double> roots;
        double x = a; // Используем 'a' как начальное приближение
        for (int i = 0; i < 1000; ++i) {
            double y = f(x), dy = dif(f, x);
            if (std::abs(y) < dx) {
                roots.insert(round_to(x, 3));
                x += 0.1;
                continue;
            }
            if (dy == 0) break; // предотвращение деления на ноль
            x = x - y / dy;
        }
        return roots;
    }

private:
    double dif(std::function<double(double)> f, double x) const {
        return (f(x + dx) - f(x - dx)) / (2 * dx);
    }

    double round_to(double x, int n) const {
        double pos = std::pow(10, n);
        return std::round(x * pos) / pos;
    }
};

// Метод секущих
class SecantMethod : public RootFindingMethod {
public:
    std::unordered_set<double> findRoots(std::function<double(double)> f, double a, double b) const override {
        std::unordered_set<double> roots;
        double y_a = f(a), y_b = f(b);
        if (y_a * y_b < 0) {
            for (int i = 0; i < 1000; ++i) {
                double x = a - (y_a * (b - a)) / (y_b - y_a);
                double y_x = f(x);
                if (std::abs(y_x) < dx) {
                    roots.insert(round_to(x, 3));
                    x += 0.1;
                    continue;
                }
                a = b;
                b = x;
                y_a = f(a);
                y_b = f(b);
                if (std::abs(y_b) < dx) break;
            }
        }
        return roots;
    }

private:
    double round_to(double x, int n) const {
        double pos = std::pow(10, n);
        return std::round(x * pos) / pos;
    }
};

// Итерационный метод
class IterativeMethod : public RootFindingMethod {
public:
    std::unordered_set<double> findRoots(std::function<double(double)> f, double a, double b) const override {
        std::unordered_set<double> roots;
        double x = a; // Используем 'a' как начальное приближение
        for (int i = 0; i < 1000; ++i) {
            double prev_x = x;
            x -= f(x) / 2;
            if (std::abs(f(x)) < dx) {
                roots.insert(round_to(x, 3));
                x += 0.1;
                continue;
            }
        }
        return roots;
    }

private:
    double round_to(double x, int n) const {
        double pos = std::pow(10, n);
        return std::round(x * pos) / pos;
    }
};

// Класс для работы с функциями и методами
class FunctionSolver {
public:
    FunctionSolver(const std::function<double(double)>& func) : f(func) {}

    std::string solve(const RootFindingMethod& method, double a, double b) const {
        std::unordered_set<double> roots = method.findRoots(f, a, b);
        return str(roots);
    }

private:
    std::function<double(double)> f;

    std::string str(const std::unordered_set<double>& roots) const {
        if (roots.empty()) return "Корни не найдены";
        std::string out;
        int i = 0;
        for (const auto& root : roots) {
            i++;
            out += " x" + std::to_string(i) + " = " + std::to_string(root);
        }
        return out;
    }
};

void solution_2() {
    std::setlocale(LC_ALL, "russian");

    // Пример функций
    std::function<double(double)> f1 = [](double x) { return std::pow(x, 3) - 10 * x - 5; };
    std::function<double(double)> f2 = [](double x) { return std::pow(x, 3) - 10 * x * x - 20; };

    NewtonMethod newton;
    SecantMethod secant;
    IterativeMethod iter;

    FunctionSolver solver1(f1);
    FunctionSolver solver2(f2);

    double for_newton = 3, a = 2, b = 3;

    std::cout << "f1:\n";
    std::cout << "Метод Ньютона: " << solver1.solve(newton, for_newton, b) << "\n";
    std::cout << "Метод секущих: " << solver1.solve(secant, a, b) << "\n";
    std::cout << "Метод итерации: " << solver1.solve(iter, for_newton, b) << "\n\n";

    std::cout << "f2:\n";
    std::cout << "Метод Ньютона: " << solver2.solve(newton, for_newton, b) << "\n";
    std::cout << "Метод секущих: " << solver2.solve(secant, a, b) << "\n";
    std::cout << "Метод итерации: " << solver2.solve(iter, for_newton, b) << "\n";
}



int main() {
    try {
        //task_1::solution();
        solution_2();
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}