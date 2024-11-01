#ifndef TASK_1_SOLUTION_H
#define TASK_1_SOLUTION_H

#include "./Dependencies/file_work/file_processor.h"
#include "./Calculates-expressions/calculator.h"
#include <./Dependencies/stdafx.h>

#include "./Value.h"

namespace task_1 {

    void solution() {
        using namespace file_work;

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
        
        for (std::vector<PathParams>::const_iterator i1 = vec_input.begin(),
                                                     i2 = vec_output.begin();
                                                     i1 < vec_input.end();
                                                     ++i1, ++i2)
        {
            using Data = calc::Expression<Value<double>>;
            Data readData = File<Data>::read(*i1);

            std::map<std::string, Value<double>> results;

            for (const auto& pair : readData) {
                const std::string& expression = pair.first;
                const auto& data = pair.second;

                calc::Calculator<Value<double>> calculator(expression, data);
                const auto result = calculator.solve();

                results[expression] = result;
            }

            File<std::map<std::string, Value<double>>>::write(*i2, results);
        }
    }
}

#endif // !TASK_1_SOLUTION_H