#ifndef SIMPSONREACTANGLEMETHOD_H
#define SIMPSONREACTANGLEMETHOD_H

#include "./IIntegrationMethod.h"

namespace task_2 {

    class SimpsonMethod : public IIntegrationMethod {
    public:
        double integrate(const IEquation& func, double a, double b, int n) const override {
            if (n & 1) {
                ++n;
            }

            double h = (b - a) / n;
            double sum = func.evaluate(a) + func.evaluate(b);

            for (int i = 1; i < n; ++i) {
                sum += func.evaluate(a + i * h) * (i % 2 == 0 ? 2 : 4);
            }

            return sum * h / 3;
        }
    };
}

#endif // !SIMPSONREACTANGLEMETHOD_H