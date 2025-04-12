#pragma once
double right_rectangle(double (*f)(double, double), double a, double b, size_t n, double p) {
    const double h = (b - a) / n;

    double sum = 0.0;
    for (size_t i = 1; i <= n; ++i) {
        sum += f((a + i * h), p);
    } return sum * h;
}