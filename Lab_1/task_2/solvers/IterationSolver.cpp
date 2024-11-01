#pragma once
#ifndef ITERATIONSOLVER_H
#define ITERATIONSOLVER_H

#include "../Interfaces.h"
#include "./Model-lab/IEquation.h"

#include <./Dependencies/stdafx.h>

namespace task_2 {

    class IterationSolver : public IIterationSolver {
    private:
        const IEquation& equation;

    public:
        IterationSolver(const IEquation& eq, double eps = 1e-6)
            : IIterationSolver(eps), equation(eq) {}

        std::optional<double> solve(float initialGuess, double lambda) override {
            double x = initialGuess;
            double nextX = x - lambda * equation.f(x);

            while (std::fabs(nextX - x) > epsilon) {
                x = nextX;
                nextX = x - lambda * equation.f(x);
            }
            return nextX;
        }
    };
}

#endif // !ITERATIONSOLVER_H