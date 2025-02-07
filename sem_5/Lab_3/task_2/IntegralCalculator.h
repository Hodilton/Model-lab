#ifndef INTEGRAL_CALCULATOR_H
#define INTEGRAL_CALCULATOR_H

#include "./methods/IIntegrationMethod.h"

#include <memory>
#include <stdexcept>

namespace task_2 {

    class IntegralCalculator {
    private:
        std::shared_ptr<IIntegrationMethod> method;

    public:
        void setMethod(std::shared_ptr<IIntegrationMethod> method) {
            this->method = method;
        }

        double calculate(const IEquation& func, double a, double b, int n) const {
            if (!method) {
                throw std::runtime_error("Integration method not set.");
            }

            return method->integrate(func, a, b, n);
        }
    };
}

#endif // !INTEGRAL_CALCULATOR_H