#ifndef TASK_1_CALCULATOR_H
#define TASK_1_CALCULATOR_H

#include "./Value.h"
#include "./ExpressionEvaluator.h"

class Calculator {
public:
    Calculator(const std::string& expression, const std::map<std::string, Value<double>>& letters):
    expression(expression), letters(letters) {}

    Value<double> solve() {
        ExpressionEvaluator<double> evaluator;

        evaluator.addOperator(std::make_shared<PlusOperator<double>>());
        evaluator.addOperator(std::make_shared<MinusOperator<double>>());
        evaluator.addOperator(std::make_shared<MultiplyOperator<double>>());
        evaluator.addOperator(std::make_shared<DivideOperator<double>>());

        return evaluator.evaluate(expression, letters);
    }

private:
    std::string expression;
    std::map<std::string, Value<double>> letters;
};

#endif // !TASK_1_CALCULATOR_H