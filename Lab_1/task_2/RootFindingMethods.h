#ifndef ROORFINDINGMETHODS_H
#define ROORFINDINGMETHODS_H

#include <unordered_set>
#include <functional>

class RootFindingMethod {
public:
    virtual std::unordered_set<double> findRoots(std::function<double(double)> f, double a, double b) const = 0;
    virtual ~RootFindingMethod() = default;
};

const double dx = 1e-6;

class NewtonMethod : public RootFindingMethod {
public:
    std::unordered_set<double> findRoots(std::function<double(double)> f, double a, double b) const override {
        std::unordered_set<double> roots;
        double x = a; // ���������� 'a' ��� ��������� �����������
        for (int i = 0; i < 1000; ++i) {
            double y = f(x), dy = dif(f, x);
            if (std::abs(y) < dx) {
                roots.insert(round_to(x, 3));
                x += 0.1;
                continue;
            }
            if (dy == 0) break; // �������������� ������� �� ����
            x = x - y / dy;
        }
        return roots;
    }

private:
    double dif(std::function<double(double)> f, double x) const {
        return (f(x + dx) - f(x - dx)) / (2 * dx);
    }

    double round_to(double x, int n) const {
        double pos = std::pow(10, n);
        return std::round(x * pos) / pos;
    }
};

class SecantMethod : public RootFindingMethod {
public:
    std::unordered_set<double> findRoots(std::function<double(double)> f, double a, double b) const override {
        std::unordered_set<double> roots;
        double y_a = f(a), y_b = f(b);
        if (y_a * y_b < 0) {
            for (int i = 0; i < 1000; ++i) {
                double x = a - (y_a * (b - a)) / (y_b - y_a);
                double y_x = f(x);
                if (std::abs(y_x) < dx) {
                    roots.insert(round_to(x, 3));
                    x += 0.1;
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

private:
    double round_to(double x, int n) const {
        double pos = std::pow(10, n);
        return std::round(x * pos) / pos;
    }
};

class IterativeMethod : public RootFindingMethod {
public:
    std::unordered_set<double> findRoots(std::function<double(double)> f, double a, double b) const override {
        std::unordered_set<double> roots;
        double x = a; // ���������� 'a' ��� ��������� �����������
        for (int i = 0; i < 1000; ++i) {
            double prev_x = x;
            x -= f(x) / 2;
            if (std::abs(f(x)) < dx) {
                roots.insert(round_to(x, 3));
                x += 0.1;
                continue;
            }
        }
        return roots;
    }

private:
    double round_to(double x, int n) const {
        double pos = std::pow(10, n);
        return std::round(x * pos) / pos;
    }
};

#endif // !ROORFINDINGMETHODS_H