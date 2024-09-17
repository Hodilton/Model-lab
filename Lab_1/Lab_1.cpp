#include <iostream>

#include "./task_1/Solution.h"

int main() {
    try {
        task_1::solution(); 
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}