#include "DataTable.h"
#include "InterpolationFactory.h"

#include "./Dependencies/stdafx.h"

int main() {
    std::vector<double> x_vals = { 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5 };
    std::vector<double> y_vals = { 2.7, 4.5, 7.4, 12.2, 20.1, 33.1, 54.6, 90.0, 148.4, 244.7 };

    lab_2::DataTable table(x_vals, y_vals);

    double x = 2.5;
    table.setInterpolationMethod(lab_2::Factory::create<lab_2::Type::Newton>(x_vals, y_vals));
    std::cout << "Newton Interpolation Formula: " << *table.getFormula() << std::endl;
    std::cout << "Interpolated value at x = " << x << ": " << *table.interpolate(x) << std::endl;

    table.setInterpolationMethod(lab_2::Factory::create<lab_2::Type::Lagrange>(x_vals, y_vals));
    std::cout << "\nLagrange Interpolation Formula: " << *table.getFormula() << std::endl;
    std::cout << "Interpolated value at x = " << x << ": " << *table.interpolate(x) << std::endl;

    return 0;
}