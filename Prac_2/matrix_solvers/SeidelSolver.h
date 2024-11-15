#ifndef SEIDEL_MATRIX_SOLVER_H
#define SEIDEL_MATRIX_SOLVER_H

#include "./IMatrixSolver.h"

namespace matrix {

	class SeidelSolver : public IMatrixSolver {
	public:
		std::vector<double> solve(const Matrix<double>& matrix,
								  double tolerance) override {
            if (!matrix.isDiagonalDominance()) {
                throw std::runtime_error("Matrix is not diagonally dominant.");
            }

            size_t n = matrix.getRows();
            std::vector<double> x(n, 0), x_old(n, 0);

            do {
                x_old = x;
                for (size_t i = 0; i < n; ++i) {
                    double sum = matrix(i, matrix.getCols() - 1);

                    for (size_t j = 0; j < i; ++j) {
                        sum -= matrix(i, j) * x[j];
                    }
                    for (size_t j = i + 1; j < n; ++j) {
                        sum -= matrix(i, j) * x[j];
                    }

                    x[i] = sum / matrix(i, i);
                }
            } while (!hasConverged(x_old, x, tolerance));

            if (!checkSolution(matrix, x, tolerance)) {
                throw std::runtime_error("Solution verification failed.");
            }

            return x;
		}
	};
}

#endif // !SEIDEL_MATRIX_SOLVER_H