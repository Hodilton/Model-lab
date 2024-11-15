#ifndef GAUSS_MATRIX_SOLVER_H
#define GAUSS_MATRIX_SOLVER_H

#include "./IMatrixSolver.h"

namespace matrix {

	class GaussSolver : public IMatrixSolver {
	private:
		void forwardElimination(Matrix<double>& matrix) {
			size_t n = matrix.getRows();
			for (size_t i = 0; i < n; ++i) {

				if (std::abs(matrix(i, i)) < 1e-10) {
					throw std::runtime_error("Division by zero detected in Gaussian elimination.");
				}

				for (size_t j = i + 1; j < n; ++j) {
					double factor = matrix(j, i) / matrix(i, i);
					for (size_t k = i; k <= n; ++k) {
						matrix(j, k) -= factor * matrix(i, k);
					}
				}
			}
		}

		std::vector<double> backSubstitution(const Matrix<double>& matrix) {
			size_t n = matrix.getRows();
			std::vector<double> x(n, 0);
			for (int i = n - 1; i >= 0; --i) {

				x[i] = matrix(i, n);

				for (size_t j = i + 1; j < n; ++j) {
					x[i] -= matrix(i, j) * x[j];
				}

				x[i] /= matrix(i, i);
			}
			return x;
		}

	public:
		std::vector<double> solve(const Matrix<double>& matrix,
								  double tolerance) override {
			if (matrix.getCols() != matrix.getRows() + 1) {
				throw std::runtime_error("Matrix does not have a free column.");
			}

			Matrix<double> temp = matrix;

			forwardElimination(temp);
			auto result = backSubstitution(temp);

			if (!checkSolution(matrix, result, tolerance)) {
				throw std::runtime_error("Solution verification failed in Gauss method.");
			}

			return result;
		}
	};
}

#endif // !GAUSS_MATRIX_SOLVER_H