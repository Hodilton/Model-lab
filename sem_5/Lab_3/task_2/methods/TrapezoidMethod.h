#ifndef TRAPEZOIDREACTANGLEMETHOD_H
#define TRAPEZOIDREACTANGLEMETHOD_H

#include "./IIntegrationMethod.h"

namespace task_2 {

    class TrapezoidMethod : public IIntegrationMethod {
    public:
        double integrate(const IEquation& func, double a, double b, int n) const override {
            double h = (b - a) / n;
            double sum = 0.5 * (func.evaluate(a) + func.evaluate(b));

            for (int i = 1; i < n; ++i) {
                sum += func.evaluate(a + i * h);
            }

            return sum * h;
        }
    };
}

#endif // !TRAPEZOIDREACTANGLEMETHOD_H