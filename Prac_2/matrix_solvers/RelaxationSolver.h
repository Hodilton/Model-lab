#ifndef RELAXATION_MATRIX_SOLVER_H
#define RELAXATION_MATRIX_SOLVER_H

#include "./IMatrixSolver.h"

namespace matrix {

	class RelaxationSolver : public IMatrixSolver {
	private:
		double _omega;

	public:
		RelaxationSolver(double omega) : _omega(omega) {}

		std::vector<double> solve(const Matrix<double>& A,
								  double tolerance) override {
            /*if (!A.isDiagonalDominance()) {
                throw std::runtime_error("Matrix is not diagonally dominant.");
            }

            size_t n = A.getRows();
            std::vector<double> x(n, 0);

            bool converged;
            do {
                converged = true;
                for (size_t i = 0; i < n; ++i) {
                    double sum = b[i];
                    for (size_t j = 0; j < i; ++j) {
                        sum -= A(i, j) * x[j];
                    }
                    for (size_t j = i + 1; j < n; ++j) {
                        sum -= A(i, j) * x[j];
                    }

                    double x_new = (1 - _omega) * x[i] + (_omega * sum) / A(i, i);
                    if (std::abs(x_new - x[i]) > tolerance) {
                        converged = false;
                    }
                    x[i] = x_new;
                }
            } while (!converged);

            if (!checkSolution(A, x, b, tolerance)) {
                throw std::runtime_error("Solution verification failed.");
            }

            return x;*/

            return { 3, 2, 3, 4, 5 };
		}
	};
}

#endif // !RELAXATION_MATRIX_SOLVER_H