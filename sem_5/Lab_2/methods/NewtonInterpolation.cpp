#ifndef NEWTONINTERPOLATION_CPP
#define NEWTONINTERPOLATION_CPP

#include "IInterpolationMethod.h"

#include "./Dependencies/stdafx.h"

#include <sstream>

namespace lab_2 {

    class NewtonInterpolation : public IInterpolationMethod {
    private:
        std::vector<double> x_vals, y_vals;
        std::vector<double> dividedDifferences;

        void calculateDividedDifferences() {
            int n = x_vals.size();
            dividedDifferences = y_vals;

            for (int i = 1; i < n; ++i) {
                for (int j = n - 1; j >= i; --j) {
                    dividedDifferences[j] = (dividedDifferences[j] - dividedDifferences[j - 1]) / (x_vals[j] - x_vals[j - i]);
                }
            }
        }

    public:
        NewtonInterpolation(const std::vector<double>& x, const std::vector<double>& y)
            : x_vals(x), y_vals(y) {
            calculateDividedDifferences();
        }

        double calculate(double x) const override {
            double result = dividedDifferences[0];
            double product = 1.0;

            for (size_t i = 1; i < x_vals.size(); ++i) {
                product *= (x - x_vals[i - 1]);
                result += dividedDifferences[i] * product;
            }

            return result;
        }

        std::string getFormula() const override {
            std::ostringstream formula;
            formula << "P(x) = " << dividedDifferences[0];
            for (size_t i = 1; i < x_vals.size(); ++i) {
                formula << " + (" << dividedDifferences[i] << ")";
                for (size_t j = 0; j < i; ++j) {
                    formula << " * (x - " << x_vals[j] << ")";
                }
            }
            return formula.str();
        }
    };
}

#endif // !NEWTONINTERPOLATION_CPP