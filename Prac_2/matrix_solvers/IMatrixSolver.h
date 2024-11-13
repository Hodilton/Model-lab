#ifndef IMATRIX_SOLVER_H
#define IMATRIX_SOLVER_H

#include "./Matrix/Matrix.h"

#include <vector>

namespace matrix {

    class IMatrixSolver {
    public:
        virtual std::vector<double> solve(const Matrix<double>& A, double tolerance) = 0;
        virtual bool checkSolution(const Matrix<double>& A, const std::vector<double>& x, double tolerance) const {
            size_t n = A.getRows();
            for (size_t i = 0; i < n; ++i) {
                double sum = 0.0;

                for (size_t j = 0; j < n; ++j) {
                    sum += A(i, j) * x[j];
                }

                if (std::abs(sum - x[i]) > tolerance) {
                    return false;
                }
            }
            return true;
        }

        virtual ~IMatrixSolver() = default;
    };
}

#endif // !IMATRIX_SOLVER_H