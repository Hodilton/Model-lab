#include "./task_1.h"
#include "./task_2.h"

int main() {
	std::cout << "Task 1:\n" << "f(x) = x * sqrt(x + 1), a = 0, b = 4" << std::endl;
	prac_3::task_1::solution();

	std::cout << "\nTask 2:\n" << "f(x) = x * y^2, a = 0, b = 1\n" << "D1 = x^2, D2 = 1 + x" << std::endl;
	prac_3::task_2::solution();

	return 0;
}