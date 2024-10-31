#ifndef INTERPOLATIONFACTORY_H
#define INTERPOLATIONFACTORY_H

#include "./methods/IInterpolationMethod.h"
#include "./methods/NewtonInterpolation.cpp"
#include "./methods/LagrangeInterpolation.cpp"

#include "./Dependencies/stdafx.h"
#include "./Dependencies/except.h"

namespace lab_2 {

    enum class Type {
        Newton,
        Lagrange
    };

    class Factory {
    public:
        template <Type type>
        static std::unique_ptr<IInterpolationMethod> create(
            const std::vector<double>& x,
            const std::vector<double>& y)
        {
            if constexpr (type == Type::Newton) {
                return std::make_unique<NewtonInterpolation>(x, y);
            }
            else if constexpr (type == Type::Lagrange) {
                return std::make_unique<LagrangeInterpolation>(x, y);
            }
            else {
                auto except = except::Factory::create<except::Type::Simple>();
                except->handleException("Unknown type of interpolation method.");
            }
        }
    };
}

#endif // !INTERPOLATIONFACTORY_H