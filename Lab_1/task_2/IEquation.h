#pragma once
#ifndef IEQUATION_H
#define IEQUATION_H

#include <cmath>
#include <string>

namespace task_2 {

    class IEquation {
    public:
        virtual double f(double x) const = 0;
        virtual double f_derivative(double x) const = 0;
        virtual std::string get_str_f() const = 0;
        virtual ~IEquation() = default;
    };

    class AbstractEquation : public IEquation {
    protected:
        std::string str_f;

    public:
        AbstractEquation(const std::string& str_f) : str_f(str_f) {}
    };
}

#endif // !IEQUATION_H