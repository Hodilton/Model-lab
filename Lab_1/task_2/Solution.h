#ifndef TASK_2_SOLUTION_H
#define TASK_2_SOLUTION_H

#include "./SolverFactory.hpp"

#include <./Dependencies/stdafx.h>

namespace task_2 {

    class F1 : public AbstractEquation {
    public:
        F1(std::string f): AbstractEquation(f) {}

        double f(double x) const override {
            return std::pow(x, 3) - 10 * x - 5;
        }

        double f_derivative(double x) const override {
            return 3 * std::pow(x, 2) - 10;
        }

        std::string get_str_f() const override {
            return str_f;
        }
    };

    void solution() {
        F1 equation("f(x) = x ^ 3 - 10 * x - 5");

        auto newtonSolver = Factory::create<Type::Newton>(equation);
        auto bisectionSolver = Factory::create<Type::Bisection>(equation);
        auto iterationSolver = Factory::create<Type::Iteration>(equation);

        auto nr = newtonSolver->solve(1.5);
        auto br = bisectionSolver->solve(3.0, 4.0);
        auto ir = iterationSolver->solve(1.5, 0.01);

        cout << "" << equation.get_str_f() << endl;
        cout << "Newton: " << (nr ? "" + std::to_string(*nr) : "no solution found") << endl;
        cout << "Bisection: " << (br ? "" + std::to_string(*br) : "no solution found") << endl;
        cout << "Iteration: " << (ir ? "" + std::to_string(*ir) : "no solution found") << endl;
    }
}

#endif // !TASK_2_SOLUTION_H