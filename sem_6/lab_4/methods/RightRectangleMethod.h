#pragma once
#include "../Function.h"

double right_rectangle(const Function& func, size_t n) {
    const auto& [a, b] = func.getRange();
    const double h = (b - a) / n;

    double sum = 0.0;
    for (size_t i = 1; i <= n; ++i) {
        double x = a + i * h;
        sum += (x == 0.0)
            ? func.fx(1e-15)
            : func.fx(x);
    } return sum * h;
}