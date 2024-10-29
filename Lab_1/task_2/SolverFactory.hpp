#ifndef SOLVERFACTORY_H
#define SOLVERFACTORY_H

#include "./solvers/NewtonSolver.hpp"
#include "./solvers/BisectionSolver.hpp"
#include "./solvers/IterationSolver.hpp"

#include "./Dependencies/except.h"

#include <memory>

namespace task_2 {

    enum class Type {
        Newton,
        Bisection,
        Iteration
    };

    class Factory {
    public:
        template <Type type>
        static auto create(const IEquation& equation, double eps = 1e-6) {
            if constexpr (type == Type::Newton) {
                return std::unique_ptr<INewtonSolver>(new NewtonSolver(equation, eps));
            }
            else if constexpr (type == Type::Bisection) {
                return std::unique_ptr<IBisectionSolver>(new BisectionSolver(equation, eps));
            }
            else if constexpr (type == Type::Iteration) {
                return std::unique_ptr<IIterationSolver>(new IterationSolver(equation, eps));
            }
            else {
                auto except = except::Factory::create<except::Type::Simple>();
                except->handleException("Unknown type of solvers.");
            }
        }
    };
}

#endif // !SOLVERFACTORY_H