#ifndef IINTEGRATION_METHOD_H
#define IINTEGRATION_METHOD_H

#include <./Model-lab/IEquation.h>

namespace task_2 {

    class IIntegrationMethod {
    public:
        virtual double integrate(const IEquation& func, double a, double b, int n) const = 0;

        virtual ~IIntegrationMethod() = default;
    };
}

#endif // !IINTEGRATION_METHOD_H