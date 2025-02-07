#ifndef DATATABLE_H
#define DATATABLE_H

#include "./methods/IInterpolationMethod.h"

#include "./Dependencies/stdafx.h"

namespace lab_2 {

    class DataTable {
    private:
        std::vector<double> x_vals, y_vals;
        std::unique_ptr<IInterpolationMethod> interpolationMethod;

    public:
        DataTable(const std::vector<double>& x, const std::vector<double>& y)
            : x_vals(x), y_vals(y) {}

        void setInterpolationMethod(std::unique_ptr<IInterpolationMethod> method) {
            interpolationMethod = std::move(method);
        }

        std::optional<double> interpolate(double x) const {
            if (!interpolationMethod) {
                return std::nullopt;
            }

            return interpolationMethod->calculate(x);
        }

        std::optional<std::string> getFormula() const {
            if (!interpolationMethod) {
                return std::nullopt;
            }

            return interpolationMethod->getFormula();
        }
    };
}

#endif // !DATATABLE_H