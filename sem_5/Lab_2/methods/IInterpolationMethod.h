#ifndef IINTERPOLATIONMETHOD_H
#define IINTERPOLATIONMETHOD_H

#include "./Dependencies/stdafx.h"

namespace lab_2 {

    class IInterpolationMethod {
    public:       
        virtual double calculate(double x) const = 0;
        virtual std::string getFormula() const = 0;

        virtual ~IInterpolationMethod() = default;
    };

}

#endif // !IINTERPOLATIONMETHOD_H