#ifndef IDIFFERENTIATION_H
#define IDIFFERENTIATION_H

#include "./Dependencies/stdafx.h"

namespace task_1 {

    class IDifferentiation {
    public:
        virtual std::optional<std::vector<double>> calculateFirstOrder(const std::vector<double>& x, const std::vector<double>& y) const = 0;
        virtual std::optional<std::vector<double>> calculateSecondOrder(const std::vector<double>& x, const std::vector<double>& y) const = 0;

        virtual ~IDifferentiation() = default;
    };
}

#endif // !IDIFFERENTIATION_H