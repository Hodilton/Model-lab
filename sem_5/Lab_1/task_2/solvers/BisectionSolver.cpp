#pragma once
#ifndef BISECTIONSOLVER_H
#define BISECTIONSOLVER_H

#include "../Interfaces.h"
#include "./Model-lab/IEquation.h"

#include <./Dependencies/stdafx.h>

namespace task_2 {

    class BisectionSolver : public IBisectionSolver {
    private:
        const IEquation& equation;

    public:
        BisectionSolver(const IEquation& eq, double eps = 1e-6)
            : IBisectionSolver(eps), equation(eq) {}

        std::optional<double> solve(double a, double b) override {
            double left = a, right = b;
            if (equation.f(left) * equation.f(right) > 0) {
                return std::nullopt;
            }

            while (std::fabs(right - left) > epsilon) {
                double midpoint = (left + right) / 2.0;
                if (equation.f(midpoint) == 0.0) {
                    return midpoint;
                }
                else if (equation.f(left) * equation.f(midpoint) < 0) {
                    right = midpoint;
                }
                else {
                    left = midpoint;
                }
            }
            return (left + right) / 2.0;
        }
    };
}

#endif // BISECTIONSOLVER_H