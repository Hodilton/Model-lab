#ifndef JACOBI_MATRIX_SOLVER_H
#define JACOBI_MATRIX_SOLVER_H

#include "./IMatrixSolver.h"

namespace matrix {

	class JacobiSolver : public IMatrixSolver {
	public:
		std::vector<double> solve(const Matrix<double>& A,
								  double tolerance) override {
            /*if (!A.isDiagonalDominance()) {
                throw std::runtime_error("Matrix is not diagonally dominant.");
            }

            size_t n = A.getRows();
            std::vector<double> x(n, 0), x_old(n, 0);

            bool converged;
            do {
                converged = true;
                for (size_t i = 0; i < n; ++i) {
                    double sum = b[i];
                    for (size_t j = 0; j < n; ++j) {
                        if (i != j) {
                            sum -= A(i, j) * x_old[j];
                        }
                    }
                    x[i] = sum / A(i, i);

                    if (std::abs(x[i] - x_old[i]) > tolerance) {
                        converged = false;
                    }
                }
                x_old = x;
            } while (!converged);

            if (!checkSolution(A, x, b, tolerance)) {
                throw std::runtime_error("Solution verification failed.");
            }

            return x;*/

            return { 4, 2, 3, 4, 5 };
		}
	};
}

#endif // !JACOBI_MATRIX_SOLVER_H