#ifndef TASK_1_SOLUTION_H
#define TASK_1_SOLUTION_H

#include "./file_work/file_processor.h"
using namespace file_work;

#include "./Value.h"
#include "./calculates_expressions/calculator.h"

#include<iostream>

namespace task_1 {

    void solution() {
        std::vector<PathParams> vec_input{
            PathParams("./task_1/data", "1_row_input", "json"),
            PathParams("./task_1/data", "2_row_input", "json"),
            PathParams("./task_1/data", "3_row_input", "json")
        };

        std::vector<PathParams> vec_output{
            PathParams("./task_1/data", "1_row_output", "json"),
            PathParams("./task_1/data", "2_row_output", "json"),
            PathParams("./task_1/data", "3_row_output", "json")
        };

        using Data = std::map<std::string, std::map<std::string, Value<double>>>;
        
        for (std::vector<PathParams>::const_iterator i1 = vec_input.begin(),
                                                     i2 = vec_output.begin();
                                                     i1 < vec_input.end();
                                                     ++i1, ++i2)
        {
            using Data = Expression<Value<double>>;
            Data readData = File<Data>::read(*i1);

            std::map<std::string, Value<double>> results;

            for (const auto& pair : readData) {
                const std::string& expression = pair.first;
                const auto& data = pair.second;

                //std::cout << expression << std::endl;

                Calculator<Value<double>> calculator(expression, data);
                const auto result = calculator.solve();

                results[expression] = result;
            }

            File<std::map<std::string, Value<double>>>::write(*i2, results);
        }
    }
}

#endif // !TASK_1_SOLUTION_H