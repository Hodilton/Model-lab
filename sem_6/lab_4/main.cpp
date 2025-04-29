#include "./CPlusPlus-File/src/File.h"

#include "./methods/LeftRectangleMethod.h"
#include "./methods/MiddleRectangleMethod.h"
#include "./methods/RightRectangleMethod.h"
#include "./methods/SimpsonMethod.h"
#include "./methods/TrapezoidMethod.h"

#include "./Function.h"

#include "iostream"
#include "iomanip"
#include <Windows.h>
#include <cmath>
#include <numbers>
#include <functional>
#include <string>
#include <map>

using IntegrationMethod = std::function<double(const Function&, size_t)>;
using IntegrationMethods = std::map<std::string, IntegrationMethod>;

void solve(const std::string& method_name,
    IntegrationMethod method,
    const Function& func)
{
    const double I_T = func.I_T();

    std::cout << "--- " << method_name << " ---\n";
    std::cout << "Функция: f(x) = " << func.getF() << "\n";
    std::cout << "Интервал: [" 
        << func.getRange().first 
        << ", " 
        << func.getRange().second << "]\n";
    std::cout << "Точное значение (I_T): " << std::setprecision(25) << I_T << "\n";

    std::cout << std::right
              << std::setw(8) << "n"
              << std::setw(25) << "I_N"
              << std::setw(30) << "E" << "\n";
    std::cout << std::string(73, '-') << "\n";

    for (size_t n : func.getNValues()) {
        try {
            double I_N = method(func, n);
            double epsilon = std::abs(I_T - I_N) / I_T;

            std::cout << std::setw(8) << n << std::setw(15) << " " << std::left
                      << std::setw(37) << std::setprecision(25) << I_N
                      << std::setw(10) << std::setprecision(6) << epsilon 
                      << std::right << "\n";
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка при n = " << n << ": " << e.what() << "\n";
        }
    } std::cout << "\n";
}

int main() {
    SetConsoleOutputCP(1251);

    using Data = std::map<std::string, Function>;
    auto data = file::File<Data>::read(file::path::PathParams(
        "./data", "input", "json"
    ));

    const Function& func = (*data).at("2");

    IntegrationMethods methods = {
         {"Левые прямоугольники", left_rectangle},
         {"Правые прямоугольники", right_rectangle},
         {"Средние прямоугольники", middle_rectangle},
         {"Трапеции", trapezoid},
         {"Симпсон", simpson}
    };

    for (const auto& [name, method] : methods) {
        solve(name, method, func);
    }

	return 0;
}