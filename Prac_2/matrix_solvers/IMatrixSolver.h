#ifndef IMATRIX_SOLVER_H
#define IMATRIX_SOLVER_H

#include "./Matrix/Matrix.h"

#include <vector>

namespace matrix {

    class IMatrixSolver {
    public:
        virtual std::vector<double> solve(const Matrix<double>& A, double tolerance) = 0;

        virtual bool checkSolution(const Matrix<double>& matrix, const std::vector<double>& x, double tolerance) const {
            Matrix<double> temp = matrix;
            temp.resize(matrix.getRows(), matrix.getCols() - 1);

            Matrix<double> X(x.size(), 1);
            X.setCol(0, x);

            std::vector<double> calculated = (temp * X).getCol(1);

            /*std::cout << "\n check:\n";
            std::copy(calculated.begin(), calculated.end(), std::ostream_iterator<double>(std::cout, " "));*/

            std::vector<double> free_elems = matrix.getCol(matrix.getCols());

            size_t n = matrix.getRows();
            for (size_t i = 0; i < n; ++i) {
                if (std::abs(calculated[i] - free_elems[i]) > tolerance) {
                    return false;
                }
            }
            return true;
        }

        virtual ~IMatrixSolver() = default;
    };
}

#endif // !IMATRIX_SOLVER_H