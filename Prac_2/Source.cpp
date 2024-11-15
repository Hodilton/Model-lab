#include "./Matrix/Matrix.h"
#include "./SolverFactory.h"

#include "./Dependencies/file_work/file_processor.h"

template<typename T>
using Solution = std::map<std::string, std::vector<T>>;

template<typename T>
using Solutions = std::map<std::string, Solution<T>>;

using namespace matrix;

int main() {
	try {
		auto data = file_work::File<json>::read(
			file_work::PathParams("./data", "input", "json"));

		auto matrices = MatrixJsonDeserializer<double>::fromJsonMap(data);

		std::vector<std::shared_ptr<IMatrixSolver>> solvers = {
			matrix::SolverFactory::create<matrix::Type::Gauss>(),
			matrix::SolverFactory::create<matrix::Type::Jacobi>(),
			matrix::SolverFactory::create<matrix::Type::Seidel>(),
			matrix::SolverFactory::create<matrix::Type::Relaxatin>()
		};

		std::vector<std::string> solversNames = {
			"Gauss",
			"Jacobi",
			"Seidel",
			"Relaxation"
		};

		Solution<double> solution;
		Solutions<double> solutions;

		for (const auto& [key, matrix] : matrices) {
			for (size_t i = 0; i < solvers.size(); ++i) {
				std::vector<double> x = solvers[i]->solve(matrix, 0.001);
				solution[solversNames[i]] = x;
			}
			solutions[key] = solution;
		}

		file_work::File<Solutions<double>>::write(
			file_work::PathParams("./data", "output", "json"),
			solutions);
	}
	catch (std::runtime_error& e) {
		std::cerr << "Error: " << e.what() << '\n';
	}

	return 0;
}