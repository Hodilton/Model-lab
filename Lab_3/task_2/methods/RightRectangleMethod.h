#ifndef RIGHTREACTANGLEMETHOD_H
#define RIGHTREACTANGLEMETHOD_H

#include "./IIntegrationMethod.h"

namespace task_2 {

    class RightRectangleMethod : public IIntegrationMethod {
    public:
        double integrate(const IEquation& func, double a, double b, int n) const override {
            double h = (b - a) / n;
            double sum = 0.0;

            for (int i = 1; i <= n; ++i) {
                sum += func.evaluate(a + i * h);
            }

            return sum * h;
        }
    };
}

#endif // !RIGHTREACTANGLEMETHOD_H