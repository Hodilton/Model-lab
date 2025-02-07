#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
#include <functional>

namespace prac_3::task_2 {

    class DoubleIntegral {
    public:
        double integrate(const std::function<double(double, double)>& func,
            double x1, double x2,
            const std::function<double(double)>& yLower,
            const std::function<double(double)>& yUpper,
            int nx, int ny) {

            double dx = (x2 - x1) / nx;
            double sum = 0.0;

            for (int i = 0; i < nx; ++i) {
                //double x = x1 + (i + 0.5) * dx; // Центр ячейки по x
                double x = x1 + i * dx + 0.5 * dx;
                double y1 = yLower(x);
                double y2 = std::min(yUpper(x), 1 + x);
                double dy = (y2 - y1) / ny;

                for (int j = 0; j < ny; ++j) {
                    //double y = y1 + (j + 0.5) * dy; // Центр ячейки по y
                    double y = y1 + j * dy + 0.5 * dy;
                    sum += func(x, y) * dy;
                }
            }

            return sum * dx;
        }

        // Уточнение по правилу Рунге
        double refine(const std::function<double(double, double)>& func,
            double x1, double x2,
            const std::function<double(double)>& yLower,
            const std::function<double(double)>& yUpper,
            double& approxResult, double eps) {

            int n = 4;
            double resultPrev = integrate(func, x1, x2, yLower, yUpper, n, n);
            double resultCurr;

            double error = 1.0;

            while (error > eps) {
                n *= 2;
                resultCurr = integrate(func, x1, x2, yLower, yUpper, n, n);
                error = std::abs(resultCurr - resultPrev) / 3;
                resultPrev = resultCurr;
            }

            return resultCurr;
        }
    };

    const void solution() {
        DoubleIntegral integrator;
        double x1 = 0.0, x2 = 1.0;
        double eps = 0.0001;

        // Функция для интегрирования
        auto func = [](double x, double y) { return x * std::pow(y, 2); };

        // Нижняя и верхняя границы по y
        auto yLower = [](double x) { return std::pow(x, 2); };
        auto yUpper = [](double x) { return 1 + x; };

        double approxResult;
        double resultRefined = integrator.refine(func, x1, x2, yLower, yUpper, approxResult, eps);

        std::cout << std::fixed << std::setprecision(6);
        std::cout << "Double Integral Results:\n";
        std::cout << "  Refined Result:    " << resultRefined << "\n";
        std::cout << "  Approximately:     " << approxResult << "\n";
    }
}