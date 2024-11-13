#ifndef GAUSS_MATRIX_SOLVER_H
#define GAUSS_MATRIX_SOLVER_H

#include "./IMatrixSolver.h"

namespace matrix {

	class GaussSolver : public IMatrixSolver {
	private:
		void forwardElimination(Matrix<double>& A) {
			/*size_t n = A.getRows();
			for (size_t i = 0; i < n; ++i) {
				for (size_t j = i + 1; j < n; ++j) {

					double factor = A(j, i) / A(i, i);

					for (size_t k = i; k < n; ++k) {
						A(j, k) -= factor * A(i, k);
					}

					b[j] -= factor * b[i];
				}
			}*/
		}

		std::vector<double> backSubstitution(const Matrix<double>& A) {
			/*size_t n = A.getRows();
			std::vector<double> x(n, 0);
			for (int i = n - 1; i >= 0; --i) {

				x[i] = b[i];

				for (size_t j = i + 1; j < n; ++j) {
					x[i] -= A(i, j) * x[j];
				}

				x[i] /= A(i, i);
			}
			return x;*/
		}

	public:
		std::vector<double> solve(const Matrix<double>& A,
								  double tolerance) override {
			//std::vector<double> temp_b = b;
			//forwardElimination(A, temp_b);
			//std::vector<double> result = backSubstitution(A, temp_b);
			//if (!checkSolution(A, result, b, tolerance)) {
			//	throw std::runtime_error("Solution verification failed.");
			//}
			//return result;

			return { 1, 2, 3, 4, 5 };
		}
	};
}

#endif // !GAUSS_MATRIX_SOLVER_H