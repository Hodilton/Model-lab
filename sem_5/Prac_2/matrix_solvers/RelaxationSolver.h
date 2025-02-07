#ifndef RELAXATION_MATRIX_SOLVER_H
#define RELAXATION_MATRIX_SOLVER_H

#include "./IMatrixSolver.h"

namespace matrix {

	class RelaxationSolver : public IMatrixSolver {
	private:
		double _omega;
	public:
		RelaxationSolver(double omega) : _omega(omega) {}

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
                    x[i] = (1 - _omega) * x[i] + (_omega * sum) / matrix(i, i);
                }
            } while (!hasConverged(x_old, x, tolerance));

            if (!checkSolution(matrix, x, tolerance)) {
                throw std::runtime_error("Solution verification failed in Relaxation method.");
            }
            return x;
		}
	};
}

#endif // !RELAXATION_MATRIX_SOLVER_H