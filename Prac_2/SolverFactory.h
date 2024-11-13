#ifndef MATRIX_SOLVER_FACTORY_H
#define MATRIX_SOLVER_FACTORY_H

#include "./matrix_solvers/GaussSolver.h"
#include "./matrix_solvers/JacobiSolver.h"
#include "./matrix_solvers/RelaxationSolver.h"
#include "./matrix_solvers/SeidelSolver.h"

namespace matrix {

    enum class Type {
        Gauss,
        Jacobi,
        Relaxatin,
        Seidel
    };

    class SolverFactory {
    public:
        template <Type type>
        static std::shared_ptr<IMatrixSolver> create(double omega = 1.0) {
            if constexpr (type == Type::Gauss) {
                return std::make_shared<GaussSolver>();
            }
            else if constexpr (type == Type::Jacobi) {
                return std::make_shared<JacobiSolver>();
            }
            else if constexpr (type == Type::Seidel) {
                return std::make_shared<SeidelSolver>();
            }
            else if constexpr (type == Type::Relaxatin) {
                return std::make_shared<RelaxationSolver>(omega);
            }
            else {
                throw std::runtime_error("Unknown type of matrix solver.");
            }
        }
    };
}

#endif // !MATRIX_SOLVER_FACTORY_H