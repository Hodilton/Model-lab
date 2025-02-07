#pragma once
#include <iostream>
#include <cmath>
#include <functional>
#include <iomanip>
#include <memory>
#include <numbers>

namespace prac_3::task_1 {

    class IIntegralCalculator {
    public:
        virtual double integrate(const std::function<double(double)>& func, double a, double b, int intervals) = 0;
        virtual ~IIntegralCalculator() = default;
    };

    // Метод прямоугольников
    class RectangleMethodCalculator : public IIntegralCalculator {
    public:
        double integrate(const std::function<double(double)>& func, double a, double b, int intervals) override {
            double h = (b - a) / intervals;
            double result = 0.0;

            for (int i = 0; i < intervals; ++i) {
                result += func(a + i * h) * h;
            }

            return result;
        }
    };

    // Метод Симпсона
    class SimpsonMethodCalculator : public IIntegralCalculator {
    public:
        double integrate(const std::function<double(double)>& func, double a, double b, int intervals) override {
            if (intervals % 2 != 0) {
                ++intervals; // Четное число интервалов
            }

            double h = (b - a) / intervals;
            double result = func(a) + func(b);

            for (int i = 1; i < intervals; ++i) {
                double x = a + i * h;
                result += func(x) * (i % 2 == 0 ? 2 : 4);
            }

            return result * h / 3.0;
        }
    };

    // Уточнение результата по правилу Рунге
    class RungeRuleRefiner {
    public:
        static double refine(const std::shared_ptr<IIntegralCalculator>& calculator,
            const std::function<double(double)>& func, double a, double b,
            double epsilon, int& finalIntervals) {
            int n = 4; // Начальное число разбиений

            double I1 = calculator->integrate(func, a, b, n);
            double I2;
            do {
                I2 = I1;
                n *= 2;
                I1 = calculator->integrate(func, a, b, n);

            } while (std::abs(I1 - I2) / 15.0 > epsilon);

            finalIntervals = n;
            return I1;
        }
    };

    class IntegrationAnalyzer {
    public:
        void analyze(const std::function<double(double)>& func, double a, double b, double exactValue, double epsilon) {
            auto rectangleCalculator = std::make_shared<RectangleMethodCalculator>();
            auto simpsonCalculator = std::make_shared<SimpsonMethodCalculator>();

            int rectIntervals, simpIntervals;

            // Уточнение результата по правилу Рунге
            double rectResult = RungeRuleRefiner::refine(rectangleCalculator, func, a, b, epsilon, rectIntervals);
            double simpResult = RungeRuleRefiner::refine(simpsonCalculator, func, a, b, epsilon, simpIntervals);

            // Вычисление без уточнения
            double rectApprox = rectangleCalculator->integrate(func, a, b, rectIntervals / 2);
            double simpApprox = simpsonCalculator->integrate(func, a, b, simpIntervals / 2);

            // Вывод результатов
            printResults("Rectangle Method", rectResult, rectApprox, exactValue, rectIntervals);
            printResults("Simpson Method", simpResult, simpApprox, exactValue, simpIntervals);
        }

    private:
        void printResults(const std::string& method, double refinedResult, double approxResult,
            double exactValue, int intervals) {
            std::cout << method << ":\n";
            std::cout << "  Refined Result: " << refinedResult << '\n';
            std::cout << "  Approximately Result: " << approxResult << '\n';
            std::cout << "  Exact Value:    " << exactValue << '\n';
            std::cout << "  Error (Refined): " << std::abs(refinedResult - exactValue) << '\n';
            std::cout << "  Error (Approx.): " << std::abs(approxResult - exactValue) << '\n';
            std::cout << "  Intervals Used: " << intervals << "\n\n";
        }
    };

    double Function1(double x) {
        return std::pow(std::numbers::e, std::sqrt(x));
    }

    double Function2(double x) {
        return x * std::sqrt(x + 1);
    }

    const void solution() {
        double a = 2.0;
        double b = 3.0;
        double exactValue = 4.6953854; // Точное значение интеграла
        double epsilon = 0.0001;

        IntegrationAnalyzer analyzer;
        analyzer.analyze(Function2, a, b, exactValue, epsilon);
    }
}