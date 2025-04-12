#include "./methods/LeftRectangleMethod.h"
#include "./methods/MiddleRectangleMethod.h"
#include "./methods/RightRectangleMethod.h"
#include "./methods/SimpsonMethod.h"
#include "./methods/TrapezoidMethod.h"

#include "iostream"
#include "iomanip"
#include <Windows.h>
#include <cmath>
#include <numbers>
#include <functional>
#include <string>
#include <map>

class Function {
public:
    static double fx(double x, double p) {
        return (std::pow(x, p) + std::pow(x, -p)) / (1.0 + std::pow(x, 2));
    }

    static double I_T(double p) {
        return std::numbers::pi / (2.0 * std::cos((p * std::numbers::pi) / 2.0));
    }
};

using IntegrationMethod = std::function<double(double(*)(double, double), double, double, size_t, double)>;

void solve(const std::string& method_name,
    IntegrationMethod method,
    double p,
    const std::vector<size_t>& n_values,
    double a, double b)
{
    const double I_T = Function::I_T(p);
    constexpr double eps = std::numeric_limits<double>::epsilon();

    std::cout << "--- " << method_name << " ---\n";
    std::cout << "Функция: f(x) = (x^(" << p << ")" << " + x^(-" << p << "))/(1 + x^2)\n";
    std::cout << "Интервал: [" << a << ", " << b << "]\n";
    std::cout << "Точное значение (I_T): " << std::setprecision(12) << I_T << "\n";

    std::cout << std::setw(8) << "n"
              << std::setw(45) << "I_N"
              << std::setw(40) << "E" << "\n";
    std::cout << std::string(100, '-') << "\n";

    for (size_t n : n_values) {
        try {
            double I_N = method(Function::fx, a, b, n, p);
            //double epsilon = std::abs(I_T - I_N) / I_T;
            double epsilon = (std::abs(I_N) < eps) ?
                std::abs(I_N) :
                std::abs(I_T - I_N) / std::abs(I_T);    

            std::cout << std::setw(8) << n
                      << std::setw(69) << std::setprecision(67) << I_T
                      << std::setw(20) << std::setprecision(6) << epsilon << "\n";
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка при n = " << n << ": " << e.what() << "\n";
        }
    } std::cout << "\n";
}

int main() {
    SetConsoleOutputCP(1251);

    const double p = 0.1;
    const double a = 1e-10; // Нижняя граница (избегаем 0)
    const double b = 1.0;   // Верхняя граница
    const std::vector<size_t> n_values = { 4, 8, 16, 32, 64 };

    std::map<std::string, IntegrationMethod> methods = {
         {"Левые прямоугольники", left_rectangle},
         {"Правые прямоугольники", right_rectangle},
         {"Средние прямоугольники", middle_rectangle},
         {"Трапеции", trapezoid},
         {"Симпсон", simpson}
    };

    for (const auto& [name, method] : methods) {
        solve(name, method, p, n_values, a, b);
    }

	return 0;
}