#ifndef ROORFINDINGMETHODS_H
#define ROORFINDINGMETHODS_H

#include <unordered_set>
#include <functional>
#include <cmath>

class RootFindingMethod {
public:
    virtual std::unordered_set<double> findRoots(const std::function<double(double)>& f, double a, double b) const = 0;
    virtual ~RootFindingMethod() = default;

protected:
    static double round_to(double x, int n) {
        double pos = std::pow(10, n);
        return std::round(x * pos) / pos;
    }

    static const double dx;
    static const int max_iterations;
    static const double step_after_root;
};

constexpr double RootFindingMethod::dx = 1e-6;
constexpr int RootFindingMethod::max_iterations = 1000;
constexpr double RootFindingMethod::step_after_root = 0.1;

class NewtonMethod : public RootFindingMethod {
public:
    std::unordered_set<double> findRoots(const std::function<double(double)>& f, double a, double b) const override {
        std::unordered_set<double> roots;

        double x = a; // Используем 'a' как начальное приближение

        for (int i = 0; i < max_iterations; ++i) {

            double y = f(x), dy = dif(f, x);

            if (std::abs(y) < dx) {
                roots.insert(round_to(x, 3));
                x += step_after_root;
                continue;
            }

            if (dy == 0) break; // предотвращение деления на ноль
            x = x - y / dy;
        }

        return roots;
    }

private:
    double dif(const std::function<double(double)>& f, double x) const {
        return (f(x + dx) - f(x - dx)) / (2 * dx);
    }
};

class SecantMethod : public RootFindingMethod {
public:
    std::unordered_set<double> findRoots(const std::function<double(double)>& f, double a, double b) const override {
        std::unordered_set<double> roots;

        double y_a = f(a), y_b = f(b);

        if (y_a * y_b < 0) {
            for (int i = 0; i < max_iterations; ++i) {

                double x = a - (y_a * (b - a)) / (y_b - y_a);
                double y_x = f(x);

                if (std::abs(y_x) < dx) {
                    roots.insert(round_to(x, 3));
                    x += step_after_root;
                    continue;
                }

                a = b;
                b = x;
                y_a = f(a);
                y_b = f(b);

                if (std::abs(y_b) < dx) break;
            }
        }
        return roots;
    }
};

class IterativeMethod : public RootFindingMethod {
public:
    std::unordered_set<double> findRoots(const std::function<double(double)>& f, double a, double b) const override {
        std::unordered_set<double> roots;

        double x = a; // Используем 'a' как начальное приближение

        for (int i = 0; i < max_iterations; ++i) {

            double prev_x = x;
            x -= f(x) / 2; // Здесь можно улучшить стратегию шага

            if (std::abs(f(x)) < dx) {
                roots.insert(round_to(x, 3));
                x += step_after_root;
                continue;
            }
        }
        return roots;
    }
};

#endif // !ROORFINDINGMETHODS_H