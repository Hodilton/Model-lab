#pragma once
double simpson(double (*f)(double, double), double a, double b, size_t n, double p) {
    if (n & 1) ++n;
    const double h = (b - a) / n;

    double sum = f(a, p) + f(b, p);
    for (size_t i = 1; i < n; ++i) {
        sum += f(((a + i * h) * (i % 2 == 0 ? 2 : 4)), p);
    } return sum * h / 3;
}