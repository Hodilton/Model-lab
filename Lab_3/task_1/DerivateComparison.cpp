#ifndef DERIVATIVECOMPARISON_H
#define DERIVATIVECOMPARISON_H

#include "./IDifferentiation.h"

#include "./Model-lab/IEquation.h"
#include "./Model-lab/Lab_2/methods/IInterpolationMethod.h"

#include <tuple>

namespace task_1 {

    class DerivativeComparison {
    private:
        std::vector<double> x_vals;
        std::unique_ptr<IDifferentiation> differentiationMethod;
        std::unique_ptr<IEquation> function;
        std::unique_ptr<lab_2::IInterpolationMethod> interpolationMethod;

    public:
        DerivativeComparison(std::vector<double> x,
            std::unique_ptr<IDifferentiation> diff,
            std::unique_ptr<IEquation> func,
            std::unique_ptr<lab_2::IInterpolationMethod> method)
            : x_vals(std::move(x)), differentiationMethod(std::move(diff)),
              function(std::move(func)), interpolationMethod(std::move(method)) {}

        std::tuple<std::vector<double>, std::vector<double>, std::vector<double>> calculateFirstOrder() const {
            // ¬ычисл€ем первую производную дл€ табличных данных
            std::vector<double> y_vals;
            for (double x : x_vals) {
                y_vals.push_back(function->evaluate(x));
            }
            auto tableDerivatives = differentiationMethod->calculateFirstOrder(x_vals, y_vals);

            // ¬ычисл€ем первую производную дл€ интерпол€ционного полинома
            std::vector<double> polyDerivatives;
            for (double x : x_vals) {
                polyDerivatives.push_back(interpolationMethod->calculate(x));
            }

            // ¬ычисл€ем аналитическую первую производную
            std::vector<double> functionDerivatives;
            for (double x : x_vals) {
                functionDerivatives.push_back(function->derivativeFirst(x));
            }

            return { *tableDerivatives, polyDerivatives, functionDerivatives };
        }

        std::tuple<std::vector<double>, std::vector<double>, std::vector<double>> calculateSecondOrder() const {
            // ¬ычисл€ем вторую производную дл€ табличных данных
            std::vector<double> y_vals;
            for (double x : x_vals) {
                y_vals.push_back(function->evaluate(x));
            }
            auto tableDerivatives = differentiationMethod->calculateSecondOrder(x_vals, y_vals);

            // ¬ычисл€ем вторую производную дл€ интерпол€ционного полинома
            std::vector<double> polyDerivatives;
            for (double x : x_vals) {
                polyDerivatives.push_back(interpolationMethod->calculate(x));
            }

            // ¬ычисл€ем аналитическую вторую производную
            std::vector<double> functionDerivatives;
            for (double x : x_vals) {
                functionDerivatives.push_back(function->derivativeSecond(x));
            }

            return { *tableDerivatives, polyDerivatives, functionDerivatives };
        }
    };
}

#endif // !DERIVATIVECOMPARISON_H