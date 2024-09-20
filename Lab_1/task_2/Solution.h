#ifndef TASK_2_SOLUTION_H
#define TASK_2_SOLUTION_H

#include<iostream>
#include <cmath>
#include <string>
#include <sstream>

#include "./RootFindingMethods.h"

namespace task_2 {

    class FunctionSolver {
    public:
        explicit FunctionSolver(const std::function<double(double)>& func) : f(func) {}

        std::unordered_set<double> solve(const RootFindingMethod& method, double a, double b) const {
            return method.findRoots(f, a, b);
        }

    private:
        std::function<double(double)> f;
    };

    std::string formatRoots(const std::unordered_set<double>& roots) {
        if (roots.empty()) {
            return "No find roots.";
        }

        std::ostringstream out;
        int i = 0;

        for (const auto& root : roots) {
            i++;
            out << " x" << i << " = " << root;
        }

        return out.str();
    }

    void solution() {
        

        std::function<double(double)> f1 = [](double x) { return std::pow(x, 3) - 10 * x - 5; };
        std::function<double(double)> f2 = [](double x) { return std::pow(x, 3) - 10 * x * x - 20; };

        NewtonMethod newton;
        SecantMethod secant;
        IterativeMethod iter;

        FunctionSolver solver1(f1);
        FunctionSolver solver2(f2);

        // Параметры для нахождения корней
        double for_newton = 3, a = 2, b = 3;

        std::cout << "f1:\n";
        std::cout << "Newton: " << formatRoots(solver1.solve(newton, for_newton, b)) << "\n";
        std::cout << "Secant: " << formatRoots(solver1.solve(secant, a, b)) << "\n";
        std::cout << "Iterative: " << formatRoots(solver1.solve(iter, for_newton, b)) << "\n\n";

        std::cout << "f2:\n";
        std::cout << "Newton: " << formatRoots(solver2.solve(newton, for_newton, b)) << "\n";
        std::cout << "Secant: " << formatRoots(solver2.solve(secant, a, b)) << "\n";
        std::cout << "Iterative: " << formatRoots(solver2.solve(iter, for_newton, b)) << "\n";
    }
}

#endif // !TASK_2_SOLUTION_H