#ifndef TASK_2_SOLUTION_H
#define TASK_2_SOLUTION_H

#include<iostream>
#include <cmath>
#include <string>

#include "./RootFindingMethods.h"

namespace task_2 {

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
            if (roots.empty()) {
                return "Корни не найдены";
            }

            std::string out;

            int i = 0;
            for (const auto& root : roots) {
                i++;
                out += " x" + std::to_string(i) + " = " + std::to_string(root);
            }

            return out;
        }
    };

    void solution() {
        std::setlocale(LC_ALL, "russian");
        
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
        std::cout << "Метод Cекущих: " << solver1.solve(secant, a, b) << "\n";
        std::cout << "Метод Bтерации: " << solver1.solve(iter, for_newton, b) << "\n\n";
        
        std::cout << "f2:\n";
        std::cout << "Метод Ньютона: " << solver2.solve(newton, for_newton, b) << "\n";
        std::cout << "Метод Cекущих: " << solver2.solve(secant, a, b) << "\n";
        std::cout << "Метод Bтерации: " << solver2.solve(iter, for_newton, b) << "\n";
    }
}

#endif // !TASK_2_SOLUTION_H