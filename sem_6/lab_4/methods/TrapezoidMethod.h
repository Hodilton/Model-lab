#pragma once
#include "../Function.h"

double trapezoid(const Function& func, size_t n) {
    const auto& [a, b] = func.getRange();
    const double h = (b - a) / n;

    double sum = 0.5 * (func.fx(a == 0.0 ? 1e-15 : a)
                        + func.fx(b == 0.0 ? 1e-15 : b));
    for (size_t i = 1; i < n; ++i) {
        double x = a + i * h;
        sum += (x == 0.0)
            ? func.fx(1e-15)
            : func.fx(x);
    } return sum * h;
}