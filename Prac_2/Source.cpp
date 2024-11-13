#include "./Matrix/Matrix.h"
#include "./SolverFactory.h"

#include "./Dependencies/file_work/file_processor.h"

template<typename T>
using Solution = std::map<std::string, std::vector<T>>;

template<typename T>
using Solutions = std::map<std::string, Solution<T>>;

int main() {
	using namespace matrix;

	try {
		auto data = file_work::File<json>::read(
			file_work::PathParams("./data", "input", "json"));

		auto matrices = MatrixJsonDeserializer<double>::fromJsonMap(data);

		std::vector<std::shared_ptr<IMatrixSolver>> solvers;
		solvers.push_back(matrix::SolverFactory::create<matrix::Type::Gauss>());
		solvers.push_back(matrix::SolverFactory::create<matrix::Type::Jacobi>());
		solvers.push_back(matrix::SolverFactory::create<matrix::Type::Seidel>());
		solvers.push_back(matrix::SolverFactory::create<matrix::Type::Relaxatin>());

		std::vector<std::string> solversNames = {
			"Gauss",
			"Jacobi",
			"Seidel",
			"Relaxation"
		};
	
		std::string key = "1";
		Matrix<double> A = matrices.at(key);

		Solution<double> solution;
		Solutions<double> solutions;

		for (size_t i = 0; i < solvers.size(); ++i) {
			std::vector<double> vec = solvers[i]->solve(A, 0.001);
			solution[solversNames[i]] = vec;
		}

		solutions[key] = solution;

		file_work::File<Solutions<double>>::write(
			file_work::PathParams("./data", "output", "json"),
			solutions);
	}
	catch (std::runtime_error& e) {
		std::cerr << "Error: " << e.what() << '\n';
	}

	return 0;
}