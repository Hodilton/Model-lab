#include "./CPlusPlus-File/src/File.h"
#include "./Calculates-expressions/src/Calculator.h"

#include "./Function.h"

#include <Windows.h>
#include <string>
#include <map>
#include <cmath>

calc::Calculator<double> clc;

double bisection(const Function& f, double eps, int& iterations) {
    auto [a, b] = f.getRange();

    double fa = *clc.evaluate(f.fx(), { {"x", a} });
    double fb = *clc.evaluate(f.fx(), { {"x", b} });

    if (std::fabs(fa) < eps) return a;
    if (std::fabs(fb) < eps) return b;

    if (fa * fb > 0) {
        std::cout << "Метод не может быть применен: функция не меняет знак на интервале [" << a << ", " << b << "]\n";
        return std::nan("");
    }

    while ((b - a) / 2.0 > eps) {
        iterations++;

        double c = (a + b) / 2.0;
        double fc = *clc.evaluate(f.fx(), { {"x", c} });

        if (std::fabs(fc) < eps) {
            return c;
        }
        if (fa * fc < 0) {
            b = c;
            fb = fc;
        }
        else {
            a = c;
            fa = fc;
        }
    } return (a + b) / 2.0;
}

double simple_iterations(const Function& f, double eps, int& iterations) {
    auto [a, b] = f.getRange();
    double x0 = (a + b) / 2.0;
    double x1;

    double df_x0 = *clc.evaluate(f.dfx(), { {"x", x0} });
    double beta = -1.0 / df_x0;

    // |1 - b * f'(x)| < 1 в пределах интервала
    bool convergent = true;
    for (double test_x = a; test_x <= b; test_x += (b - a) / 100.0) {
        double df_test = *clc.evaluate(f.dfx(), { {"x", test_x} });

        if (fabs(1 + beta * df_test) >= 1.0) {
            convergent = false;
            break;
        }
    }

    if (!convergent) {
        std::cout << "Метод простых итераций не сходится на данном интервале.\n";
        return std::nan("");
    }

    iterations = 0;
    do {
        iterations++;
        double fx0 = *clc.evaluate(f.fx(), { {"x", x0} });
        x1 = x0 + beta * fx0;

        if (fabs(x1 - x0) < eps) {
            break;
        }

        x0 = x1;
    } while (iterations < 100000);

    return x1;
}

double newton(const Function& f, double eps, int& iterations) {
    auto [a, b] = f.getRange();
    double x0 = (a + b) / 2.0;
    double x1;

    do {
        iterations++;

        double fx0 = *clc.evaluate(f.fx(), { {"x", x0} });
        double dfx0 = *clc.evaluate(f.dfx(), { {"x", x0} });

        if (std::fabs(dfx0) < eps) {
            std::cout << "Ошибка: производная слишком мала\n";
            return std::nan("");
        }

        x1 = x0 - fx0 / dfx0;

        if (fabs(x1 - x0) < eps) {
            break;
        }

        if (std::fabs(x1 - x0) < eps) {
            break;
        }

        x0 = x1;
    } while (true);
    return x1;
}

void solve(const std::string& method_name,
           double (*method)(const Function&, double, int&),
           const Function& function)
{
    int iterations = 0;
    double x = method(function, function.getEps(), iterations);
    double rounded_x = std::round(x * 1e6) / 1e6;
    double f_x = *clc.evaluate(function.fx(), { {"x", rounded_x} });

    std::cout << method_name << ":\n";
    std::cout << "x = " << rounded_x << std::endl;
    std::cout << "Количество итераций: " << iterations << std::endl;
    std::cout << ((std::fabs(f_x) < function.getCheckEps())
        ? "Корень найден корректно.\n"
        : "Ошибка: найденный корень неверен.\n");
    for (size_t i = 0; i < 40; i++) { std::cout << "-"; } std::cout << std::endl;
}

int main() {
    SetConsoleOutputCP(1251);

    using Data = std::map<std::string, Function>;

    auto data = file::File<Data>::read(file::path::PathParams(
        "./data", "input", "json"
    ));

    for (const auto& [name, function] : *data) {
        std::cout << "Номер: " << name << std::endl;
        std::cout << "Функция: " << function.fx() << std::endl;
        auto [a, b] = function.getRange();
        std::cout << "Область: (" << a << ", " << b << ")\n" << std::endl;

        solve("Метод дихотомии", bisection, function);
        solve("Метод последовательных приближений", simple_iterations, function);
        solve("Метод Ньютона", newton, function);
    }

	return 0;
}