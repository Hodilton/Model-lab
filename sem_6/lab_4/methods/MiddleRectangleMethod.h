#pragma once
#include "../Function.h"

double middle_rectangle(const Function& func, size_t n) {
    const auto& [a, b] = func.getRange();
    const double h = (b - a) / n;

    double sum = 0.0;
    for (size_t i = 0; i < n; ++i) {
        double x = a + (i + 0.5) * h;
        sum += (x == 0.0)
            ? func.fx(1e-15)
            : func.fx(x);
    } return sum * h;
}