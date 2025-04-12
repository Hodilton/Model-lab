#pragma once
#include "../Function.h"

double simpson(const Function& func, size_t n) {
    if (n & 1) ++n;
    const auto& [a, b] = func.getRange();
    const double h = (b - a) / n;

    double sum = func.fx(a == 0.0 ? 1e-15 : a) 
               + func.fx(b == 0.0 ? 1e-15 : b);
    for (size_t i = 1; i < n; ++i) {
        double x = (a + i * h) * (i % 2 == 0 ? 2 : 4);
        sum += (x == 0.0)
            ? func.fx(1e-15)
            : func.fx(x);
    } return sum * h / 3;
}