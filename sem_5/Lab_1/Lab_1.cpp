#include <iostream>

#include "./task_1/Solution.cpp"
#include "./task_2/Solution.cpp"

int main() {
    try {
        task_1::solution();
        task_2::solution();
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}