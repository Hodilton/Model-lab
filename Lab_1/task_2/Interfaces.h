#pragma once
#ifndef INTERFACES_H
#define INTERFACES_H

namespace task_2 {

    class IEquationSolver {
    protected:
        double epsilon;

    public:
        explicit IEquationSolver(double eps = 1e-6) : epsilon(eps) {}
        virtual ~IEquationSolver() = default;
    };

    class INewtonSolver : public IEquationSolver {
    public:
        using IEquationSolver::IEquationSolver;
        virtual std::optional<double> solve(float initialGuess) = 0;
    };

    class IIterationSolver : public IEquationSolver {
    public:
        using IEquationSolver::IEquationSolver;
        virtual std::optional<double> solve(float initialGuess, double lambda) = 0;
    };

    class IBisectionSolver : public IEquationSolver {
    public:
        using IEquationSolver::IEquationSolver;
        virtual std::optional<double> solve(double a, double b) = 0;
    };
}

#endif // !INTERFACES_H