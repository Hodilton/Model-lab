#include "./IntegralCalculator.h"
#include "./IntegralFactory.h"

#include <iostream>

namespace task_2 {

    class F1 : public IEquation {
    public:
        double evaluate(double x) const override {
            return exp(x);
        }

        double derivativeFirst(double x) const override {
            return exp(x);
        }

        double derivativeSecond(double x) const override {
            return exp(x);
        }

        std::string getStrF() const override {
            return "e^x";
        }
    };

    static void solution() {
        IntegralCalculator calculator;

        F1 function;
        double a = 0.0, b = 5.0;
        int n = 1000;

        std::vector<std::shared_ptr<IIntegrationMethod>> methods;
        methods.push_back(Factory::create<Type::LeftRectangle>());
        methods.push_back(Factory::create<Type::RightRectangle>());
        methods.push_back(Factory::create<Type::MiddleRectangle>());
        methods.push_back(Factory::create<Type::Trapezoid>());
        methods.push_back(Factory::create<Type::Simpson>());

        std::vector<std::string> methodNames = {
            "Left Rectangle Method",
            "Right Rectangle Method",
            "Middle Rectangle Method",
            "Trapezoid Method",
            "Simpson Method"
        };

        for (size_t i = 0; i < methods.size(); ++i) {
            try {
                calculator.setMethod(methods[i]);
                double result = calculator.calculate(function, a, b, n);
                std::cout << methodNames[i] << ": " << result << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << "Error with " << methodNames[i] << ": " << e.what() << std::endl;
            }
        }
    }
}