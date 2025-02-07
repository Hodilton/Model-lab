#ifndef DIFFERENTIATION_H
#define DIFFERENTIATION_H

#include "./IDifferentiation.h"

namespace task_1 {

    class Differentiation : public IDifferentiation {
    public:
        std::optional<std::vector<double>> calculateFirstOrder(const std::vector<double>& x,
                                                               const std::vector<double>& y) const override {
            if (x.size() != y.size() || x.size() < 2) {
                std::nullopt;
            }

            std::vector<double> firstDerivatives;
            for (size_t i = 0; i < x.size() - 1; ++i) {
                double dy_dx = (y[i + 1] - y[i]) / (x[i + 1] - x[i]);
                firstDerivatives.push_back(dy_dx);
            }

            return firstDerivatives;
        }

        std::optional<std::vector<double>> calculateSecondOrder(const std::vector<double>& x,
                                                                const std::vector<double>& y) const override {
            if (x.size() != y.size() || x.size() < 3) {
                std::nullopt;
            }

            std::vector<double> secondDerivatives;
            for (size_t i = 1; i < x.size() - 1; ++i) {
                double d2y_dx2 = (y[i + 1] - 2 * y[i] + y[i - 1]) / ((x[i + 1] - x[i]) * (x[i] - x[i - 1]));
                secondDerivatives.push_back(d2y_dx2);
            }
            return secondDerivatives;
        }
    };
}

#endif // !DIFFERENTIATION_H