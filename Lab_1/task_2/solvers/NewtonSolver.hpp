#pragma once
#ifndef NEWTONSOLVER_H
#define NEWTONSOLVER_H

#include "../Interfaces.h"
#include "../IEquation.h"

#include <./Dependencies/stdafx.h>

namespace task_2 {

    class NewtonSolver : public INewtonSolver {
    private:
        const IEquation& equation;

    public:
        NewtonSolver(const IEquation& eq, double eps = 1e-6)
            : INewtonSolver(eps), equation(eq) {}

        std::optional<double> solve(float initialGuess) override {
            double x = initialGuess;
            while (std::fabs(equation.f(x)) > epsilon) {
                double f_val = equation.f(x);
                double f_prime = equation.f_derivative(x);
                if (std::fabs(f_prime) < epsilon) {
                    return std::nullopt;
                }
                x = x - f_val / f_prime;
            }
            return x;
        }
    };
}

#endif // !NEWTONSOLVER_H