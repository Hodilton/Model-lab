#ifndef LAGRANGEINTERPOLATION_CPP
#define LAGRANGEINTERPOLATION_CPP

#include "IInterpolationMethod.h"

#include "./Dependencies/stdafx.h"

#include <sstream>

namespace lab_2 {

    class LagrangeInterpolation : public IInterpolationMethod {
    private:
        std::vector<double> x_vals, y_vals;

    public:
        LagrangeInterpolation(const std::vector<double>& x, const std::vector<double>& y)
            : x_vals(x), y_vals(y) {}

        double calculate(double x) const override {
            double result = 0.0;
            for (size_t i = 0; i < x_vals.size(); ++i) {
                double term = y_vals[i];
                for (size_t j = 0; j < x_vals.size(); ++j) {
                    if (j != i) {
                        term *= (x - x_vals[j]) / (x_vals[i] - x_vals[j]);
                    }
                }
                result += term;
            }
            return result;
        }

        std::string getFormula() const override {
            std::ostringstream formula;
            formula << "P(x) = ";
            for (size_t i = 0; i < x_vals.size(); ++i) {
                formula << "(" << y_vals[i] << ")";
                for (size_t j = 0; j < x_vals.size(); ++j) {
                    if (j != i) {
                        formula << " * (x - " << x_vals[j] << ") / (" << x_vals[i] - x_vals[j] << ")";
                    }
                }
                if (i != x_vals.size() - 1) {
                    formula << " + ";
                }
            }
            return formula.str();
        }
    };
}

#endif // !LAGRANGEINTERPOLATION_CPP