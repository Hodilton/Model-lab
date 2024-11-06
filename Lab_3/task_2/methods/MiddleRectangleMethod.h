#ifndef MIDDLEREACTANGLEMETHOD_H
#define MIDDLEREACTANGLEMETHOD_H

#include "./IIntegrationMethod.h"

namespace task_2 {

    class MiddleRectangleMethod : public IIntegrationMethod {
    public:
        double integrate(const IEquation& func, double a, double b, int n) const override {
            double h = (b - a) / n;
            double sum = 0.0;

            for (int i = 0; i < n; ++i) {
                sum += func.evaluate(a + (i + 0.5) * h);
            }

            return sum * h;
        }
    };
}

#endif // !MIDDLEREACTANGLEMETHOD_H