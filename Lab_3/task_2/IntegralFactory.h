#ifndef INTEGRAL_FACTORY_H
#define INTEGRAL_FACTORY_H

#include "./methods/LeftRectangleMethod.h"
#include "./methods/RightRectangleMethod.h"
#include "./methods/MiddleRectangleMethod.h"
#include "./methods/TrapezoidMethod.h"
#include "./methods/SimpsonMethod.h"

#include <memory>
#include <stdexcept>

namespace task_2 {

    enum class Type {
        LeftRectangle,
        MiddleRectangle,
        RightRectangle,
        Simpson,
        Trapezoid
    };

    class Factory {
    public:
        template <Type type>
        static std::shared_ptr<IIntegrationMethod> create() {
            if constexpr (type == Type::LeftRectangle) {
                return std::make_shared<LeftRectangleMethod>();
            }
            else if constexpr (type == Type::MiddleRectangle) {
                return std::make_shared<MiddleRectangleMethod>();
            }
            else if constexpr (type == Type::RightRectangle) {
                return std::make_shared<RightRectangleMethod>();
            }
            else if constexpr (type == Type::Simpson) {
                return std::make_shared<SimpsonMethod>();
            }
            else if constexpr (type == Type::Trapezoid) {
                return std::make_shared<TrapezoidMethod>();
            }
            else {
                throw std::runtime_error("Unknown type of interpolation method.");
            }
        }
    };
}

#endif // !INTEGRAL_FACTORY_H